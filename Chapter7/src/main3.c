#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int x[2] = {1,2};
int y[2] = {3,4};
int z[2];

int main(void){
	void  *handle = NULL;
	char *error = NULL;

	void (*addvec)(int *,int *,int *,int);

	handle = dlopen("../libraries_dynamic/libvector.dll", RTLD_LAZY);
	if(handle == NULL){
		printf("%s\n", dlerror());
		exit(1);
	}
	addvec = dlsym(handle,"addvec");
	error = dlerror();
	if(error != NULL){
		printf("%s\n", error);
		exit(1);
	}

	addvec(x,y,z,2);
	printf("z = [%d %d]\n", z[0],z[1]);

	if(dlclose(handle) < 0){
		printf("%s\n", dlerror());
		exit(1);
	}
	
	return 0;
}