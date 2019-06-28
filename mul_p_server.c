#include "echo.h"

void sigchld_handler(int sig)
{
	while (waitpid(-1, 0, WNOHANG) > 0)
		;
	return;
}

int main(int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	pid_t repid;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
	}

	signal(SIGCHLD, sigchld_handler);
	listenfd = open_listenfd(argv[1]);
	while (1) {
		clientlen = sizeof(struct sockaddr_storage);
		connfd = accept(listenfd, (struct sockaddr *) &clientaddr, &clientlen);
		repid = fork();
		if (repid == 0) {
			close(listenfd);
			echo(connfd);
			close(connfd);
			exit(0);
		}
		if (repid > 0) {
			printf("create child: %d\n", repid);
		}
		close(connfd);
	}
}
