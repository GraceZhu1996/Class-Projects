#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>

struct dirent *ent;
struct stat *statbk;

int level = 0;
int size = 0;

void handleError(char *dir, int lvl);

char* humanReadable(int size, char *buf){
    int i = 0;
    const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    while(size>1024){
        size /= 1024;
        i++;
    }
    sprintf(buf, "%d%s", size, units[i]);
    return buf;
}


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
    if (strlen(dir) > 0)// && (dir[0] != '.' || strlen(dir) > 2))     //Exclude hidden files
    {
        if(stat(dir, statbk) == -1){
            handleError(dir, lvl);
        }else{
            FILE* f = fopen(dir, "r");
            char buffer[1024];
            if (f != NULL){
                printf("%s\t %s\n", humanReadable((intmax_t) statbk->st_size, buffer),  dir);
                if (level == lvl){
                    size +=  (intmax_t) statbk->st_size;
                }else{
                    level = 0;
                    size = 0;
                }
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

void du(char *dir, int lvl, int ignoreHidden, int workingDir){
    DIR* d;
    char *contents[500];
    if (workingDir) lvl = -1;
    if ((d = openDirectory(dir)) != NULL){

        while((ent = readdir(d)) != NULL){
            if (ignoreHidden && ent->d_name[0] == '.') continue;
            char longPath[500];
            strcpy(longPath, dir);
            strcat(longPath, "/");
            strcat(longPath, ent->d_name);
            du(longPath, lvl+1, 1, 0);
        }
        if(stat(dir, statbk) == -1){
            handleError(dir, lvl);
        }else{
            char buffer[1024];
            printf("%s\t %s\n", humanReadable(size + (intmax_t) statbk->st_size, buffer),  dir);
        }
    }else{
        handleError(dir, lvl);
    }
    
}

int main(int argc, char* argv[]){
    int i;
    statbk = malloc(sizeof(struct stat));

    if (argc < 2)
        du(".", 0, 1, 1);
    for (i = 1; i < argc; ++i)
        du(argv[1], 0, 1, 1);
    free(statbk);       
    return 0;
}		      
