#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define SCHEME 0
#define DOMAIN 1
#define PATH 2

void parseWord(char first, char word[], int* type){
    char c = getchar();
    word[0] = first;
    int size = 1;
    while(isalpha(c) || isdigit(c) || ispunct(c))
    {
        if (ispunct(c)){
            if (c == ':' || c== '?' || c=='#')
            {
                char d = getchar();
                if (isdigit(d)){
                    (*type)+= 1;
                }
                ungetc(d, stdin);
                ungetc(c, stdin);
                word[size] = '\0';
                return;
            }else if(c == '/'){
                ungetc(c, stdin);
                word[size] = '\0';
                (*type)+= 1;
                return;
            }
        }
        word[size++] = c;
        c = getchar();
    }
    word[size++] = '\0';
    ungetc(c, stdin);
    (*type)+= (*type == SCHEME) ? 1 : 2;
}

void parseOther(char first, char word[]){
    char c = getchar();
    word[0] = first;
    int size = 1;
    while(isalpha(c) || isdigit(c) || ispunct(c))
    {
        if (ispunct(c)){
            if (c == ':'|| c== '?' || c=='#')
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

int parseNum(char first){
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

void getToken(){
    int inch;
    int type = SCHEME;
    while((inch = getchar())!= EOF)
        switch(inch){
            case ' ':
            case '\t':
            case '\n':
                type = SCHEME;
                printf("\n");
                break;
            case ':':
                break;
            case '/':
                inch = getchar();
                if(inch != '/'){
                    char word[250];
                    parseOther(inch, word);
                    printf("path: %s\n", word);
                }
                break;
            case '?':
                inch = getchar();
                if(inch != ' '){
                    char word[250];
                    parseOther(inch, word);
                    printf("query_string: %s\n", word);
                }
                break;
            case '#':
                inch = getchar();
                if(inch != ' '){
                    char word[250];
                    parseOther(inch, word);
                    printf("fragment_id: %s\n", word);
                }
                break;
            default: 
                if (isdigit(inch)){
                    int num = parseNum(inch);
                    printf("port: %d\n", num);
                    break;
                }
                if (isalpha(inch)|| ispunct(inch)){
                    char word[250];
                    parseWord(inch, word, &type);
                    if(type == SCHEME){
                        printf("scheme: %s\n", word);
                    }else if (type == DOMAIN){
                        printf("domain: %s\n", word);
                    }
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
