#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

struct sigaction act;
int interupt = 0;
int quit = 0;
int stop = 0;

void printstats(){
    printf("\nInterrupt: %d\nStop: %d\nQuit: %d\n", interupt, stop, quit);
    raise(SIGKILL);
}

void sighandler(int signum, siginfo_t *info, void *ptr)
{
    switch(signum){
        case SIGTSTP:
            printf("S");
            fflush(stdin);
            stop++;
            (stop == 3) ? printstats() : raise(SIGSTOP);
            break;
        case SIGINT:
            printf("I");
            interupt++;
            break;
        case SIGQUIT:
            printf("Q");
            quit++;
            break;
    }
    fflush(stdin);
}

void init(){
    memset(&act, '\0', sizeof(act));
    act.sa_sigaction = sighandler;
    act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGTSTP, &act, NULL) < 0){
        perror("sigaction");
        return 1;
    }
    if (sigaction(SIGINT, &act, NULL) < 0){
        perror("sigaction");
        return 1;
    }
    if (sigaction(SIGQUIT, &act, NULL) < 0){
        perror("sigaction");
        return 1;
    }
}

int main(){
    init();

    while(1){
        printf("X");
        fflush(stdout);
        sleep(1);
    }
    return 0;
}
