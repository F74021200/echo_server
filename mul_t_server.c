#include "mul_t.h"

int rmnN = 300;
pthread_mutex_t lock;

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

	if(pthread_mutex_init(&lock, NULL) != 0){
		printf("\n mutex init fail\n");
		exit(-1);
	}

	while (1) {
		clientlen = sizeof(struct sockaddr_storage);
		if (!(connfdp = malloc(sizeof(int)))){
			fprintf(stderr, "Error: malloc error\n");
			return -1;
		}
		*connfdp = Accept(listenfd, (struct sockaddr *) &clientaddr,\
								&clientlen);
		if (pthread_create(&tid, NULL, thread, connfdp) != 0) {
			fprintf(stderr, "Error: thread-create error\n");
			return -1;
		}
	}
	pthread_mutex_destroy(&lock);
}
