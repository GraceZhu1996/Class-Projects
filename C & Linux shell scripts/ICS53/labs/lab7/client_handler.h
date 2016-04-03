#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdlib.h>
#include <memory.h>


#define MAX 31
typedef struct Clients{
    int socketfd;
    char username[80];
} Client;

void setArray(Client client[]);
int addClient(int socketfd, char *username, int *size);
int removeClient(int socketfd, int *size);
void cleanUp();
