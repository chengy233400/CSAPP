#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

typedef long long typeForReplace;

extern void show_bytes(void *p,size_t bytes);
#define show_int(num_int) show_bytes(&num_int,sizeof(int))
#define show_float(num_float) show_bytes(&num_float,sizeof(float))
#define show_pointer(pointer) show_bytes(&pointer,sizeof(void*))
#define show_short(num_short) show_bytes(&num_short,sizeof(short))
#define show_long(num_long) show_bytes(&num_long,sizeof(long))
#define show_longlong(num_longlong) show_bytes(&num_longlong,sizeof(long long))
#define show_double(num_double) show_bytes(&num_double,sizeof(double));

extern bool is_little_endian();
extern typeForReplace leastByteReplace(typeForReplace x,typeForReplace y);
extern unsigned replace_byte(unsigned x,unsigned int i,unsigned char b);

#define anyIsOne(x) (!~x)
#define anyIsZero(x) (!x)
#define anyOfLeastIsOne(x) (!((~x)<<(((sizeof(x)-1)<<3))))
#define anyOfMostIsZero(x) (!((x>>((sizeof(x)-1)<<3))&0xFF))

#define int_shifts_are_arithmetic() (!((-1>>1)+1))

extern unsigned srl(unsigned x, int k);
extern int sra(int x, int k);

#define any_odd_one(x) (!(~((x&0xAAAAAAAA)|0x55555555)))

extern int odd_ones(unsigned x);
extern int leftmost_one(unsigned x);

extern int int_size_is_32();
extern int lower_one_mask(int n);
extern unsigned rotate_left(unsigned x,int n);
extern int fits_bits(int x,int n);

typedef unsigned packed_t;
extern int xbyte(packed_t word,int bytenum);
extern void copy_int(int val, void *buf, size_t maxbytes);
extern int saturating_add(int x,int y);

extern int tsub_ok(int x, int y);

typeForReplace leastByteReplace(typeForReplace x,typeForReplace y){
	//to adjust any word-size machine
	x = (~(x&0xFF))&0xFF;
	y = y | 0xFF;
	return x^y;
}

void show_bytes(void *p,size_t bytes){
	printf("%d bytes:0x",bytes);
	for(size_t i = 0;i < bytes;i++){
		printf("%.2X",((unsigned char *)p)[i]);//what about [signed char]
	}
	printf("\n");
}

bool is_little_endian(){
	const int num = 0x1;
	return (&num)[0];
}

unsigned replace_byte(unsigned x,unsigned int i,unsigned char b){
	unsigned char *p = (unsigned char *)(&x);
	unsigned int index = is_little_endian() ? i : (sizeof(x) - 1 - i);
	if(i >= 0 && i < sizeof(x)) p[index] = b;//avoid index overflow
	return *(unsigned*)(p);
}

unsigned srl(unsigned x, int k){
	/* Perform shift arithmetically */
	unsigned xsra = (int)x>>k;
	xsra &= (2<<((sizeof(int)<<3)-k-1))-1;
	return xsra;
}

int sra(int x, int k){
	/* Perform shift logically */
	int xsrl = (unsigned)x>>k;
	if(x<0) xsrl |= ((2<<(k-1))-1)<<((sizeof(int)<<3)-k);
	return xsrl;
}

int odd_ones(unsigned x){
	int odd = 0;
	const unsigned table[] = {
		0,1,1,2,
		1,2,2,3,
		1,2,2,3,
		2,3,3,4,
	};
	while(x != 0){
		odd += table[x&0xF];
		x >>= 4;/* logically right shift */
	}
	return odd & 0x1;
}

int leftmost_one(unsigned x){
	 x |= x>>1;
	 x |= x>>2;
	 x |= x>>4;
	 x |= x>>8;
	 x |= x>>16;
	 return x^(x>>1);
}

int int_size_is_32(){
	int tmp = -1;
	tmp <<= 15;
	tmp <<= 15;
	tmp <<= 1;
	return tmp < 0 && !(tmp<<1);
}

int lower_one_mask(int n){
	const size_t w = sizeof(int)<<3;
	int x = 0;
	if(n >= 1 && n <= w){
		x = -1;
		x = (unsigned)(x)>>(w-n);
	} 
	return x;
}

