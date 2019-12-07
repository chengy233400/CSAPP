#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void){
	int x = 1;

	pid_t pid;
	pid = fork();

	if(pid < 0){
		fprintf(stderr, "fork error:%s\n", strerror(errno));
		exit(-1);
	}

	pid = fork();

	if(pid < 0){
		fprintf(stderr, "fork error:%s\n", strerror(errno));
		exit(-1);
	}


	// if(pid == 0){
	// 	/* child */
	// 	write(1,"child_x:",9);
	// 	printf("%d\n", ++x);

	// 	exit(0);
	// }
	printf("pid:%d_x:%d\n", getpid(),--x);

	exit(0);
	// printf("pid=%d\n", getppid());
}