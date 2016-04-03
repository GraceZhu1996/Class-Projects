#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ioredirect.h"

#define IN 1
#define OUT 2
#define PIPE 3

char *args[10];
char **envp_;
char buffer[4096];
int outputfd = -1;


int isRedir(char *str){
    if (str == NULL) return 0;
    if (strcmp(str, ">") == 0)
       return OUT;
    else if(strcmp(str, "<") == 0)
       return IN;
    else if(strcmp(str, "|") == 0)
       return PIPE;
    else
        return 0;
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

int miniArgs(char *mini[], int *index){
    int size = 0;
    while(args[*index] != NULL && !isRedir(args[*index])){
        mini[size++] = args[*index];
        (*index)++;
    }
    mini[size] = NULL;
    return (size == 0) ? 0 : 1;
}

int scanForRedir(char *args[]){
    int i = 0;
    while(args[i] != NULL)
        if(isRedir(args[i++])) return 1;
    return 0;
}

void crunchArgs(int from){
    int i = 0;
    while(args[from] != NULL)
        args[i++] = args[from++];
    args[i] = NULL;
}

void freeResources(){
    int i = 0;
    while(args[i] != NULL)
        free(args[i++]);
}

void readFile(char *str, int fd){
    FILE* f = fdopen(fd, "r");
    if (f != NULL)
        fscanf(f, "%s", str);
}

void createProcess(char *args[10]){
    int status;
    pid_t child_pid = fork();
    switch(child_pid){
        case 0: //If child process, execute.
            if (execvpe(args[0], args, envp_) == -1){ //This automatically closes the process on success
                perror(args[0]);
                exit(1);
            }
            exit(0);
        case -1:
            perror("fork");
            break;
        default: //Parent
            waitpid(child_pid, &status, 0);
            if (status != 0) printf("Process terminated with error.\n");
    }
    
}
void printTillNULL(char *C[]){
    int i = 0;
    while(C[i] != NULL)
        printf("%s\n", C[i++]);
}

int doPipe(char *commands[], int pipein, int pipeout){
    pid_t child = fork();
    switch (child){
        case 0:
            close(pipeout);
            switchInputFD(pipein);
            createProcess(commands);
            break;
        case -1:
            break;
        default:
            wait(&child);
            close(pipein);
            switchOutputFD(pipeout);
            close(pipeout);
            return 0;
    }
    return 0;
}


int parseArgsWithRedir(){
    int i = 0;
    char *mini[10];
    int fd[2]; pipe(fd);
    while(args[i] != NULL){
        int type = 0, next = 0, piped = 0;
        int res = (miniArgs(mini, &i));
        if ((type = isRedir(args[i])) != 0){
            switch(type){
                case IN:
                    switchInput(args[i+1]); i+=2;
                    next = isRedir(args[i]);
                    if (next == OUT){ 
                        switchOutput(args[i+1]); i+=2;
                    }else if (next == PIPE){
                        switchOutputFD(fd[1]); i+=1; piped = 1;
                    }
                    break;
                case OUT:
                    switchOutput(args[i+1]); i+=2;
                    next = isRedir(args[i]);
                    if (next == IN){ 
                        switchInput(args[i+1]); i+=2;
                    }else if (next == PIPE){
                        switchInputFD(fd[0]); i+=1; piped = 1;
                    }
                    break;
                case PIPE:
                    //switchInputFD(fd[0]);
                    //switchOutputFD(fd[1]);
                    piped = 1;
                    i++;
                    break;
            }
        }else{
            i++;
        }
        if (res && !piped){
            createProcess(mini);
        }else if (piped){
            doPipe(mini, fd[0], fd[1]);
        }

            resetIO();
    }
    resetIO();
}

void shellLoop(){
    char input[1024];
    scanf(" %[^\n]%*c", &input);
    setProgArgs(input);
    if (scanForRedir(args)) parseArgsWithRedir(); else createProcess(args); 
    freeResources();
}

int main(int argc, char *argv[], char *envp[]){
    envp_ = envp;
    while(1){
        printf("%% ");
        shellLoop();
    }
}
