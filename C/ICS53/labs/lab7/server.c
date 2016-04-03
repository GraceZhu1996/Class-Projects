
#include "client_handler.h"
#define PORT 1130
#define BACKLOG 10
#define MAX_ 300

static Client clients[MAX];
static int size = 0;

struct sockaddr_in server_addr, client_addr;

void broadcastAll(char *message, int except){
    int i = 0;
    for (i = 0; i < size; i++){
        if ( clients[i].socketfd != except)
            send(clients[i].socketfd, message, strlen(message), 0);
    }
}

void *handle_client(void *socket){
    int sock = *(int*) socket;
    char buffer[MAX_];
    write(sock, "Enter Username: ", 17);
    bzero(buffer, MAX_);
    int l = read(sock, buffer, MAX_);
    if (l < 0 ){
       perror("Error reading from socket");
       exit(1);
    }
    buffer[MAX_] = '\0';
    addClient(sock, buffer, &size);
    printf("Status %s has joined. Number of chatters: %d\n", buffer, size);
    strcat(buffer, " has joined the room.\n");
    broadcastAll(buffer, sock);
    while(1){
        bzero(buffer, MAX_);
        l = recv(sock, buffer, MAX_-1, 0);
        buffer[MAX_] = '\0';
        if (l < 0 ){
            perror("Error recving from socket");
            exit(1);
        }else{
            broadcastAll(buffer, sock);
        }
    }
    free(socket);
}

int main(){
    int max_clients = 30, client_sockets[30];
    char *users[30];
    int activity, i, valread, sd, max_sd;
    int opt = 1;
    int socketfd, nsocketfd, *newsocket;
    int sin_size; 
    char buffer[MAX_];
    setArray(clients);
    fd_set readfds;

    for(i = 0; i < max_clients; i++)
        client_sockets[i] = 0;

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Creating socket error.");
        exit(1);
    }
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) < 0){
        perror("setsockopt");
        exit(1);
    }

    bzero((char*) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    memset(&(server_addr.sin_zero), 0, 8);

    if (bind(socketfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
        perror("Binding Error.");
        exit(1);
    }
    if (listen(socketfd, BACKLOG) == -1){
        perror("Listen Error");
        exit(1);
    }
    sin_size = sizeof(client_addr);
    printf("Waiting for Clients...\n"); 
    while(1){
        FD_ZERO(&readfds);
        FD_SET(socketfd, &readfds);
        max_sd = socketfd;
        for (i=0; i < max_clients; i++)
        {
            sd = client_sockets[i];
            if(sd > 0)
                FD_SET(sd, &readfds);

            if(sd > max_sd)
                max_sd = sd;
        }
        activity = select( max_sd +1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR))
            printf("select error");

        if (FD_ISSET(socketfd, &readfds))
        {
            if ((nsocketfd = accept(socketfd, (struct sockaddr*) &client_addr, (socklen_t *) &sin_size)) == -1){
            perror("Accept Error.");
            exit(1);
        }else{
            printf("Client connected. Waiting for username...\n");
        }
            if (send(nsocketfd, "Enter username: ", 17, 0) < 0)
                perror("send");
            char username[80];
            recv(nsocketfd, username, 80, 0);
            username[80] = '\0';
            for (i = 0; i < max_clients; i++)
            {
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = nsocketfd;
                    users[i] = username;
                    printf("Added new user.\n");
                    break;
                }
            }
        }
    
        for (i = 0; i < max_clients; i++)
        {
            sd = client_sockets[i];
            if (FD_ISSET(sd, &readfds))
            {
                if((valread = read(sd, buffer, MAX_)) == 0) {
                    getpeername(sd, (struct sockaddr*) &client_addr, (socklen_t*) &sin_size);
                    printf("SOmeone Disconnected.");
                        //printf("Host %s disconnected\n", inet_ntoa(client_addr.sin_addr));
                    close(sd);
                    client_sockets[i] = 0;
                }else{
                    buffer[strlen(buffer)] = '\0';
                    if (strlen(buffer) > 0){
                        int j;
                        printf("New message from %s\n", users[i]);

                        for (j=0;j < max_clients; j++){
                            if (client_sockets[j] != 0 && client_sockets[j] != client_sockets[i]){
                            //char message[400];
                            //strcat(message, users[j]);
                            //strcat(message, ": ");
                            //strcat(message, buffer);
                                send(client_sockets[j], buffer, strlen(buffer), 0);
                            }else if( client_sockets[j] == client_sockets[i]){
                                send(client_sockets[i], "Message sent.", 14, 0);
                            }
                        }
                        memset(buffer, 0, MAX_);
                    }
                }
            }
        }
    }
    return 0;
}
