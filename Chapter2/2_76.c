#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void* calloc(size_t nmemb, size_t size){
	void* res = NULL;
	size_t len = nmemb*size;
	// printf("len:0x%p\n", len);
	bool isMultiply_ok = !(len < nmemb || len < size);
	// printf("isMultiply_ok:%d\n",isMultiply_ok ? 1 : 0);
	if(nmemb != 0 && size != 0 && isMultiply_ok){
		res = malloc(len);
		// printf("res:0x%p\n", res);
		if(res != NULL){
			memset(res,0,len);
		}
	}
	return res;
}

int main(void){
	size_t nmemb = -1;
	size_t size = -1;
	void *p = calloc(nmemb,size);
	printf("pAddress:0x%p\n", p);
	if(p != NULL){
		printf("value:%u\n", *((int*)p));
	}
	return 0;
}