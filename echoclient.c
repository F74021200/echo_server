#include "echo.h"

int main(int argc, char **argv)
{
	int clientfd;
	char *host, *port;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = argv[2];

	clientfd = open_clientfd(host, port);
	cl_echo(clientfd);

	close(clientfd);
	exit(0);
}
