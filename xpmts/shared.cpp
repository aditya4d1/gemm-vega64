#include <iostream>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

typedef float Float4 __attribute__((ext_vector_type(4)));

__global__ void MatMul(Float4 *A, Float4 *B, Float4 *C) {
    int tx = hipThreadIdx_x;
    __shared__ Float4 sA[1024];
    __shared__ Float4 sB[1024];
    sA[0] = A[0];
    sA[1] = A[1];
    sA[2] = A[2];
    sA[3] = A[3];

    sB[0] = B[0];
    sB[1] = B[1];
    sB[2] = B[2];
    sB[3] = B[3];

    Float4 c0 = C[0];
    Float4 c1 = C[1];
    Float4 c2 = C[2];
    Float4 c3 = C[3];

    Float4 a = sA[0];
    Float4 b = sB[0];
    c0.x += a.x * b.x;
    c0.y += a.x * b.y;
    c0.z += a.x * b.z;
    c0.w += a.x * b.w;

    c1.x += a.y * b.x;
    c1.y += a.y * b.y;
    c1.z += a.y * b.z;
    c1.z += a.y * b.w;

    c2.x += a.z * b.x;
    c2.y += a.z * b.y;
    c2.z += a.z * b.z;
    c2.w += a.z * b.w;

    c3.x += a.w * b.x;
    c3.y += a.w * b.y;
    c3.z += a.w * b.z;
    c3.w += a.w * b.w;

    a = sA[1];
    b = sB[1];
    c0.x += a.x * b.x;
    c0.y += a.x * b.y;
    c0.z += a.x * b.z;
    c0.w += a.x * b.w;

    c1.x += a.y * b.x;
    c1.y += a.y * b.y;
    c1.z += a.y * b.z;
    c1.w += a.y * b.w;

    c2.x += a.z * b.x;
    c2.y += a.z * b.y;
    c2.z += a.z * b.z;
    c2.w += a.z * b.w;

    c3.x += a.w * b.x;
    c3.y += a.w * b.y;
    c3.z += a.w * b.z;
    c3.w += a.w * b.w;

    C[0] = c0;
    C[1] = c1;
    C[2] = c2;
    C[3] = c3;
}

int main() {
    Float4 *Ad, *Bd, *Cd;
    hipLaunchKernelGGL(MatMul, dim3(1,1,1), dim3(1,1,1), 0, 0, Ad, Bd, Cd);
}
