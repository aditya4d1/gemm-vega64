#include <iostream>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

typedef float Float4 __attribute__((ext_vector_type(4)));

__global__ void MatMul(Float4 *A, Float4 *B, Float4 *C) {
    int tx = hipThreadIdx_x;
/*
    __shared__ Float4 sA[4];
    __shared__ Float4 sB[4];
    sA[0] = A[0];
    sA[1] = A[1];
    sA[2] = A[2];
    sA[3] = A[3];

    sB[0] = B[0];
    sB[1] = B[1];
    sB[2] = B[2];
    sB[3] = B[3];


*/

    uint32_t shared_a, shared_b;
    Float4 a,b;
    asm volatile(
    "\n \
    v_mov_b32 %0, 0 \n \
    v_mov_b32 %1, 64 \n \
    "
    :"=v"(shared_a),"=v"(shared_b)
    :
    );

    asm volatile(
    "\n \
    ds_write_b128 %0, %4 \n \
    ds_write_b128 %1, %5 \n \
    ds_write_b128 %2, %6 \n \
    ds_write_b128 %3, %7 \n \
    "
    :
    :"v"(shared_a),"v"(shared_a+16),"v"(shared_a+32),"v"(shared_a+48), \
        "v"(A[0]),"v"(A[1]),"v"(A[2]),"v"(A[3])
    );

    asm volatile(
    "\n \
    ds_write_b128 %0, %4 \n \
    ds_write_b128 %1, %5 \n \
    ds_write_b128 %2, %6 \n \
    ds_write_b128 %3, %7 \n \
    "
    :
    :"v"(shared_b), "v"(shared_b+16), "v"(shared_b+32), "v"(shared_b+48), \
        "v"(B[0]), "v"(B[1]), "v"(B[2]), "v"(B[3])
    );

    asm volatile(
    "\n \ 
    s_waitcnt vmcnt(0) lgkmcnt(0) \n \
    "
    :
    :
    );

    asm volatile(
    " \n \
    ds_read_b128 %0, %2 \n \
    ds_read_b128 %1, %3 \n \
    "
    :"=v"(a),"=v"(b)
    :"v"(shared_a),"v"(shared_b)
    );

    asm volatile(
    "\n \
    s_waitcnt vmcnt(0) lgkmcnt(0) \n \
    "
    :
    :
    );

    Float4 c0 = C[0];
    Float4 c1 = C[1];
    Float4 c2 = C[2];
    Float4 c3 = C[3];

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

    C[0] = c0;
    C[1] = c1;
    C[2] = c2;
    C[3] = c3;
}

int main() {
    Float4 *Ad, *Bd, *Cd;
    hipHostMalloc(&Ad, sizeof(Float4)*4);
    hipHostMalloc(&Bd, sizeof(Float4)*4);
    hipHostMalloc(&Cd, sizeof(Float4)*4);
    Ad[0] = Float4(1.0f);
    Ad[1] = Float4(1.0f);
    Ad[2] = Float4(1.0f);
    Ad[3] = Float4(1.0f);

    Bd[0] = Float4(2.0f);
    Bd[1] = Float4(2.0f);
    Bd[2] = Float4(2.0f);
    Bd[3] = Float4(2.0f);

    Cd[0] = Float4(0.0f);
    Cd[1] = Float4(0.0f);
    Cd[2] = Float4(0.0f);
    Cd[3] = Float4(0.0f);
    hipLaunchKernelGGL(MatMul, dim3(1,1,1), dim3(1,1,1), 4*sizeof(Float4)*2, 0, Ad, Bd, Cd);
    hipDeviceSynchronize();
    std::cout<<Cd[0].x<<std::endl;
}
