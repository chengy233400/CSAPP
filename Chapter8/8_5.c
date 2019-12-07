#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

unsigned int snooze(unsigned int secs){
	unsigned int rc = sleep(secs);
	printf("Slept for %d of %d secs.\n", secs-rc, secs);
}

int main(int argc,const char *argv[],const char *envp[]){
	unsigned int secs = 10;
	snooze(secs);
	int res = pause();
	printf("%d\n", res);

	// for(int i = 0;i < argc;i++){
	// 	printf("%s\n", argv[i]);
	// }

	// setenv("WSLENV","lzjTenma",1);

	// for(int i = 0;envp[i] != NULL;i++){
	// 	printf("%s\n", envp[i]);
	// }
	return 0;
}