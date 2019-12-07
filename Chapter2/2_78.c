#include <stdio.h>

extern int divide_power2(int x,int k);
extern int mul3div4(int x);
extern int threefouths(int x);

int divide_power2(int x,int k){
	int res = (x<0 ? (x+(1<<k)-1) : x) >> k;
	return res;
}

int mul3div4(int x){
	int halfX = divide_power2(x,1);
	int res = halfX>>1;
	res += halfX;
	return res;
}

int threefouths(int x){
	int tempB = 3*(x&3);
	tempB = ((x>>(sizeof(int)-1)) && (tempB & 3)) + (tempB>>2);
	return 3*(x>>2) + tempB;
}
int main(void){

	printf("%d\n", divide_power2(100,2));
	printf("%d\n", mul3div4(-10));
	printf("%d\n", 0x80000000);
	printf("%d\n", threefouths(0x80000000));
	return 0;
}