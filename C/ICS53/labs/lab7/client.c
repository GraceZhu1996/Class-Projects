#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

// the port client will be connecting to
#define PORT 1130   
// max number of bytes we can get at once
#define MAXDATASIZE 300

void receive_message(int sock){ 
    char buffer[MAXDATASIZE];
    int i;
    i = recv(sock, buffer, MAXDATASIZE, 0);
    if (i < 0){
        perror("Error reading in receive.");
        exit(1);
    }
    buffer[strlen(buffer)] = '\0';
    printf("%s\n", buffer);
    
}

void send_message(int sock){
    char buffer[MAXDATASIZE];
    int i;
    while(1){
       // printf("Enter message: ");
        //scanf(" %[^\n]%*c", &buffer);
        scanf("%s", &buffer);
        buffer[MAXDATASIZE] = '\0';
        write(sock, buffer, MAXDATASIZE);
        receive_message(sock);
    }

}


int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    // connector’s address information
    struct sockaddr_in their_addr;
     
    // if no command line argument supplied
    if(argc != 2)
    {
        fprintf(stderr, "Client-Usage: %s the_client_hostname\n", argv[0]);
        // just exit
        exit(1);
    }
     
    // get the host info
    if((he=gethostbyname(argv[1])) == NULL)
    {
        perror("gethostbyname()");
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
     
    // host byte order
    their_addr.sin_family = AF_INET;
    // short, network byte order
    printf("Server-Using %s and port %d...\n", argv[1], PORT);
    their_addr.sin_port = htons(PORT);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    // zero the rest of the struct
    memset(&(their_addr.sin_zero), '\0', 8);
     
    if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect()");
        exit(1);
    }
    else
        printf("Client- connect() is OK...\n");
     
    if((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
    {
        perror("recv()");
        exit(1);
    }
    else
        printf("Client-The recv() is OK...\n");
    
    char username[80];
    buf[numbytes] = '\0';
    printf("%s", buf);
    scanf(" %[^\n]%*c", &username);
    username[80] = '\0';
    send(sockfd, username, 80, 0);
    
    send_message(sockfd);
    
    return 0;
}
