
void merge(long src1[],long src2[],long dest[],long n){

	long i1 = 0;
	long i2 = 0;
	long id = 0;
	while(i1 < n && i2 < n){
		// long v1 = src1[i1];
		// long v2 = src2[i2];
		// long take = v1 < v2;
		// dest[id++] = take == 1 ? v1 : v2;
		// i1 += take;
		// i2 += 1-take;
		dest[id++] = src1[i1] < src2[i2] ? src1[i1++] : src2[i2++];
	}
	while(i1 < n) dest[id++] = src1[i1++];
	while(i2 < n) dest[id++] = src2[i2++];
}