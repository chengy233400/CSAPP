#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <gmp.h>

static int numPPDIs = 0;
static const int decimal = 10;
/* to store the selected number, and the length is constant decimal */
static int *selected = NULL;

/* to store the w power of root,
 * EMPHASIZE it is a two-dimension array,
 * powerRoots[decimal][w+1]
 */
static mpz_t **powerRoots = NULL;
/* to store the value of num mutiplied by the w power of root,
 * EMPHASIZE it is a two-dimension array,
 * numOf_powerRoots[decimal][w+1]
 */
static mpz_t **numOf_powerRoots = NULL;

/* to store the valude of 10^k
 * EMPHASIZE it is an array,
 * k_powerOf_10[w+1]
 */
static mpz_t *k_powerOf_10 = NULL;

static mpz_t stdOne;

void init(const int w);
void destory(const int w);

void initForEachIteration(const int w);
void destoryForEachIteration(const int w);

void printNumArray(int *arr,int len,int w);
void printArray_twoDimension(mpz_t **p,const int w);
void printPowerRoots(const int w);
void printNumOf_powerRoots(const int w);
void printSelected(int w);
void printArray(const mpz_t *p,const int len);

bool isSame(const int *selected,const int *spilt);
void getCounter(const mpz_t sum,int **spilt);

void freePoint(int **p);

bool isPPDI(const int w, const mpz_t sum);

bool preCheck(const mpz_t sum,const mpz_t max,const int cIndex,int rest,const int w);

void generator(int cIndex,int rest,const int w, const mpz_t sum);

int main(void){
	int beginW = 0;
	int endW = 0;

	printf("输入起始位数：");
	scanf("%d",&beginW);
	printf("输入结束位数：");
	scanf("%d",&endW);
	printf("\n");
	int w = endW;
	init(w);

	mpz_t sum;
	mpz_init_set_ui(sum,0);

	/* encounter costing time begin */
	double total_t;
	clock_t start_t,end_t;
	start_t = clock();

		for(int i = beginW;i <= endW;i++){
			initForEachIteration(i);
			
			generator(decimal-1,i,i,sum);

			destoryForEachIteration(i);		
		}

	end_t = clock();/* ending encounter */
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("\n\nRunning Time：%f s\n", total_t);


	mpz_clear(sum);

	destory(w);
	return 0;
}

void init(const int w){
	selected = malloc(sizeof(int)*decimal);

	for(int i = 0;i < decimal;i++){
		selected[i] = 0;
	}

	powerRoots = malloc(sizeof(mpz_t*)*decimal);
	numOf_powerRoots = malloc(sizeof(mpz_t*)*decimal);
	for (int y = 0; y < decimal; y++){
		powerRoots[y] = malloc(sizeof(mpz_t)*(w+1));
		numOf_powerRoots[y] = malloc(sizeof(mpz_t)*(w+1));
		if(y == 0) mpz_init_set_ui(powerRoots[0][0],0);
		if(y != 0) mpz_init_set_ui(powerRoots[y][0],1);
		for(int x = 1;x <= w;x++){
			mpz_init_set_ui(powerRoots[y][x],y);
			mpz_init_set_ui(numOf_powerRoots[y][x],y);
		}
	}

	/* calculate the w power of root */
	for (int y = 0; y < decimal; y++){
		/* improve performance SIMD */
		for(int x = 2;x <= w;x++){
			mpz_mul(powerRoots[y][x],powerRoots[y][x],powerRoots[y][x-1]);
		}
	}

	k_powerOf_10 = malloc(sizeof(mpz_t)*(w+1));
	for(int i = 0;i <= w;i++){
		mpz_init(k_powerOf_10[i]);
		mpz_ui_pow_ui(k_powerOf_10[i],10,i);
	}
	
	mpz_init_set_ui(stdOne,1);
}

void initForEachIteration(const int w){
	for (int y = 0; y < decimal; y++){
		for(int x = 0;x <= w;x++){
			mpz_mul_ui(numOf_powerRoots[y][x],powerRoots[y][w],x);
		}
	}
}

