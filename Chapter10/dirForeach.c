#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>

int main(void){

	char *pathname = "/mnt/d/CSAPP/";

	DIR* dirptr = opendir(pathname);

	if(dirptr == NULL){
		printf("error");
		exit(-1);
	}

	printf("\t\tino\ttype\tpathname\n");

	errno = 0;

	struct dirent *dir = NULL;
	while((dir = readdir(dirptr)) != NULL){
		printf("%19ld\t%d\t%s\n", dir->d_ino,dir->d_type,dir->d_name);
		
	}

	if(errno != 0){
		printf("error on read\n");
		exit(-1);
	}

	closedir(dirptr);
	return 0;
}