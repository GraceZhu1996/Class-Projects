#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int BUFFER = 7;
char* possible_input[50];

void load_posible_input();
FILE* openfile(char filename[], char* mode);
void read_lines(FILE* f, char* lines);
int english_to_decimal(char* line);
char* decimal_to_english(int dec);
char* get_string(int i);
char* get_int(char str[]);


void load_posible_input(){
     int i;
     for (i = 0; i < 21; i++)    
         possible_input[i] = decimal_to_english(i);
     for (i = 30; i < 91; i+=10)
         possible_input[i] = decimal_to_english(i);
}
char* decimal_to_english(int dec){   
      switch(dec){
                  case 1:
                       return "one";
                   case 2:
                       return "two";      
                   case 3:
                        return "three";
                   case 4:
                        return "four";
                   case 5:
                        return "five";
                   case 6:
                        return "six";
                   case 7:
                        return "seven";
                   case 8:
                        return "eight";
                   case 9:
                        return "nine";
                   case 0:
                        return "zero";
                   case 11:
                        return "eleven";
                   case 12:
                        return "twelve";
                   case 13:
                        return "thirteen";
                   case 14:
                        return "fourteen";
                   case 15:
                        return "fifteen";
                   case 16:
                        return "sixteen";
                   case 17:
                        return "seventeen";
                   case 18:
                        return "eighteen";
                   case 19:
                        return "nineteen";
                   case 20:
                        return "twenty";
                   case 30:
                        return "thirty";
                   case 40:
                        return "forty";
                   case 50:
                        return "fifty";
                   case 60:
                        return "sixty";
                   case 70:
                        return "seventy";
                   case 80:
                        return "eighty";
                   case 90:
                        return "ninety";
      }
}


char* get_int(char str[]){
    int i, j, s, size =50;
    char* result = (char*) malloc(size*sizeof(char));
    for (i = 0; i < 21; i++){
         if (strcasecmp(possible_input[i], str) == 0){
            snprintf(result, size, "%d", i) ;
            break;
         }
    }
     for (j = 30; j < 91; j+=10){
          if (strcasecmp(possible_input[j], str) == 0){
             snprintf(result, size, "%d", j);
            break;
            }
     }
    if (strcasecmp(str, "hundred") == 0)
       strncpy(result, "00", 2);
    if (strcasecmp(str, "thousand") == 0)
       strncpy(result, "000", 3);
     if (strcasecmp(str, "million") == 0)
       strncpy(result, "000000", 6);  
    
     return result;
}
int english_to_decimal(char* line){
    char* p;
    char c[6], result[10];
    char final[20];
    int size, i;
    while(line != NULL){
          p = get_int(line);
          strcpy(c, p);
          free(p);
          strcat(result, c);
          line = strtok(NULL, " "); 
          size = strnlen(result, 10);
          for (i = 0; i < size; i++){
              printf("%c", result[i]);    
          }
          strncpy(final, result, size);
          memset(result,0,size);
    }
     /*size = strnlen(final, 20);
      for (i = 0; i < size; i++){
          if (final[i] == '_'){
             final[i] = '0';             
          }    
      }*/
    //printf("%s", final);
    return 0;
}
int main(){
    load_posible_input();
    char input[1000];
    while(1){
        printf("Enter input: ");
        scanf(" %[^\n]%*c", &input);
        char* in_array = strtok(input, " ");
        english_to_decimal(in_array);
        printf("\n");
        }
    return 0;
}
