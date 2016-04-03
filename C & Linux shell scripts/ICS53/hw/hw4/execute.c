#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char PATHS[50][50];
char* args[10];

/*EXCEEDING 5 LINES BY 2*/
void runWithFullPath(){
    int i;
    char fullPath[200];
    for (i = 0; strcmp(PATHS[i], "\0") != 0; ++i){
        strcpy(fullPath, PATHS[i]);
        strcat(fullPath, args[0]);
        if (execv(fullPath, args) == -1)
        {
            perror(fullPath); continue;
        }else{
            return;
        }
    }
}

void setPaths(){
    int i = 0;
    char *path = getenv("PATH");
    char *token = strtok(path, ":");
    do{
        if (token != NULL && (strcmp(token, ".") != 0)){
           strcpy(PATHS[i], token);
           strcat(PATHS[i++], "/");
        }
    }while((token = strtok(NULL, ":")) != NULL);
    strcpy(PATHS[i], "\0"); 
}

/*EXCEEDING 5 LINES BY 2*/
void setProgArgs(char *input){
    char *token = strtok(input, " ");
    int i = 0;
    args[i] = malloc(sizeof(char) * strlen(token) + 1);
    strcpy(args[i++], token);
    while((token = strtok(NULL, " ")) != NULL){
        args[i] = malloc(sizeof(char) * strlen(token) + 1);
        strcpy(args[i++], token);
    }
    args[i] = NULL;
}

void freeResources(){
    int i = 0;
    if (args[i] != NULL)
        free(args[i++]);
    else
        return;
}

int main(int argc, char *argv[], char *envp[]){
    char input[1024];
    scanf(" %[^\n]%*c", &input);
    setProgArgs(input); 
    setPaths();
    if (execv(args[0], args) == -1) runWithFullPath();
    freeResources();
}
