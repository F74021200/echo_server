#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define MAXLINE 1024
#define LISTENQ 1024

int open_clientfd(char *hostname, char *port);
int open_listenfd(char *port);
void echo(int connfd);
int Accept (int, struct sockaddr *, socklen_t *);
