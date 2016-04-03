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

#define PORT 7945
#define BACKLOG 10
#define MAX_ 10000


struct sockaddr_in server_addr, client_addr;

//Parse args string into string array
int parseArgs(char *commands[], char args[], int i ){
    char *token = strtok(args, " ");
    commands[i++] = token;
    while((token = strtok(NULL, " ")) != NULL){
        commands[i++] = token;
    }
    return i;
}

//Execute ls -l on arguments while redirecting output to socket
void execToFD(char arg[], int sockfd, char *envp[]){
    int child = fork();
    int output = dup(1);
    char *command[10];
    command[0] = "ls";
    command[1] = "-l";
    int i = parseArgs(command, arg, 2);
    command[i] = NULL;
    switch(child){
        case 0:
            if ((dup2(sockfd, STDOUT_FILENO)) != -1){
                close(sockfd);
                execvpe(command[0], command, envp);
                perror("ls -l");
                exit(1);
            }else{ perror("dup2"); }
            exit(0);
        case -1:
            perror("fork()");
            exit(1);
        default:
            close(sockfd);
            waitpid(child, NULL, 0);
            dup2(output, STDOUT_FILENO);
            close(output);
    }

}

int main(int argc, char *argv[], char *envp[]){
    int max_clients = 30, client_sockets[30];
    int activity, i, valread, sd, max_sd;
    int opt = 1;
    int socketfd, nsocketfd, *newsocket;
    int sin_size; 
    char buffer[MAX_];
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
    printf("Waiting for Clients and Jobs...\n"); 
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
            printf("New client connected. Accepting jobs.\n");
        }
            for (i = 0; i < max_clients; i++)
            {
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = nsocketfd;
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
                    printf("Someone Disconnected.");
                    //printf("Host %s disconnected\n", inet_ntoa(client_addr.sin_addr));
                    close(sd);
                    client_sockets[i] = 0;
                }else{
                    buffer[strlen(buffer)] = '\0';
                    if (strlen(buffer) > 0){
                        printf("Received Job[%d]: ls -l %s\n", sd, buffer);
                        execToFD(buffer, sd, envp);
                        memset(buffer, 0, MAX_);
                        printf("Finished Job[%d]: ls -l %s", sd, buffer);
                    }
                }
            }
        }
    }
    return 0;
}
