## Trying to match numpy perfomance with the use of SSE intrinsics in C 


N=10000 <br>
Numpy vector addition gflops = 0.44

C naive addition gflops = 0.13 <br>


With the use of _mm_add_sd intrinsic addition gflops jumped to 0.255
