#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>


struct dirent *ent;
typedef struct {
    char *pattern;
    int file_index;
    char * file_name;
} arg_struct;

int error(char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void print_number(int i)
{
	printf(" %d ", i);
}
void print_string(char *s)
{
	printf(" %s ", s);
}
void print_match(char * file_name, int file_index, int line_number, char * line)
{
    // Ensure text for match comes out on one line (so lines are atomic)
    // Matches from several files may be intermixed with each other (if parallel).
    // Use the following to start, but it will be wrong if your parallelism is working.
    print_number(file_index);
    print_string(file_name);
    print_number(line_number);
    print_string(line);
    printf("\n");
}

void add_all_matching_lines(char * pattern, int file_index, char * file_name)
{
    int line_number = 1;
    FILE* f; char line[200];
    if ((f = fopen(file_name, "r")) != NULL){
        while(fgets(line, 200, f) != NULL){
            if(strstr(line, pattern) != NULL)
                print_match(file_name, file_index, line_number, line);
            fflush(stdout);
            line_number++;
        }
        fclose(f);
    }
    
}

void *threadCall(void *args){
    arg_struct *real_args = args;
    add_all_matching_lines(real_args->pattern, real_args->file_index, real_args->file_name); 
    free(real_args);
//    pthread_exit(NULL);
}

char* fullpath(char *dir, char name[], char buffer[]){
    strcpy(buffer, dir);
    strcat(buffer, "/");
    strcat(buffer, name);
    return buffer;
}

void search(char * pattern, int file_index, char * file_name)
{

    DIR* dir; char longpath[500];
    if ((dir = opendir(file_name)) == NULL){
        if (errno == ENOTDIR){ //FILE
        //DO: fork_thread add_all_matching_lines(pattern, file_index, file_name);
            //int child = fork(), r;
            int r;
            pthread_t thread;
            arg_struct *args = malloc(sizeof(*args));
            //switch(child){
             //   case 0:
                    args->pattern = pattern;
                    args->file_index = file_index;
                    args-> file_name = file_name;
                    r = pthread_create(&thread, NULL, threadCall, args);               
                    if (r != 0){
                       free(args);
                       error("pthread_create()");
                    }

    //                pthread_join(thread, NULL);
               //     exit(0);
               // case -1:
               //     free(args);
               //     error("fork()");
               // defualt:
               //     return;
           // }
        }else   return;
    }else { //DIR
        while((ent = readdir(dir)) != NULL){
            if (ent->d_name[0] == '.') continue; //Ignore Hidden files and directorys
            search(pattern, file_index, fullpath(file_name, ent->d_name,  longpath));
    
        }
    }
}

int main( int argc, char *argv[] ) // a parallel version of grep -r
{
    int file_index = 1, i;
    if ( argc < 3 )
        error("Usage: search pattern file");
    for (i=2; i < argc; i++)
        search(argv[1], file_index++, argv[i]);
    pthread_exit(NULL);
    return 0;
}
