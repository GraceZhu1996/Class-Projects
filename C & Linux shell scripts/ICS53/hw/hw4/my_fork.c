#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


pid_t pID;
int returnStatus;

void printNTimes(char c, int n){
    while(n-- > 0){
        putchar(c);
        fflush(stdout);
        sleep(1);
    }
}

void createProcess(char c, int n){
    pID = fork();
    if (pID == 0) printNTimes(c, n);
    else if (pID == -1) perror("fork");
}

int main(int argc, char *argv[]){
    pid_t wpid;
    int returnStatus;
    int n = (argc > 1) ? atoi(argv[1]) : 10000;
    char c = 'A';
    do
    {
        createProcess(c++, n);
    }while(pID > 0 && c != 'E'); //WHile this is parent
    waitpid(pID, &returnStatus, 0);
}
