#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

#ifdef __SSE2__
        #include <emmintrin.h>
#else
        #warning My processor does not support __SSE2__!
#endif

#define N 100000

float A[N] __attribute__ ((aligned(32)));
float B[N]__attribute__ ((aligned(32)));
float C[N]__attribute__ ((aligned(32)));
float val[N]; // gia debug

// vectors of four floating point numbers (4x32 = 128 bits)
__m128 *Am = (__m128 *)A;
__m128 *Bm = (__m128 *)B;
__m128 *Cm = (__m128 *)C;

// monotonic time in C
uint64_t nanos(){
	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	return (uint64_t)start.tv_sec*1000000000 + (uint64_t)start.tv_nsec;
}

void vec_add(){
/*	for (int i=0;i<N;i++){
		C[i] = A[i] + B[i];
	}*/
	for(int i=0;i<N/4;i++){
		Cm[i] = _mm_add_ps(Am[i], Bm[i]);
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
	// compute: N floating point operations for vector add
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
