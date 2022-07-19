#!/usr/bin/env python3

import numpy as np
import time
import os

np.set_printoptions(suppress=True)

N = 100000

if __name__ =='__main__':

    A = np.random.randn(N).astype(np.float32)
    B = np.random.randn(N).astype(np.float32)

    # compute: N operations for vector addition
    flop = N
    print(f"flop: {flop/1e9:.2f} GFLOP")
    for i in range(10):
        st = time.monotonic()
        C = A + B
        et = time.monotonic()
        s = et - st
        print(f"{flop/s* 1e-9:.2f} GFLOP/s")
	
    #print(A)
    #print(B)
    #print(C)
    with open("vecadd", "wb") as f:
        f.write(A.data)
        f.write(B.data)
        f.write(C.data)
