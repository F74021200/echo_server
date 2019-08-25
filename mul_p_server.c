#include "mul_p.h"

int main(int argc, char **argv)
{
	int listenfd, connfd, shmid;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	pid_t repid;
	int *n, *shm;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
	}

	if ((shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) < 0){
		fprintf(stderr, "shnget error\n");
		exit(-1);
	}
	if ((shm = shmat(shmid, NULL, 0)) == (int *) - 1){
		fprintf(stderr, "shmat error\n");
		exit(-1);
	}

	n = shm;
	*n = 300;

	signal(SIGCHLD, sigchld_handler);
	listenfd = open_listenfd(argv[1]);
	while (1) {
		clientlen = sizeof(struct sockaddr_storage);
		connfd = Accept(listenfd, (struct sockaddr *) &clientaddr, &clientlen);
		repid = fork();
		if (repid == 0) {
			close(listenfd);
			consume(connfd, n);
			close(connfd);
			exit(0);
		}
		if (repid > 0) {
			printf("create child: %d\n", repid);
		}
		close(connfd);
		if (shmctl(shmid, IPC_RMID, 0) == -1){
			fprintf(stderr, "shmctl error\n");
			exit(-1);
		}
	}
}
