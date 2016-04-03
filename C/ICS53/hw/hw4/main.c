#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"
#include "Timer.h"

void print_time(int method){
    double wallclock;
    double user_time;
    double system_time;
    Timer_elapsedTime(&wallclock, &user_time, &system_time);
    printf("Method[%d]: Wallclock: %lf | User Time: %lf | System Time: %lf\n", method, wallclock, user_time, system_time);
}

void useMethod1(char *from, char *to, int repeat){
    FILE* f = fopen(from, "r");
    FILE* t = fopen(to, "w");
    Timer_start();
    while(repeat-- > 0)
        method1(f, t);
    print_time(1);
    fclose(f); fclose(t);
 
}

/*EXCEDING 5 LINES BY 2*/
void useMethod2(char *from, char *to, int repeat){
    int f = open(from, O_RDONLY);
    int w = open(to, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (f != -1 && w != -1){
        Timer_start();
        while(repeat-- > 0)
            method2(f, w);
        print_time(2);
        if ((close(w) != -1) && (close(f) != -1)) return;
        else perror("method2");
    }
}

/*EXCEEDING 5 LINES BY 2*/
void useMethod3(char *from, char *to, int repeat){
    int f = open(from, O_RDONLY);
    int w = open(to, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (f != -1 && w != -1){
        Timer_start();
        while(repeat-- > 0)
            method3(f, w);
        print_time(3);
        if ((close(w) != -1) && (close(f) != -1)) return;
        else   perror("method3");
    }
}

int main(int argc, char *argv[]){
    int repeat = (argc > 4) ? atoi(argv[4]) : 1;
    char *from = argv[2];
    char *to = argv[3];
    if (argc >= 4){
        switch(atoi(argv[1])){
            case 1:
                useMethod1(from, to, repeat);
                break;
            case 2:
                useMethod2(from, to, repeat);
                break;
            case 3:
                useMethod3(from, to, repeat);
                break;
        }
    }

    return 0;
}
