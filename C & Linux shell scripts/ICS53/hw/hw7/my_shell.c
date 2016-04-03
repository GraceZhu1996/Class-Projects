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
int bgjob = -1;
int bgcount = 0;

/*EXCEEDING 5 LINES BY 2*/
int setProgArgs(char *input){
    char *token = strtok(input, " ");
    int i = 0;
    args[i] = malloc(sizeof(char) * strlen(token) + 1);
    strcpy(args[i++], token);
    while((token = strtok(NULL, " ")) != NULL){
        args[i] = malloc(sizeof(char) * strlen(token) + 1);
        strcpy(args[i++], token);
    }
    args[i] = NULL;
    return i-1;
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


int miniArgs(char *mini[], int *index){
    int size = 0;
    while(args[*index] != NULL && strcmp(args[*index], "|") != 0){
        mini[size++] = args[*index];
        (*index)++;
    }
    mini[size] = NULL;
    return (size == 0) ? 0 : 1;
}

void createProcess(char *args[10]){
    int returnStatus;
    child_pid = fork();
    switch(child_pid){
        case 0: //If child process, execute.
            execvpe(args[0], args, envp_); //This automatically closes the process on success
            perror(args[0]);
            exit(0);
        case -1:
            perror("fork");
        default:
            waitpid(child_pid, &returnStatus, 0);
            if (returnStatus != 0) printf("%s terminated with errors.\n", args[0]);
    }
}

void createPipeProcess(char *args[], int fd[]){
    child_pid = fork();
    switch(child_pid){
        case -1:
            perror("Fork");
            break;
        case 0:
            close(fd[1]);
            dup2(fd[0], 0);
            execvpe(args[0], args, envp_); //This automatically closes the process on success
            perror(args[0]);
            close(fd[0]);
            exit(0);
        default:
            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);
            wait(NULL);
    }
}

void crunchArgs(int from){
    int i = 0;
    while(args[from] != NULL)
        args[i++] = args[from++];
    args[i] = NULL;
}

void printArgs(char *args[]){
    int i = 0;
    while(args[i] != NULL)
        printf("%i: %s\n", i++, args[i]);
    args[i] = NULL;
}
int handleIORedirect(){
    int i = 0;
    char *mini[10];
    while(args[i] != NULL){
        if (strcmp(args[i], ">") == 0){
            if(switchOutput(args[i+1]) == -1) return - 1; args[i] = NULL;
        }else if(strcmp(args[i], "<") == 0){
            if(switchInput(args[i+1]) == -1) return -1; args[i] = NULL;
        }else if(strcmp(args[i], "|") == 0){
            args[i] = NULL;
            if(miniArgs(mini, &i)){
                int fd[2]; pipe(fd);
                createPipeProcess(mini, fd);
            }
            crunchArgs(i+1);
            i = 0;
        }

        i++;
    }
    createProcess(args);
    return 0;
}

void bgRun(){
    int returnstatus;
    bgjob = fork();
    switch(bgjob){
        case -1:
            perror("Fork");
            break;
        case 0:
            setpgid(0,0);
            if (handleIORedirect() != 0) return; 
            freeResources();
            fflush(stdout);
            exit(0);
        default:
            bgcount++;
            waitpid(bgjob, &returnstatus, 0);
            printf("BG Job [%d] %s\n", bgcount, (returnstatus) ? "Failed" : "Successful");
            bgcount--;
            return;
    }
}

void run(){
    if (handleIORedirect() != 0) return; 
    freeResources();
}

int main(int argc, char *argv[], char *envp[]){
    envp_ = envp;
    while(1)
    {
        int bg;
        char input[1024];
        printf("%% ");
        scanf(" %[^\n]%*c", &input);
        bg = setProgArgs(input); //Set program arguments and see if we need to run in background
        if (strcmp(args[bg], "&") == 0){
            args[bg] = NULL;
            bgRun();
        }else{
            run();
        }
    }
}
