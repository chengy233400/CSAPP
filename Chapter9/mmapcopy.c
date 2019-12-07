#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/mman.h>

int main(void){

	int fd = open("./test.txt",O_RDWR);
	if(fd == -1){
		printf("error\n");
		return -1;
	}
	

	size_t size = lseek(fd, 0, SEEK_END);
	int len = size/sizeof(char);
	if(size == -1){
		printf("%s\n", strerror(errno));
		return -1;
	}

	printf("reading:%d size:%ld\n",fd,size);

	void *buf = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	char *p = (char*)buf;

	printf("before modify:%c\n", p[25]);
	p[25] = (p[25] + 1 - 'a')%26 + 'a';
	printf("after modify:%c\n", p[25]);

	// pause();

	int resStatus = munmap(buf,size);
	if(resStatus == -1){
		printf("munmap error\n");
	}

	fd = close(fd);
	if(fd == 0){
		printf("successfully closed\n");
	}else{
		printf("fail to close\n");
	}
	return 0;
}