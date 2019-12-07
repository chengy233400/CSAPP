#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
static unsigned a = 0;

void sigint_handler(int sig){
	printf("%dCaught SIGINT:%u\n",sig,a);
	kill(getpid(),SIGCONT);
	printf("final_i:%u\n", a++);
}
void sigcont_handler(int sig){
	printf("%dCaught SIGCONT:%u\n",sig,a++);
}
int main(void){
	printf("pid:%d\n", getpid());
	if(signal(SIGINT,sigint_handler) == SIG_ERR){
		printf("unix error\n");
		exit(-1);
	}
	if(signal(SIGCONT,sigcont_handler) == SIG_ERR){
		printf("unix error\n");
		exit(-1);
	}
	pause();
	printf("final:%u\n", a++);
	return 0;
}