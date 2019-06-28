#include "echo.h"

int main(int argc, char **argv)
{
	int clientfd;
	char *host, *port, buf[MAXLINE];

	if (argc != 3) {
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = argv[2];

	clientfd = open_clientfd(host, port);

	memset(buf, 0, MAXLINE);
	while (fgets(buf, MAXLINE, stdin) != NULL){
		write(clientfd, buf, strlen(buf));
		memset(buf, 0, MAXLINE);
		read(clientfd, buf, MAXLINE);
		fputs(buf, stdout);
		memset(buf, 0, MAXLINE);
	}
	close(clientfd);
	exit(0);
}
