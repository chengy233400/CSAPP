
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10
int main(void){
	
	pid_t pid[N];
	for(int i = 0;i < N;i++){
		pid[i] = fork();
		if(pid[i] < 0){
			fprintf(stderr, "fork error:%s\n", strerror(errno));
			/* reap other proccesses that have been forked */
			// waitpid(-1,NULL,0);
			// break;
		}else if(pid[i] == 0){
			/* child */
			printf("i:%d child_pid:%d running\n", i,getpid());
			exit(100+i);
		}

	}

	int status;
	int i = 0;
	pid_t retpid;
	while((retpid = waitpid(pid[i++],&status,0)) > 0){
		if(WIFEXITED(status)){
			printf("child terminated normally, pid:%d exit status:%d\n", retpid, WEXITSTATUS(status));
		}else{
			printf("child terminated abnormally, pid:%d\n", retpid);
		}
	}

	if(errno != ECHILD){
		printf("waitpid error:%s\n", strerror(errno));
	}


	return 0;
}