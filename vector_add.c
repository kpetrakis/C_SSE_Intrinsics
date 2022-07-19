#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

#define N 10000

float A[N];
float B[N];
float C[N];
float val[N]; // gia debug

// monotonic time in C
uint64_t nanos(){
	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	return (uint64_t)start.tv_sec*1000000000 + (uint64_t)start.tv_nsec;
}

void vec_add(){
	for (int i=0;i<N;i++){
		C[i] = A[i] + B[i];
	}
}

int main(){
	
	FILE * f = fopen("vecadd", "rb");
	
	fread(A, 1, sizeof(float)*N, f);
	fread(B, 1, sizeof(float)*N, f);
	fread(val, 1, sizeof(float)*N, f);
	fclose(f);
	/*for(int i=0;i<N;i++){
		printf(" %f ", A[i]);
	}	
	for(int i=0;i<N;i++){
		printf(" %f ", B[i]);
	}*/	
	uint64_t start = nanos();
	vec_add();
	uint64_t end = nanos();
	float gflop = N*1e-9;
	float s = (end-start)*1e-9;
	printf("Gflop: %f\n", gflop);
	printf("%f GFLOP/s\n", gflop/s);

	for (int k = 0; k < N; k++) {
	    if (fabsf(C[k] - val[k]) > 1e-3) {
	      printf("MISMATCH AT %d, %f != %f\n", k, C[k], val[k]);
	      return -1;
	    }
  }
  printf("match\n");
		
	return 0;
}
