#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void){

	struct stat status;

	char *pathname = "./stat";
	stat(pathname,&status);

	printf("type:%d\n", S_ISREG(status.st_mode));

	printf("st_dev:%lu\n",status.st_dev);
	printf("st_ino:%lu\n",status.st_ino);
	printf("st_mode:%u\n",status.st_mode);
	printf("st_nlink:%lu\n",status.st_nlink);
	printf("st_uid:%u\n",status.st_uid);
	printf("st_gid:%u\n",status.st_gid);
	printf("st_rdev:%lu\n",status.st_rdev);
	printf("st_size:%ld\n",status.st_size);
	printf("st_blksize:%ld\n",status.st_blksize);
	printf("st_blocks:%ld\n",status.st_blocks);
	printf("st_atime:%ld\n",status.st_atime);
	printf("st_mtime:%ld\n",status.st_mtime);
	printf("st_ctime:%ld\n",status.st_ctime);
	return 0;
}
