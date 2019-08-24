#include "mul_p.h"

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

void consume(int connfd)
{
	char buf[MAXLINE];
	int rcvn = 0;

	memset(buf, 0, MAXLINE);
	while (sprintf(buf, "%d", rmnN) > 0){
		write(connfd, buf, strlen(buf));
		memset(buf, 0, MAXLINE);
		if(read(connfd, buf, MAXLINE) > 0){
			rcvn = atoi(buf);
			printf("rmnN: %d\nrecieve:%d\n", rmnN, rcvn);
			pthread_mutex_lock(&lock);
			if(rmnN - rcvn >= 0){
				sleep(1);
				rmnN = rmnN - rcvn;
			}
			pthread_mutex_unlock(&lock);
		}
		if(rmnN < 0){
			printf("\nrmnN: %d\n", rmnN);
			exit(-1);
		}
		else if(rmnN == 0)
			rmnN = 300;
	}
}
