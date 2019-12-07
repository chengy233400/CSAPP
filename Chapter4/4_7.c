#include <stdio.h>

extern int checkRspValue();

int main(void){
	int isSame = checkRspValue();
	printf("%s\n", isSame == 1 ? "true" : "false");	

	return 0;
}