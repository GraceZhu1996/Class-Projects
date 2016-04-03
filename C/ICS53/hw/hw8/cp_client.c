#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>

// the port client will be connecting to
#define PORT 7945
// max number of bytes we can get at once
#define MAXDATASIZE 500 

struct stat statbk;

char *create_file = "[incoming file]";
char *create_dir = "[create dir]";
void createFile(int sock){
    char filename[80], buffer[MAXDATASIZE];
    read(sock, filename, sizeof(filename));
    int s = strlen(filename);
    filename[s] = '\0';
    sleep(1);
    int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd != 0){
        printf("Creating %s...\n", filename);
        while(1){
            int r = recv(sock, buffer, MAXDATASIZE, MSG_DONTWAIT);
            if (r > 0)
            {
                buffer[r] = '\0';
                write(fd, buffer, r);
            }else{
                printf("Created file: %s.\n", filename);
                sleep(1);
                break;
            }
        }
    }
    close(fd);
}

void createDir(int sock){
    char dirname[80], buffer[MAXDATASIZE];
    read(sock, dirname, sizeof(dirname));
    sleep(1);
    if (strcmp(dirname, create_dir) == 0) read(sock, dirname, sizeof(dirname));
    int s = strlen(dirname);
    dirname[s] = '\0';
    if(stat(dirname, &statbk) == -1){
        printf("Creating dir %s.", dirname);
        int r = mkdir(dirname, 0700);
        if (r != -1){
            printf("Created Dir: %s.\n", dirname);
        }
        else
            perror("mkdir");
    }else{
        printf("Dir %s exists.\n", dirname);

    }
}

void receive_message(int sock){ 
    char buffer[MAXDATASIZE];
    recv(sock, buffer, MAXDATASIZE, 0);
    buffer[strlen(buffer)] = '\0';
    //printf("Message is: %s\n", buffer);
    if (strcmp(buffer, create_file) == 0){
        sleep(1);
        createFile(sock);
        receive_message(sock);
    }else if (strcmp(buffer, create_dir) ==0){
        sleep(1);
        createDir(sock);
        receive_message(sock);
    }else
        printf("%s\n", buffer);  
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in their_addr;
     
    if(argc < 2)
    {
        fprintf(stderr, "Client-Usage: %s the_client_hostname\n", argv[0]);
        exit(1);
    }

    if((he=gethostbyname(argv[1])) == NULL)
    {
        herror("gethostbyname()");
        exit(1);
    }
    else
        printf("Client-The remote host is: %s\n", argv[1]);
     
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket()");
        exit(1);
    }
    else
        printf("Client-The socket() sockfd is OK...\n");
     
    their_addr.sin_family = AF_INET;
    printf("Server-Using %s and port %d...\n", argv[1], PORT);
    their_addr.sin_port = htons(PORT);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(their_addr.sin_zero), '\0', 8);
     
    if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect()");
        exit(1);
    }
    else
        printf("Client- connect() is OK...\n");
     
    while(1){
        char request[100];    
        printf("Enter Request: ");
        scanf("%s", &request);
        request[strlen(request)] = '\0';
        send(sockfd, request, strlen(request)+1, 0);
        receive_message(sockfd);
        fflush(stdout);
    }
    close(sockfd);
    
    return 0;
}
