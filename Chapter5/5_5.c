
double poly(double a[],double x,long degree){
	long i;
	double result = a[0];
	double xpwr = x;
	for(i = 1;i <= degree;i++){
		result += a[i] * xpwr;
		xpwr = x * xpwr;
	}
	return result;
}

int main(void){
	double a[10] = {1.0,1.1,1.0,1.1,1.0,1.1,1.0,1.1,1.0,1.1};
	double x = 2.3;
	long degree = 10;
	poly(a,x,degree);
	return 0;
}