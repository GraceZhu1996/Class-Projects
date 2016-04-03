#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ioredirect.h"

#define SIGTSTP 20

char *args[10];
char **envp_;
pid_t child_pid = -1;
char buffer[4096];



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
    while(args[i] != NULL)
        free(args[i++]);
    resetIO();
}

void readFile(char *str, int fd){
    FILE* f = fdopen(fd, "r");
    if (f != NULL)
        fscanf(f, "%s", str);
}

int handleIORedirect(){
    int i = 0;
    while(args[i] != NULL){
        if (strcmp(args[i], ">") == 0){
            if(switchOutput(args[i+1]) == -1) return - 1; args[i] = NULL;
        }else if(strcmp(args[i], "<") == 0){
            if(switchInput(args[i+1]) == -1) return -1; args[i] = NULL;
        }
        i++;
    }
    return 0;
}

void createProcess(){
    child_pid = fork();
    if (child_pid == 0){ //If child process, execute.
        if (execvpe(args[0], args, envp_) == -1){ //This automatically closes the process on success
            perror(args[0]);
            exit(1);
        }
        exit(0);
    }
    else if(child_pid == -1)
        perror("fork");
}

void shellLoop(){
    int returnStatus;
    char input[1024];

    scanf(" %[^\n]%*c", &input);
    setProgArgs(input);
    if (handleIORedirect() != 0) return; 
    createProcess();
    waitpid(child_pid, &returnStatus, 0);
    if (returnStatus != 0) printf("Process terminated with error.\n");
    freeResources();
}

int main(int argc, char *argv[], char *envp[]){
    envp_ = envp;
    while(1){
        printf("%% ");
        shellLoop();
    }
}