void destory(const int w){

	free(selected);
	selected = NULL;

	for(int y = 0;y < decimal;y++){
		free(powerRoots[y]);
		powerRoots[y] = NULL;

		free(numOf_powerRoots[y]);
		numOf_powerRoots[y] = NULL;
	}
	free(powerRoots);
	powerRoots = NULL;

	free(numOf_powerRoots);
	numOf_powerRoots = NULL;

	free(k_powerOf_10);
	k_powerOf_10 = NULL;

	mpz_clear(stdOne);
}

void destoryForEachIteration(const int w){
	for (int y = 0; y < decimal; y++){
		for(int x = 1;x <= w;x++){
			mpz_set_ui(numOf_powerRoots[y][x],y);
		}
	}
}

void printNumArray(int *arr,int len,int w){
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

void printArray_twoDimension(mpz_t **p,const int w){
	for (int y = 0; y < decimal; y++){
		for(int x = 0;x <= w;x++){
			gmp_printf("%Zd ", p[y][x]);
		}
		gmp_printf("\n");
	}
}

void printPowerRoots(const int w){
	printf("printPowerRoots:%d\n", w);
	// for (int y = 0; y < decimal; y++){
	// 	gmp_printf("%Zd\n", powerRoots[y][w]);
	// }
	printArray_twoDimension(powerRoots,w);
}

void printNumOf_powerRoots(const int w){
	printf("numOf_powerRoots:%d\n", w);
	printArray_twoDimension(numOf_powerRoots,w);
}

void printSelected(int w){
	printNumArray(selected,decimal,w);
}

void printArray(const mpz_t *p,const int len){
	for(int i = 0;i < len;i++){
		gmp_printf("%Zd ",p[i]);
	}
	printf("\n");
}

bool isSame(const int *selected,const int *spilt){
	for(int i = 0;i < decimal;i++){
		if(selected[i] != spilt[i]){
			return false;
		}
	}
	return true;
}

void getCounter(const mpz_t sum,int **spilt){
	mpz_t sum_a;
	mpz_init_set(sum_a,sum);
	*spilt = malloc(sizeof(int)*decimal);

	/* init */
	for(int i = 0;i < decimal;i++){
		(*spilt)[i] = 0;
	}

	mpz_t single;
	mpz_init_set_ui(single,0);
    while(mpz_cmp_ui(sum_a,0) > 0) {
        mpz_tdiv_qr_ui(sum_a,single,sum_a,10);
        int tempIndex = (int)mpz_get_ui(single);
        (*spilt)[tempIndex]++;
    }
    mpz_clear(single);
    mpz_clear(sum_a);
}

void freePoint(int **p){
	free(*p);
	*p = NULL;
}

bool isPPDI(const int w, const mpz_t sum){
	// printSelected(w);
	
	bool res = false;
	/* calculate the sum of the selected */
	mpz_t sum_a;/* to store the sum of the selected */
	mpz_init_set(sum_a,sum);

	/* spilt the sum_a */
	int *spilt = NULL;
	getCounter(sum_a,&spilt);

	/* compare the spilted array with the selected */
    res = isSame(selected,spilt);

    freePoint(&spilt);
	mpz_clear(sum_a);
	return res;
}

bool preCheck(const mpz_t sum,const mpz_t max,const int cIndex,int rest,const int w){

	bool res = true;
	mpz_t sum_a;
	mpz_t max_a;
	mpz_init_set(sum_a,sum);
	mpz_init_set(max_a,max);

	/* get the same */
	/* speed up */
	mpz_t gap;
	mpz_init(gap);
	mpz_sub(gap,max_a,sum_a);
	for(int i = 0;i < w;i++){
		if(mpz_cmp(gap,k_powerOf_10[i]) >= 0 && mpz_cmp(gap,k_powerOf_10[i+1]) < 0){
			mpz_tdiv_q(sum_a,sum_a,k_powerOf_10[i+1]);
			mpz_tdiv_q(max_a,max_a,k_powerOf_10[i+1]);
			break;
		}
	}

	while(mpz_cmp(sum_a,max_a) != 0){
		mpz_tdiv_q_ui(sum_a,sum_a,10);
		mpz_tdiv_q_ui(max_a,max_a,10);
	}

	/* no same part */
	if(mpz_cmp_ui(sum_a,0) == 0) goto out;

	/* has same part */
	/* spilt the part */
	int *spilt = NULL;
	getCounter(sum_a,&spilt);

	for (int i = decimal-1; i > cIndex; i--){
		if (spilt[i] > selected[i]){
			res = false;
			break;
		}
	}

	if(res){
		for (int i = 0; i <= cIndex; i++)
			rest -= spilt[i];
		res = rest >= 0;
	}
    freePoint(&spilt);

out:
	mpz_clear(sum_a);
	mpz_clear(max_a);
	return res;
}

void printSelected_arrayFormat(const int *selected,const int w,const int len){
	printf("[");
	for(int i = 0;i < len;i++){
		printf("%d", selected[i]);
		if(i != len - 1){
			printf(",");
		}
	}
	printf("]\n");
}

void generator(int cIndex,int rest,const int w, const mpz_t sum){
	/* w will only be used in printing a w decimal-bits number, so it is const*/
	mpz_t sum_a;
	mpz_init_set(sum_a,sum);

	/* cut */
	if(mpz_cmp(sum_a,k_powerOf_10[w]) >= 0) return;

	if(rest == 0){
		/* cut */
		if(mpz_cmp(sum_a,k_powerOf_10[w-1]) < 0) return;

		/* output a w decimal-bits number */
		/* output if and only if the selected is belong to PPDIs */
		// printSelected(w);
		// printSelected_arrayFormat(selected,w,decimal);
		if(isPPDI(w,sum_a)){
			numPPDIs++;
			gmp_printf("#[%02d]. %d bits: %Zd\n",numPPDIs,w,sum_a);
		}
		return;
	}

	/* cut */
	mpz_t temp_a;
	mpz_init_set(temp_a,numOf_powerRoots[cIndex][rest]);
	mpz_add(temp_a,temp_a,sum_a);
	if(mpz_cmp(temp_a,k_powerOf_10[w-1]) < 0) return;

	/* cut precheck */
	/* temp_a is max */
	if(!preCheck(sum_a,temp_a,cIndex,rest,w)) return;

	mpz_clear(temp_a);
	if(cIndex == 0){
		/* there will be w decimal-bits zeroes, which is equals to 0
		 * so to teminate it
		 */
		if(rest == w) return;
		/* because of checking a number,
		 * whether is an Armstrong Numer(PPDI) or not,
		 * we have to compare the selected array,
		 * with the number array splited by the sum of now situation.
		 * while the sum array includes some of  zeroes, but none of the selected,
		 * there will be a logic error,so set the column of cIndex to the rest,
		 * and pass 0 to generator() indicating that should be teminated,
		 * with the reason that all the rest,
		 * had been put in the column of the selected with zero
		 */
		selected[cIndex] = rest;
		generator(-1,0,w,sum_a);
	}else{
		/* to improve the performance for branch predicting 
		 * so sub powerRoots[cIndex][w] in advance
		 * and then when i is 0, to add it
		 * hence in other situations of i will not need to check if i is equals to 0
		 * hence there is not jump instruction
		 */
		mpz_sub(sum_a,sum_a,powerRoots[cIndex][w]);
		for(int i = 0;i <= rest;i++){
			/* equals to selected[cIndex]++, but with a better performance */
			selected[cIndex] = i;
			mpz_add(sum_a,sum_a,powerRoots[cIndex][w]);

			generator(cIndex-1,rest-i,w,sum_a);
		}
	}

	// printSelected(w);
	selected[cIndex] = 0;//reset

	mpz_clear(sum_a);
}