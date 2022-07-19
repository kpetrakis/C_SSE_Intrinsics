## Trying to match numpy perfomance with the use of SSE intrinsics in C 


N=100000 <br>
Numpy vector addition gflops = 1.26

C naive addition gflops = 0.13 <br>


With the use of _mm_add_ps intrinsic addition gflops jumped to 0.60 <br>

CPU: intel core i7-2630QM 2.0-2.9 Turbo GHz
