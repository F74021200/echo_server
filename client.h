#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAXLINE 1024

int open_clientfd(char *hostname, char *port);
void cl_echo(int connfd);
void cl_consume(int connfd);
