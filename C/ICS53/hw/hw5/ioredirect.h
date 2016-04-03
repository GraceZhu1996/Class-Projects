#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>


#define STDIN_ 0
#define STDOUT_ 1
#define STDERR_ 2


int switchInput(char *filename);
int switchOutput(char *filename);
void closeIO(int closeid, int replaceid);
void resetIO();
