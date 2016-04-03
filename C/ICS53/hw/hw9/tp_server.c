#include <sys/types.h>
#include <signal.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

#define BACKLOG 200
// if more than BACKLOG clients in the server accept queue, client connect will fail
#define MAXTHREADS 5
int t_count = 0;
void error(char *msg)
{
    fprintf(stderr, "ERROR: %s failed\n", msg);
    exit(-1);
}


struct sockaddr_in make_server_addr(short port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    return addr;
}

int create_server_socket(short port)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    int optval = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
    struct sockaddr_in my_addr = make_server_addr(port);
    if ( s == -1 )
        error("socket()");
    bind(s, (struct sockaddr*)&my_addr, sizeof my_addr);
    listen(s, BACKLOG);
    return s;
}

void get_file_request(int socket, char *fileName)
{
    char buf[BUFSIZ];
    int n = read(socket, buf, BUFSIZ);
    if ( n < 0 )
        error("read from socket");
    buf[n] = '\0';
    strcpy(fileName, buf);
    printf("Server got file name of '%s'\n", fileName);
}

void write_file_to_client_socket(char *file, int socket)
{
    char buf[BUFSIZ];
    int n;
    int ifd = open(file, O_RDONLY);
    if ( ifd == -1 )
        error("open()");
    while ( (n = read(ifd, buf, BUFSIZ)) > 0 )
        write(socket, buf, n);
    close(ifd);
}

typedef struct{
    int client_socket;
    int *thread_status;
}arg_struct;

void *handle_request(void *args)
{
    arg_struct *real_args =  args;
    char fileName[BUFSIZ];
    int client_socket = real_args->client_socket;
    get_file_request(client_socket, fileName);
    write_file_to_client_socket(fileName, client_socket);
    close(client_socket);
    *(real_args->thread_status) = 0; //Change status to ready.
    free(real_args);
    pthread_exit(NULL);
}

void time_out(int arg)
{
    fprintf(stderr,  "Server timed out\n");
    exit(0);
}

void set_time_out(int seconds)
{
    struct itimerval value = {0};
    value.it_value.tv_sec = seconds;
    setitimer(ITIMER_REAL, &value, NULL);
    signal(SIGALRM, time_out);
}


void accept_client_requests(int server_socket)
{
    int client_socket, r, t = 0;
    struct sockaddr_in client_addr;
    socklen_t sin_size = sizeof client_addr;
    set_time_out(5);
    pthread_t threads[MAXTHREADS];
    int thread_status[MAXTHREADS];
    memset(thread_status, 0, MAXTHREADS);
    while ( (client_socket =
            accept(server_socket, (struct sockaddr*)&client_addr, &sin_size)) > 0 )
    {
        while (t < MAXTHREADS){ //Cycle through thread_statuses till one is free;
            printf("Trying t=%d\n", t);
            if (thread_status[t] == 0) break;
            printf("Thread %d is busy.\n", t);
            t = (t == MAXTHREADS-1) ? 0 : t+1;
        }

        arg_struct *args = malloc(sizeof(*args));
        args->client_socket = client_socket;
        args->thread_status = &thread_status[t];
        printf("TP: [%d] using Thread #%d.\n", t_count++, t);
        set_time_out(5);
        r = pthread_create(&threads[t], NULL, handle_request, args);
        thread_status[t++] = 1;
        if (r != 0){
            free(args);
            error("pthread_create()");
        }
    }
}

/*
   Note, I put in a 5 second time out so you don't leave servers running.
*/

int main(int argc, char *argv[])
{
    if ( argc != 2 )
        error("usage: server port");
    short port = atoi(argv[1]);
    int server_socket = create_server_socket(port);
    accept_client_requests(server_socket);
    shutdown(server_socket, 2);
    pthread_exit(NULL);
    return 0;
}
