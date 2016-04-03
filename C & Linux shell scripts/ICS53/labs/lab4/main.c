#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stk.h"

void stackOpr(char input[]){
    char c = input[strlen(input) - 1];
    if (isdigit(c)){
        if (!stk_is_full()){
            stk_push(make_element(atoi(input)));
        }
    }else if(isalpha(c)){
        if (stk_is_empty()){
            return;
        }
        char *value = stk_pop().buf;
        switch(c){
            case 'p':
                printf("%s\n", value);
                stk_push(make_element(atoi(value)));
                break;
            case 's':
                if (1){
                    char *bottom = stk_pop().buf;
                    stk_push(make_element(atoi(value)));
                    stk_push(make_element(atoi(bottom)));
                }
                break;
            case 'd':
                stk_push(make_element(atoi(value)));
                stk_push(make_element(atoi(value)));
                break;
        }
    }else if(ispunct(c)){
        if (stk_is_empty()){
            return;
        }
        char* top = stk_pop().buf;
        char* bottom = stk_pop().buf;
        switch(c){
            case '+':
                stk_push(make_element(atoi(bottom) + atoi(top)));
                break;
            case '-':
                stk_push(make_element(atoi(bottom) - atoi(top)));
                break;
            case '/':
                stk_push(make_element(strtoll(bottom, NULL, 10) / strtoll(top, NULL, 10)));
                break;
            case '*':
                stk_push(make_element(strtoll(bottom, NULL, 10) * strtoll(top, NULL, 10)));
                break;
        }
    }
}

int main(int argc, char *argv[]){
    char input[1024];
    while((scanf(" %[^\n]%*c", &input)) != EOF){
        char *token = strtok(input, " ");
        do{
//          printf("%s\t%d\n", token, strcmp(token, "*"));
           stackOpr(token);
        }while((token = strtok(NULL, " ")) != NULL);
    }
  
    return 0;
} 
