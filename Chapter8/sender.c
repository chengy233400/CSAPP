#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
int main(int argc,const char *argv[]){


	int pid = atoi(argv[1]);
	int sig = atoi(argv[2]);
	printf("pid:%d\nsig:%d\n", pid,sig);
	kill(pid,sig);
	return 0;
}