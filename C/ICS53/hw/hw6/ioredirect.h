#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>


#define STDIN_ 0
#define STDOUT_ 1
#define STDERR_ 2


int switchInput(char *filename);
int switchOutput(char *filename);
int switchInputFD(int fd);
int switchOutputFD(int fd);
void closeIO(int closeid, int replaceid);
void resetIO();
void resetOutput();
