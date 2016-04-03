#include "client_handler.h"
Client *clients;

void setArray(Client client[]){
    clients = client;

}

int find(int socketfd, int *size){
    int i;
    for (i=0; i < *size; i++)
        if (clients[i].socketfd == socketfd) return i;
    return -1;
}

int addClient(int socketfd, char *username, int *size){
    if (*size == MAX - 1)
        return -1;
    clients[*size].socketfd = socketfd;
    strcpy(clients[*size].username, username);
    (*size)++;
    return 0;
}
int removeClient(int socketfd, int *size){
    int index = find(socketfd, size);
}    
void cleanUp();
