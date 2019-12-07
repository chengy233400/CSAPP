#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
int main(){
	printf("pid:%d\n", getpid());
	sigset_t mask;
	sigset_t premask;

	sigemptyset(&mask);
	sigaddset(&mask,SIGINT);


	sigprocmask(SIG_BLOCK,&mask,&premask);
	

	printf("in\n");
	pause();
	printf("out\n");

	sigprocmask(SIG_SETMASK,&premask,NULL);
	return 0;
}