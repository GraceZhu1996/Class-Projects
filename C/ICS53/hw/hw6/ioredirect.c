#include "ioredirect.h"

int default_stdin = -1;
int default_stdout = -1;
int new_stdin = -1;
int new_stdout = -1;

int switchInputFD(int fd){
    if (new_stdout != -1) return -1;
    default_stdin = dup(STDIN_);
    new_stdin = fd;
    if((dup2(new_stdin, STDIN_)) == -1) perror("switchInput");// else close(new_stdin);
    return new_stdin;
}
int switchOutputFD(int fd){
    if (new_stdout != -1) return -1;
    default_stdout = dup(STDOUT_);
    new_stdout = fd;
    if((dup2(new_stdout, STDOUT_)) == -1) perror("switchOutput");// else close(new_stdout);
    return new_stdout;
}

/*EXCEEDING 5 LINES BY 2*/
int switchInput(char *filename){
    if (new_stdout != -1) return -1;
    default_stdin = dup(STDIN_);
    if ((new_stdin = open(filename, O_RDONLY)) != -1){
        if((dup2(new_stdin, STDIN_)) == -1) perror("switchInput"); else close(new_stdin);
    }else{
        perror("open");
    }
    return new_stdin;
}
    
/*EXCEEDING 5 LINES BY 2*/
int switchOutput(char *filename){
    if (new_stdout != -1) return -1;
    if ((new_stdout = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)) != -1){
        default_stdout = dup(STDOUT_);
        if((dup2(new_stdout, STDOUT_)) == -1) perror("switchOutput"); else close(new_stdout);
    }else{
        perror("open");
    }
    return new_stdout;
}

void closeIO(int closeid, int replaceid){
    if((dup2(replaceid, closeid)) == -1) perror("switchOutput");
    close(closeid);
}

void resetOutput(){
    fflush(stdout);
    if (new_stdout != -1){
        dup2(default_stdout, STDOUT_);  close(default_stdout);
    }
    new_stdout = -1;
}

void resetInput(){
    fflush(stdin);
    if (new_stdin != -1){
        dup2(default_stdin, STDIN_);  close(default_stdin);
    }
    new_stdin = -1;
}
void resetIO(){
    resetInput();
    resetOutput();
}
