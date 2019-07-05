#include "echo.h"

void *thread(void *vargp);

int main(int argc, char **argv)
{
	int listenfd, *connfdp;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	pthread_t tid;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	if ((listenfd = open_listenfd(argv[1])) < 0) {
		fprintf(stderr, "Error: listenfd-open error\n");
		return -1;
	}

	while (1) {
		clientlen = sizeof(struct sockaddr_storage);
		if (!(connfdp = malloc(sizeof(int)))){
			fprintf(stderr, "Error: malloc error\n");
			return -1;
		}
		if (!(*connfdp = accept(listenfd, (struct sockaddr *) &clientaddr,\
								&clientlen))) {
			fprintf(stderr, "Error: accept error, %d\n", *connfdp);
			return -1;
		}
		if (pthread_create(&tid, NULL, thread, connfdp) != 0) {
			fprintf(stderr, "Error: thread-create error\n");
			return -1;
		}
	}
}

void *thread(void *vargp)
{
	int connfd = *((int *)vargp);
	if (pthread_detach(pthread_self()) != 0) {
		fprintf(stderr, "Error: thread-detach error\n");
		return NULL;
	}
	free(vargp);
	echo(connfd);
	return NULL;
}
