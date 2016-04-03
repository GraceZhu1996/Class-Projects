#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int inputToIntArray(int *input){
    int n = 0, in = 0;
    while((scanf("%d", &in)) != EOF){
        input[n++] = in;
    }
    return n;
}

void solve(int input[], int output[], int size){
    int i, j;
    int t = 1, t2 = 1;
    for (i = 0; i < size; i++)
    {
        output[i] = t; t *= input[i];
    }
    for (j = size - 1; j >= 0; j--){
        output[j] *= t2; t2 *= input[j]; 
    }
}



int main(int argc, char *argv[]){
    int i, input[50];
    int size = inputToIntArray(input);
    int output[size];
    memset(output, 1, size);
   
    solve(input, output, size);

    for (i = 0; i < size; i++)
        printf("%d\t%d\n",i, output[i]);
    return 0;
}
