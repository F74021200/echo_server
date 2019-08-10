#include "client.h"

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

void cl_echo(int clientfd)
{
	char buf[MAXLINE];
	int n = 0; //n is the number of communication.

	memset(buf, 0, MAXLINE);
	while (sprintf(buf, "client %d\n", n++)){
		write(clientfd, buf, strlen(buf));
		memset(buf, 0, MAXLINE);
		read(clientfd, buf, MAXLINE);
		fputs(buf, stdout);
		memset(buf, 0, MAXLINE);
	}
}

void cl_consume(int clientfd)
{
	char buf[MAXLINE];
	int rmnn = 0, cnsmn = 0;

	memset(buf, 0, MAXLINE);
	while (read(clientfd, buf, MAXLINE) > 0){
		rmnn = atoi(buf);
		srand(time(NULL));
		cnsmn = rand() % 10;
		printf("receive: %d\nsend: %d\n", rmnn, cnsmn);
		memset(buf, 0, MAXLINE);
		sprintf(buf, "%d", cnsmn);
		write(clientfd, buf, MAXLINE);
	}
}
