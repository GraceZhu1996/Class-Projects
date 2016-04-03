#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char input[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

char *output[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

int size = 36;

int getIndexOfChar(char c){
    int i;
    for (i = 0; i < size; ++i){
        if (input[i] == toupper(c))
            return i;
    }
    return - 1;
}

int getIndexOfCode(char *c){
    int i;
    for (i = 0; i < size; ++i){
        if (strcmp(output[i], c) == 0)
            return i;
    }
    return - 1;
}

int starLength(char *c){
    int i = 0;
    while(*c == '*'){
        i += 1;
        c++;
    }
    return i;
}

void toMorse(char *in){
    char *c = in;
    while (*c){
        if (*c == ' ' || *c == '\n'){
            printf("*******");
            //sleep(7);
        }else if (isalpha(*c)){
            char *morse = output[getIndexOfChar(*c)];
            char *d = morse;
            while(*d){
                printf("%c", *d);
 //               printf("*");
                fflush(stdout);
              //  sleep(1);
                d++;
            }
            printf("***");
           // sleep(3);
        }
        c++;
    }
}

void toAlphabet(char *in){
    char *c = in;
    char morseWord[6];
    int s = 0;
    while(*c){
        if (*c == '*'){
          int i = starLength(c);
          c += i - 1;
          switch(i){
              case 3: //End current char and print
                  morseWord[s] = '\0';
                  printf("%c", input[getIndexOfCode(morseWord)]);
                  fflush(stdout);
                  s = 0;
                  break;
              case 10:
              case 7: //End current word and print
                  morseWord[s] = '\0';
                  printf("%c ", input[getIndexOfCode(morseWord)]);
                  fflush(stdout);
                  s = 0;
                  break;
        }
        }else if (*c == '.' || *c == '-'){
            morseWord[s] = *c;
            s++;
        }
        c++;
    }
    morseWord[s] = '\0';
    printf("%c ", input[getIndexOfCode(morseWord)]);
    fflush(stdout);
}

int main(){
    //toMorse("Hello World");
    printf("\n");
    //printf("%c\n", input[getIndexOfCode(".-")]);
     char input[500];
     scanf(" %[^\n]%*c", input);
     toAlphabet(input);
    return 0;
}
