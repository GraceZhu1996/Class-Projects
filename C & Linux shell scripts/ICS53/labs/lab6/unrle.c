#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

void printCNtimes(char c, int n){
    while(n-- > 0)
        printf("%c", c);
    fflush(stdout);
}

void parseInput(){
    char count[5];
    char c;
    while((c = getchar()) != EOF){
        int i = 0;
        if (isalpha(c)){
            printCNtimes(c, atoi(count));
            memset(count, 0, strlen(count));
        }else if (isdigit(c)){
            i =  strlen(count);
            count[i] = c;
            count[i+1] = '\0';
        }else if(c == '\n'){
            printf("\n");
        }
    }    
}

int main(){
    parseInput();
    return 0;
}

