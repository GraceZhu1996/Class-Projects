#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
int j = 0;
int main()
{
    pid_t child = fork();
    if (child == 0){
        execlp("ls", "ls", NULL);
        j = 1;
    }else{
        waitpid(child, 0, 0);
        printf("J is [%d]\n", j);
    }
    return 0;
}
