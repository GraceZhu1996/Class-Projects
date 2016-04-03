#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include "wordcount.c"

struct dirent *ent;
struct stat *statbk;
struct passwd *pw;
struct group *grp;

void handleError(char *dir, int lvl);



DIR* openDirectory(char *dir){
    DIR *dirp;
    if (!(dirp = opendir(dir))){
        return NULL;
    }
    return dirp;
}

char* getNameFromPath(char* path){
    char *c = strrchr(path, '/');
    if (!c) return NULL;
    path = ++c;
    return path;
}

void printCount(char* dir, int lvl){
    char* strFormat = "%10d %10d %9jd %s\n"; //Newline count, word count, byte count
    if (strlen(dir) > 0 && (dir[0] != '.' || strlen(dir) > 2))     //Exclude hidden files
    {
        if(stat(dir, statbk) == -1){
            handleError(dir, lvl);
        }else{
            FILE* f = fopen(dir, "r");
            if (f != NULL){
                struct Count count = getWordCount(f);
                printf(strFormat, count.newLine, count.word, (intmax_t) statbk->st_size, dir);
            }
        }
    }
}

void handleError(char *dir, int lvl){
    if (errno == ENOTDIR) //File not DIR
        printCount(dir, lvl);
    else
        fprintf(stderr, "Error(%d) opening %s\n", errno, dir);

}

void wc(char *dir, int lvl, int ignoreHidden, int workingDir){
    DIR* d;
    char *contents[500];
    if (workingDir) lvl = -1;
    if ((d = openDirectory(dir)) != NULL){
        printCount(dir, lvl);
        while((ent = readdir(d)) != NULL){
            if (ignoreHidden && ent->d_name[0] == '.') continue;
            char longPath[500];
            strcpy(longPath, dir);
            strcat(longPath, "/");
            strcat(longPath, ent->d_name);
            wc(longPath, lvl+1, 1, 0);
        }
    }else{
        handleError(dir, lvl);
    }
    
}

int main(int argc, char* argv[]){
    int i;
    statbk = malloc(sizeof(struct stat));

    if (argc < 2)
        wc(".", 0, 1, 1);
    for (i = 1; i < argc; ++i)
        wc(argv[1], 0, 1, 1);
    free(statbk);       
    return 0;
}		      
