#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define decmialLen 10
// static const int decmialLen = 10;//进制

void printNumArray(const int *arr,const int len,const int w){
	int x = 0;
	/* print from the largest one because the generator generates number from larger to smaller */
	for(int i = len-1; i > 0 ;i--){
	// for(int i = 0;i < len;i++){
		int temp = arr[i];
		if(temp != 0){
			for(int k = 0;k < temp;k++){
				printf("%d", i);
				x++;
			}
		}
	}
	/* fill in zero */
	for(;x<w;x++){
		printf("%d", 0);
	}
	printf("\n");
}

void printSelected_arrayFormat(const int *selected,const int w,const int len){
	printf("[");
	for(int i = 0;i < len;i++){
		printf("%d", selected[i]);
		if(i != len - 1){
			printf(",");
		}
	}
	printf("] ");
}


void generator_noniteration(const int w){
	int numArr[decmialLen+1] = {0};
	numArr[0] = w;
	do{
		printNumArray(numArr,decmialLen,w);
		// printSelected_arrayFormat(numArr,w,decmialLen);
		// printf("\n");
		// printf("rest:%d,cIndex:%d\n", rest, cIndex);
		if(numArr[0] == 0){
			int pIndex = 1;
			for(;pIndex < decmialLen;pIndex++){
				if(numArr[pIndex] != 0) break;
			}

			numArr[pIndex] = 0;
			numArr[++pIndex]++;
			int sumLeft = 0;
			for(int i = pIndex;i < decmialLen;i++){
				sumLeft += numArr[i];
			}
			numArr[0] = w-sumLeft+1;
			numArr[1] = -1;
		}
		numArr[0]--;
		numArr[1]++;

	}while(numArr[decmialLen] == 0);
}

int main(void){
	generator(3);
	return 0;
}