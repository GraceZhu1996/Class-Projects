#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define height 22
#define width 80

char game[height][width];

void initGame(){
    srand(time(NULL));
    int x,y;
    for (y = 0; y < height; ++y)
        for (x = 0; x < width; ++x)
            game[y][x] = rand() % 2;
}
void printGame(){
    int y,x;
    for (y = 0; y < height; ++y){
        printf("\n");
        for (x = 0; x < width; ++x)
            printf("%c ", (game[y][x]) ? 'X' : ' ');
    }
}
int countLiveNeighbors(int x, int y){
    int result = 0;
    if (x > 0)
        result += game[y][x-1]; //Left
    if (x < width - 1)
        result += game[y][x+1]; //Right
    if (y > 0)
        result += game[y-1][x]; //UP
    if (y < height - 1)
        result += game[y+1][x]; //Down
    if (x > 0 && y > 0)
        result += game[y-1][x-1]; //TopLeft
    if (x > 0 && y < height -1)
        result += game[y+1][x-1]; //BottomLeft
    if (x < width - 1 && y > 0)
        result += game[y-1][x+1]; //TopRight
    if (x < width - 1 && y < height -1)
        result += game[y+1][x+1]; //BottomRight
    return result;
}
void replaceBoard(char backup[][width]){
    int x,y;
    for (y = 0; y < height; ++y)
        for (x = 0; x < width; ++x)
            game[y][x] = backup[y][x];
}

void advanceGame(){
    char backup[height][width];
    int x,y;
    for (y = 0; y < height; ++y){
        for (x = 0; x < width; ++x){
            int alive = countLiveNeighbors(x, y);
            switch(game[y][x]){
                case 1: //Live
                    if (alive < 2 || alive > 3) backup[y][x] = 0;
                    else backup[y][x] = game[y][x];
                    break;
                case 0: //Dead
                    if (alive == 3) backup[y][x] = 1; 
                    else backup[y][x] = game[y][x];
                    break;
            }
        }
    }
    replaceBoard(backup);
}
int main(){
    initGame();
    while(1){
        printGame();
        advanceGame();
        fflush(stdin);
        sleep(1);
    }
    return 0;
}
