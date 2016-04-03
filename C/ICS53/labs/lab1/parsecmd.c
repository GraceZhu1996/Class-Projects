#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

int parseNumber(char first){
    char number[250];
    number[0] = first;
    int size = 1;
    char c = getchar();
    while(isdigit(c))
    {
        number[size++] = c;
        c = getchar();
    }
    number[size++] = '\0';
    ungetc(c, stdin);
    return atoi(number);
}
void parseWord(char first, char word[]){
    char c = getchar();
    word[0] = first;
    int size = 1;
    while(isalpha(c) || ispunct(c))
    {
        if (ispunct(c)){
            if (c == '<' || c == '>' || c == '|' || c == '&')
            {
                ungetc(c, stdin);
                word[size] = '\0';
                return;
            }
        }
        word[size++] = c;
        c = getchar();
    }
    word[size++] = '\0';
    ungetc(c, stdin);
}

void parse_error(char *msg, char ch){
    fprintf(stderr, "ERROR: %s: %c\n", msg, ch);
}
int getToken(){
    int inch;
    while((inch = getchar())!= EOF)
        switch(inch){
            case ' ':
            case '\t':
            case '\n':
                break;
            case '&':
            case '|':
            case '<':
            case '>':
                printf("%c\n", inch);
                break;
                //                return inch;
            default:                
                if (isdigit(inch)){
                    printf("%d\n", parseNumber(inch));
                    break;
                }
                else if (isalpha(inch) || ispunct(inch)){
                    char word[250];
                    parseWord(inch, word);
                    printf("%s\n", word);
                    break;
                }
        }
}


int main(int argc, char* argv[]){
    if (argc > 1){
        FILE* f = freopen(argv[1], "r", stdin);
        if (f != NULL)
            getToken();
        else
            printf("Could not open file.\n");
        fclose(f);
    }else{
        printf("Enter file name.\n");
    }
    return 0;
}
