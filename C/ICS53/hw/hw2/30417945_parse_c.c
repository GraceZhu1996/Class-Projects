#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define OPERATOR 0
#define DIGIT 1
#define PUNCT 2
#define WORD 3

int isoperator(char c){
    char* operators = "-+*/%!=><|&^~";
    char *s = operators;
    while(*s){
        if (*s == c)
            return 1;
        s++;
    }
    return 0;
}
 /* EXCEEDING 5 LINES BY 2 */ 
int gettype(char c){
    if (isoperator(c))
        return OPERATOR;
    if (isdigit(c))
        return DIGIT;
    if (ispunct(c))
        return PUNCT;
    return WORD;
}
void endStringUnget(char *str, int loc, char c){
    str[loc] = '\0';
    ungetc(c, stdin);
}
void parseNumber(char number[]){
    char c = getchar();
    int size = 1;
    while(isdigit(c))
    {
        number[size++] = c;
        c = getchar();
    }
    endStringUnget(number, size, c);
}
void parseOperator(char opr[]){
    int size = 1;
    char c = getchar();
    while(isoperator(c))
    {
        opr[size++] = c;
        c = getchar();
    }
    endStringUnget(opr, size, c);
}
void parseString(char word[]){
    char c = getchar(),  previous;
    int status = 1;
    int size = 1;
    while(status)
    {
        word[size++] = c;
        if ((c == '\"' || c == '\'') && previous != '\\') status = 0;
        previous = c; c = getchar();
    }
    endStringUnget(word, size, c);
}

 /* EXCEEDING 5 LINES BY 2 */
void parseWord(char word[]){
    char c = getchar();
    int size = 1;
    while(isalpha(c) || ispunct(c))
    {
        if (ispunct(c)){
            endStringUnget(word, size, c);
            return;
        }
        word[size++] = c;
        c = getchar();
    }
    endStringUnget(word, size, c);
}

void handleToken(char inch, int type){
    char opr[10], word[250], number[250];
    switch(type){
        case OPERATOR:
            opr[0] = inch;
            parseOperator(opr);
            printf("%s\n", opr);
            break;
        case PUNCT:
            printf("%c\n", inch);
            break;
        case DIGIT:
            number[0] = inch;
            parseNumber(number);
            printf("%d\n", atoi(number));
            break;
        default:
            word[0] = inch;
            parseWord(word);
            printf("%s\n", word);
            break;
    }
}
int getToken(){
    int inch, comment_trigger = 0;
    char word[250];
    while((inch = getchar())!= EOF)
        switch(inch){
            case ' ':
                break;
            case '\t':
            case '\n':
                comment_trigger = 0;
                break;
            case '/':
                comment_trigger += 1;
                break;
            case '\\':
                comment_trigger -= 1;
                break;
            case '*':
                switch(comment_trigger){
                    case 1:
                        comment_trigger++;
                        break;
                    case 2:
                        comment_trigger--;
                        break;
                    case 0:
                        printf("%c\n", inch);
                        break;
                }
                break;
            case '\'':
            case '\"':
                word[0] = inch;
                parseString(word);
                printf("%s\n", word);
                break;
            default:
                if (comment_trigger == 2) break;
                handleToken(inch, gettype(inch)); 
                break;
        }
}

int main(int argc, char* argv[]){
    getToken();
    return 0;
}
