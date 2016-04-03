#include <stdio.h>
#include <string.h>
#include <memory.h>

char str1[10], str2[10];
int len1, len2;

#define Left 0
#define Up 1 
#define Topleft 2

void reset(char direction[][len2], int value[][len2]){
    int x,y;
    //Reset all values to 0
    for(x = 0; x < len1; x++){
        for(y = 0; y < len2; y++){
            direction[x][y] = 0;
            value[x][y] = 0;
        }
    }
}

void useMaxSurrounding(int var, char x, char y, char direction[][len2], int values[][len2]){
    int max = 0;
    if (x > 0){//Up
        if (max < values[x-1][y]){
            max =  values[x-1][y];
            direction[x][y] = Up;
        }
    }
    if (y > 0){ //Left
        if (max < values[x][y-1]){
            max =  values[x][y-1];
            direction[x][y] = Left;
        }
    }
    if (x > 0 && y > 0){ //TopLeft
        if (max < values[x-1][y-1]){
            max =  values[x-1][y-1];
            direction[x][y] = Topleft;
        }
    }
    values[x][y] = var + max;
}

void algorithm(char direction[][len2], int value[][len2]){
    int x,y;
     
    for(x = 0; x < len1; x++){
        for(y = 0; y < len2; y++){
            if (str1[x] == '-' ||  str2[y] == '-')
                continue;
            else if(str1[x] == str2[x])
            {
                value[x][y] = 2;
            }else{
                useMaxSurrounding(-1,x,y,direction,value);
            }
        }
    }
}

void printIt(char direction[][len2], int value[][len2]){
    int x,y;
    for(x = 0; x < len1; x++){
        for(y = 0; y < len2; y++){
            printf("%d ", value[x][y]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){
    if (argc > 2){
        strcat(str1, "-");
        strcpy(str2, "-");
        strcat(str1, argv[1]);
        strcat(str2, argv[2]); 
        len1 = strlen(str1);
        len2 = strlen(str2);
        
        char direction[len1][len2];
        int values[len1][len2];        
        reset(direction, values);
        algorithm(direction, values);
        printIt(direction, values);
    }else{
        return 1;
    }
    return 0;
}
