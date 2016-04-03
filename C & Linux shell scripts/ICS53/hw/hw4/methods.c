#include "methods.h"

void method1(FILE* f, FILE *t){
    char c;
    if (f != NULL && t != NULL){
        while((c = fgetc(f)) != EOF)
            if ((fputc(c, t)) != EOF)  continue;
            else  return;
    }
}


void method2(int f, int w){
    char buffer[1];
    while((read(f, buffer, 1)) > 0)
        if((write(w, buffer, 1)) != -1)
            continue;
        else
            perror("method2");
}


void method3(int f, int w){
    char buffer[BUFSIZ];
    size_t b;
    while((b = read(f, buffer, BUFSIZ)) > 0)
        if((write(w, buffer, b)) != -1)
           continue;
        else
           perror("method3");
}

