#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static mpz_t *exponentTable;//[10] = {0};
static time_t startTime;
    
void isArmNum(int p[],int w,int total[],int k,mpz_t *armNum,mpz_t resNum) {
    // = -1;
    mpz_t powSum;// = 0;
    // mpz_init(powSum);
    mpz_set_si(resNum,-1);
    mpz_init_set_si(powSum,0);

    for(int x = 0;x < w;x++) {
        mpz_add(powSum,powSum,exponentTable[total[p[x]]]);
        // powSum += exponentTable[total[p[x]]];
    }
    //拆powNum
    mpz_t xSum;
    // mpz_init(xSum);
    mpz_init_set_si(xSum,0);

    mpz_t tempPowSum;// = powSum;
    // mpz_init(tempPowSum);
    mpz_init_set(tempPowSum,powSum);

    int len = 0;

    mpz_t single;
    mpz_init(single);

    // gmp_printf("%Zd__%d\n",tempPowSum,mpz_cmp_ui(tempPowSum,0));

    while(mpz_cmp_ui(tempPowSum,0) > 0) {
        // mpz_mod_ui(single,tempPowSum,10);
        mpz_tdiv_qr_ui(tempPowSum,single,tempPowSum,10);

        int tempIndex = (int)mpz_get_ui(single);
        mpz_add(xSum,xSum,exponentTable[tempIndex]);

        // gmp_printf("tempPowSum:%Zd\n",tempPowSum);
        // mpz_tdiv_q_ui(tempPowSum,tempPowSum,10);
        // gmp_printf("tempPowSum:%Zd\n",tempPowSum);
        len++;
    }
    // gmp_printf("tempIndex:%d__",tempIndex);
    // gmp_printf("xSum:%Zd__%Zd__%d\n",xSum,tempPowSum,mpz_cmp_ui(tempPowSum,0));
    // printf("_________________________________________\n");
    if(mpz_cmp(xSum,powSum) == 0 && len == w) {
        bool isSame = false;
        for(int j = 0;j <= k;j++) {
            if(mpz_cmp(xSum,armNum[j]) == 0) {
                isSame = true;
                break;
            }
        }
        if(!isSame) {
            mpz_set(resNum,xSum);
            // resNum = xSum;
        }
    }
    
    mpz_clear(powSum);
    mpz_clear(xSum);
    mpz_clear(tempPowSum);
    mpz_clear(single);

    // return resNum;
}

void oneWBit(int w,int total[],int *k,mpz_t* armNum){
    for(int x = 0;x < 10;x++) {
        mpz_mul_ui(exponentTable[x],exponentTable[x],x);
        // exponentTable[x] *= x;
    }
    
    // int p[] = new int[w];
    int *p = malloc(sizeof(int)*w);
    int last = w-1;
    
    //公式稍有瑕疵，还需要确认
    int aMin = (int) (10 / pow(10*w,1.0/w)) - 1;
    int aMax = (int) (10 / pow(w,1.0/w));
    
    int *Xmin = malloc(sizeof(int)*w);
    int *Xmax = malloc(sizeof(int)*w);
    
    for(int i = 0;i < w;i++) {
        p[i] = 0;
        Xmin[i] = aMin;
        Xmax[i] = aMax;
    }
    
    p[last] = Xmin[last]+1;
    while(p[0] <= 8) {//下标为9
        mpz_t xSum;
        mpz_init(xSum);
        isArmNum(p, w, total, *k, armNum,xSum);
        
        if(mpz_cmp_si(xSum,-1) != 0) {
            mpz_set(armNum[*k],xSum);
            // armNum[k] = xSum;
            (*k)++;
        }
        
        p[last]++;
        if(p[last] > 9) {
            int index = 0;
            for(int x = w-1;x > 0;x--) {
                if(p[x] > 9) {
                    p[x-1]++;
                }else {
                    index = x;
                    break;
                }
            }
            for(int x = index;x < w - 1;x++) {
                p[x+1] = p[x];
            }
            
            if(p[last-1] <= Xmin[last-1]) {
                p[last] = Xmin[last]+1;
            }
            
            bool isMore = true;
            for(int x = 0;x < w;x++) {
                if(p[x] <= Xmax[x]) {
                    isMore = false;
                    break;
                }
            }
            if(isMore) break;
        }

        mpz_clear(xSum);
    }

    free(p);
    free(Xmin);
    free(Xmax);
}
    
void calculate(int begin,int end,int total[],int *k,mpz_t* armNum) {

    time_t inner_startTime,inner_endTime;
    for(int w = begin;w <= end;w++) {
        time(&inner_startTime);

        int cell = 5;//剪枝粒度 10^5

        oneWBit(w,total,k,armNum);

        time(&inner_endTime);  
        double inner_costTime = difftime(inner_endTime,inner_startTime);  
        printf("第%02d位计算完成，耗时%.2lf s\n",w,inner_costTime);
    }
    // return armNum;
}

void initArray(mpz_t *p,int len){
    for(int i = 0;i < len;i++){
        mpz_init(p[i]);
    }
}
int main(void) {

    int eTableLen = 10;
    exponentTable = malloc(sizeof(mpz_t)*eTableLen);
    initArray(exponentTable,eTableLen);

    printf("输入位数：");
    int begin = 2;
    int end;
    scanf("%d",&end);    

    int armNumLen = 88;
    mpz_t *armNum = malloc(sizeof(mpz_t)*armNumLen);//new mpz_t[88];
    initArray(armNum,armNumLen);

    int total[] = {1,2,3,4,5,6,7,8,9,0};
    
    for(int i = 0;i < 10;i++) {
        mpz_set_ui(exponentTable[i],i);
        // exponentTable[i] = i;
    }
    
    int k = 0;
    /* 1-9 为Armstrong Num，无需计算*/
    for(int i = 1;i <= 9;i++) {
        mpz_set_ui(armNum[k],i);
        // armNum[k] = i;
        k++;
    }

    time_t totalEndTime;
    double costTime;  
    time(&startTime);  

    calculate(begin,end, total, &k, armNum);
    
    time(&totalEndTime);  
    costTime = difftime(totalEndTime,startTime);  
    
    int len = 0;
    for(int i = 0;i < k;i++) {
        gmp_printf("%Zd\n", armNum[i]);
        len++;
    }
    printf("共找到%d个Armstrong数，耗时 %.2lf s\n",len,costTime);
    return 0;
}