unsigned rotate_left(unsigned x,int n){
	const size_t w = sizeof(x)<<3;
	unsigned x_left = (n > 0 && n < w) ? x >> (w-n) : 0;
	return (x<<n)^x_left;
}

int fits_bits(int x,int n){
	const size_t w = sizeof(x)<<3;
	int y = -1<<n;
	y = (x^y) >> n;/* perform right shift arithmetically */
	return y == -1 || y == 0 || n >= w;
}

int xbyte(packed_t word,int bytenum){
	const size_t size = 3;
	int res = word << ((size - bytenum)<<3);
	return res>>(size<<3);
}

void copy_int(int val, void *buf, size_t maxbytes){
	const size_t len = sizeof(val);
	if(maxbytes >= len) memcpy(buf, (void*)&val, len);
}

int saturating_add(int x,int y){
	int res = x+y;
	// do{
	// 	res = x^y;
	// 	y = (x&y)<<1;
	// 	x = res;
	// }while(y != 0);

	if(x > 0 && y > 0 && res < 0)  res = LONG_MAX;
	else if(x < 0 && y < 0 && res > 0) res = LONG_MIN;
	return res;
}

int tsub_ok(int x, int y){
	int subSum = x - y;
	return x==y || (x>y && subSum > 0) || (x<y && subSum < 0);
}

int main(void){
	printf("It is %s endian. \n", is_little_endian() ? "little" : "big");

	int a = 0xE;
	int *p = &a;
	show_bytes(&a,sizeof(a));
	show_int(a);

	show_bytes(p,sizeof(p));
	show_pointer(p);

	double d = -HUGE_VAL;
	show_double(d);

	long l = -LONG_MAX;
	show_long(l);

	short s = SHRT_MAX;
	show_short(s);

	long long x = 0x1234567889ABCDEF;
	long long y = 0x89ABCDEF76543210;
	long long res = leastByteReplace(x,y);
	show_longlong(x);
	show_longlong(y);
	show_longlong(res);

	printf("0x%p\n",replace_byte(0x12345678, 2, 0xAB));
	printf("0x%p\n",replace_byte(0x12345678, 0, 0xAB));

	x = 0x00FFFFF0;
	printf("anyIsOne:%s\n",anyIsOne(x) ? "true" : "false");
	printf("anyIsZero:%s\n",anyIsZero(x) ? "true" : "false");
	printf("anyOfLeastIsOne:%s\n",anyOfLeastIsOne(x) ? "true" : "false");
	printf("anyOfMostIsZero:%s\n",anyOfMostIsZero(x) ? "true" : "false");

	unsigned int tmp = (-1u)>>1;
	show_int(tmp);
	int z = int_shifts_are_arithmetic();	
	printf("int_shifts_are_arithmetic:%s\n",z ? "true" : "false");


	unsigned tmpX = 15;
	tmpX = srl(tmpX,3);
	show_int(tmpX);

	int tmpY = -1023;
	tmpY = sra(tmpY,3);
	show_int(tmpY);

	printf("any_odd_one:%s\n",any_odd_one(0xAAAAAAAB) ? "true" : "false");
	printf("odd_ones:%s\n",odd_ones(123456788u) ? "true" : "false");
	
	printf("leftmost_one:0x%p\n",leftmost_one(0x80000001));
	printf("int_size_is_32:%s\n",int_size_is_32() ? "true" : "false");

	int tmpZ = lower_one_mask(3);
	printf("lower_one_mask:0x%p\n",tmpZ);

	unsigned tmpA = 0x12345678;
	printf("rotate_left:0x%p\n",rotate_left(tmpA,32));
	printf("fits_bits:%s\n",fits_bits(0xEFFF,32) ? "true" : "false");
	packed_t word = 0x1234F678;
	printf("xbyte:0x%p\n", xbyte(word,0));

	long long buf = 0x0;
	size_t maxbytes = 4;
	copy_int(0xABCDEF38,(void*)&buf,maxbytes);
	show_double(buf);


	printf("saturating_add:%d\n", saturating_add(1,100));

	{
		int x = 0x80000000;
		int y = 0x1;
		printf("tsub_ok:%s,result:%d\n", tsub_ok(x,y) ? "true" : "false",x-y);
	}
	
	return 0;
}