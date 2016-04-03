#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

struct Count{
    int newLine;
    int word;
};

struct Count getToken(FILE* f){
    int inch, newWord = 0;
    struct Count count;
    count.newLine = 0; count.word = 0;
    while((inch = fgetc(f))!= EOF){
        switch(inch){
            case '\n':
                count.newLine++;
                if (newWord)
                    count.word++;
                newWord = 0;
                break;
            case '\r':
            case ' ':
                if (newWord)
                    count.word++;
                newWord = 0;
                break;
            default: 
                if (isprint(inch)){
                        newWord = 1;
                }
        }
    }
    return count;
   
}



struct Count getWordCount(FILE* f){
    struct Count c = getToken(f);
    return c;
}
