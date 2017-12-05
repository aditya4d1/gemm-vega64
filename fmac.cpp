#include<iostream>
#include<hip/hip_runtime.h>

#define WI 256
#define ITER 1 << 22

__global__ void FMAC(float *A) {
    int tx = hipThreadIdx_x;
    float a = A[tx];
    for(int i=0;i<ITER;i++) {
        a = a * a + a;
    }
    A[tx] = a;
}

int main() {
    float *A, *Ad;
    A = new float[WI];
    hipMalloc(&Ad, WI*sizeof(float));
    auto start = std::chrono::high_resolution_clock::now();
    hipLaunchKernelGGL(FMAC, dim3(512,1,1), dim3(WI,1,1), 0, 0, Ad);
    hipDeviceSynchronize();
    auto stop = std::chrono::high_resolution_clock::now();
    double elapsedSec = std::chrono::duration_cast<std::chrono::duration<double>>(stop-start).count();
    double ops = (double)(512) * (double)(WI) * (double)(ITER) * 2;
    double tp = (double)(ops) / 1.0E12 / elapsedSec;
    std::cout<<"Throughput: "<<tp<<std::endl;
}
