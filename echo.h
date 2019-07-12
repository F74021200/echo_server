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

int open_clientfd(char *hostname, char *port)
{
	int clientfd;
	struct addrinfo hints, *listp, *p;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;
	hints.ai_flags |= AI_ADDRCONFIG;
	getaddrinfo(hostname, port, &hints, &listp);

	for (p = listp; p; p = p->ai_next) {
		if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
				continue;
		if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
				break;
		close(clientfd);
	}

	freeaddrinfo(listp);
	if (!p)
			return -1;
	else
			return clientfd;
}

int open_listenfd(char *port)
{
	struct addrinfo hints, *listp, *p;
	int listenfd, optval = 1;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
	hints.ai_flags |= AI_NUMERICSERV;
	getaddrinfo(NULL, port, &hints, &listp);

	for (p = listp; p; p = p->ai_next) {
		if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
				continue;

		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, \
				   (const void *)&optval, sizeof(int));

		if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
				break;
		close(listenfd);
	}

	freeaddrinfo(listp);
	if (!p)
			return -1;

	if (listen(listenfd, LISTENQ) < 0) {
		close(listenfd);
		return -1;
	}
	return listenfd;
}

void echo(int connfd)
{
	 size_t n;
	 char buf[MAXLINE], send_buf[MAXLINE];

	memset(buf, 0, MAXLINE);
	 while((n = read(connfd, buf, MAXLINE)) != 0) {
		printf("server receive %d bytes\n", (int)n);
		printf("buf: %s\n", buf);
		memset(send_buf, 0, MAXLINE);
		sprintf(send_buf, "server recieved %s", buf);
		write(connfd, send_buf, strlen(send_buf));
		memset(buf, 0, MAXLINE);
	 }
}

int Accept (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int retfd;

	retfd = accept(sockfd, addr, addrlen);
	if (retfd > 0) return retfd;
	else{
		fprintf(stderr, "Error: accept error\n");
		exit(0);
	}
}
