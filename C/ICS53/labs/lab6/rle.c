#include <stdio.h>
#include <string.h>
#include <ctype.h>

void tally(char *str, char c, int count){
    char temp[10];
    sprintf(temp, "%d%c", count, c);
    strcat(str, temp);
}

void parseInput(){
    char result[1024];
    char c, last;
    int count = 0, loop = 0;
    while((c = getchar()) != EOF){
        if (isalpha(c)){        
            if (last != '\n' && c != last && loop > 0){
                tally(result, last, count);
                count = 0;
            }
            count++;
        }else if(c == '\n'){
            tally(result, last, count);
            count = 0;
            strcat(result, "\n");
        }
        last = c;
        loop++;
    }
    printf("%s", result);
}

int main(){
    parseInput();
    return 0;
}
