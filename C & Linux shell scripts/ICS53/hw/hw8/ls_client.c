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
#define PORT 7945
// max number of bytes we can get at once
#define MAXDATASIZE 10000


//Receive message, and send to stdout
void receive_message(int sock){ 
    char buffer[MAXDATASIZE];
    while ((recv(sock, buffer, MAXDATASIZE, 0)) > 0){
        buffer[strlen(buffer)] = '\0';
        printf("%s\n", buffer);
    }
    
}



int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in their_addr;
     
    if(argc < 3)
    {
        fprintf(stderr, "Client-Usage: %s the_client_hostname file(s)/folder(s)\n", argv[0]);
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
     
    //Contruct jobs string and send to server
    int i;
    char jobs[1000];
    for (i=2; i < argc; i++){
        strcat(jobs, argv[i]);
        strcat(jobs, " ");
    }
    printf("Sending job: %s\n", jobs);
    write(sockfd, jobs, strlen(jobs));
    receive_message(sockfd);
    close(sockfd);
    
    return 0;
}
