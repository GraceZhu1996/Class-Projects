#include<stdio.h>
#include<ctype.h>
#include<string.h>

int count[1000];
char character[1000];
int whitespaceCount = 0;
int nonprintableCount = 0;
int size = 0;

int findIndexOfChar(char c){
    int i = 0;
    while(i < size){
            if (c == character[i])
               return i;
            i++;
    }
    return -1;
}

void incrementChar(char c){
     int index = findIndexOfChar(c);
     if (index != -1) {
        count[index]++;
     }
     else
     {
         character[size] = c;
         count[size] = 1;
         size++;
     }
}    


void getToken(){
    int inch;
    while((inch = getchar())!= EOF)
        switch(inch){
            default: 
                if (isprint(inch) && !isspace(inch)){
                    incrementChar(inch);
                    break;
                }else if (isspace(inch)){
                      if (inch == ' ')
                         incrementChar(inch);
                      whitespaceCount++;
                      break;
                }else{
                      nonprintableCount++;
                      break;
                }
        }
}

void print(){
     int i = 0;
     while(i < size){
             printf("'%c' %d\n", character[i], count[i]);
             i++;
     }
     printf("Whitespace Characters %d\n", whitespaceCount);
     printf("Other Characters %d\n", nonprintableCount);
}

int main(int argc, char* argv[]){
    if (argc > 1){
        FILE* f = freopen(argv[1], "r", stdin);
        if (f != NULL){
            getToken();
            print();
        }else{
            printf("Could not open file.\n");
        }
        fclose(f);
    }else{
        printf("Enter file name.\n");
    }
    return 0;
}
