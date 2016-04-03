#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdlib.h>
#include <memory.h>

#define PORT 7945
#define BACKLOG 10
#define MAX_ 300


struct sockaddr_in server_addr, client_addr;
struct dirent *ent;
struct stat statbk;

//Parse args string into string array
int parseArgs(char *commands[], char args[], int i ){
    char *token = strtok(args, " ");
    commands[i++] = token;
    while((token = strtok(NULL, " ")) != NULL){
        commands[i++] = token;
    }
    return i;
}

void error(char *e){
    perror(e);
    exit(1);
}

char* fullpath(char *dir, char *name, char buffer[]){
    strcpy(buffer, (dir == NULL) ? "" : dir);
    strcat(buffer, "/");
    strcat(buffer, name);
    return buffer;
}

void writeWait(int sock, char *message, int len){
    write(sock, message, len);
    char buffer[100];
    while(1){
        printf("Waiting...");
        fflush(stdout);
        int r = recv(sock, buffer, 100, MSG_DONTWAIT);
        if (r > 0) break;
    }
}

char* makeCurrentDir(char *name, char* newname){
    char *sep = "./";
    strcpy(newname, sep);
    strcat(newname, name);
    return newname;
}

void sendFileToFD(char *filename, int sockfd){
    int fd = open(filename, O_RDONLY);
    off_t offset = 0, size = 0;
    if (fd != -1){
        if ((fstat(fd, &statbk)) == -1) error("fstat");
        size = statbk.st_size;
        char newname[100];
        makeCurrentDir(filename, newname);
        write(sockfd, newname, strlen(newname)+1); //Send filename first
        sleep(1);
        int r = sendfile(sockfd, fd, &offset, size);
        switch(r){
            case -1: //Error
                error("sendfile");
                break;
            default:
                if (r != size){
                    fprintf(stderr, "Incomplete file transfer %d of %d bytes.\n", r, (int) size);
                    exit(1);
                }else{
                    printf("File transfer successful.\n");
                    sleep(1);
                }
        }
    }else{
        error("open");
    }
    close(fd);
}

void execToFD(char dirname[], int sockfd){
    DIR *dir; 
    char longpath[500];
    if ((dir = opendir(dirname))){ //DIR
        send(sockfd, "[create dir]", 13, 0);
        sleep(1);
        printf("Create dir %s.\n", dirname);
        char newname[100];
        makeCurrentDir(dirname, newname);
        write(sockfd, newname, strlen(newname)+1); //Send Directory name
        sleep(1);
        while((ent = readdir(dir)) != NULL){
            if (ent->d_name[0] == '.') continue;
            execToFD(fullpath(dirname, ent->d_name, longpath), sockfd);
        }
    }else{
        if (errno == ENOTDIR){ //FILE
            send(sockfd, "[incoming file]", 16, 0);
            sleep(1);
            fullpath(NULL, dirname, longpath);
            printf("create file %s\n", longpath);
            sendFileToFD(dirname, sockfd); 
        }else{
            error("opendir");
        }
    }
}

int main(int argc, char *argv[]){
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
        error("Creating socket error.");
    }
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) < 0){
        error("setsockopt");
    }

    bzero((char*) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    memset(&(server_addr.sin_zero), 0, 8);

    if (bind(socketfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
        error("Binding Error.");
    }
    if (listen(socketfd, BACKLOG) == -1){
        error("Listen Error");
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
            error("select error");
       

        if (FD_ISSET(socketfd, &readfds))
        {
            if ((nsocketfd = accept(socketfd, (struct sockaddr*) &client_addr, (socklen_t *) &sin_size)) == -1){
            error("Accept Error.");
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
                    printf("Someone Disconnected.\n");
                    //printf("Host %s disconnected\n", inet_ntoa(client_addr.sin_addr));
                    close(sd);
                    client_sockets[i] = 0;
                }else{
                    buffer[strlen(buffer)] = '\0';
                    if (strlen(buffer) > 0){
                        printf("Received Job[%d]: %s\n", sd, buffer);
                        if (fork() == 0){
                            execToFD(buffer, sd);
                            exit(1);
                        }
                        memset(buffer, 0, MAX_);
                        printf("Finished Job[%d]: %s\n", sd, buffer);
                    }
                }
            }
        }
    }
    return 0;
}
