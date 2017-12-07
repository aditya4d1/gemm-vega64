#include <iostream>
#include <vector>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

#include "datatypes.h"

constexpr uint32_t len = 16;

template<typename offset>
__global__ void Kernel(Half4 *A, Half8 *B, Half8 *C) {
  int tx = hipThreadIdx_x;
  Half4 a = A[tx];
  Half8 b = B[tx];
  Half8 c0 = C[tx];
  Half8 c1 = C[tx + offset];
  Half8 c2 = C[tx + 2*offset];
  Half8 c3 = C[tx + 3*offset];
  asm volatile(
    "v_pk_fma_f16 %5, %0, %1, %5 opsel:[1,0,0] opsel_hi:[1,1,1]
    v_pk_fma_f16 %5, %0, %1, %5 opsel:[0,0,0] opsel_hi:[0,1,1]

    v_pk_fma_f16 %6, %0, %2, %6 opsel:[1,0,0] opsel_hi:[1,1,1]
    v_pk_fma_f16 %6, %0, %2, %6 opsel:[0,0,0] opsel_hi:[0,1,1]

    v_pk_fma_f16 %7, %0, %3, %7 opsel:[1,0,0] opsel_hi:[1,1,1]
    v_pk_fma_f16 %7, %0, %3, %7 opsel:[0,0,0] opsel_hi:[0,1,1]

    v_pk_fma_f16 %8, %0, %4, %8 opsel:[1,0,0] opsel_hi:[1,1,1]
    v_pk_fma_f16 %8, %0, %4, %8 opsel:[0,0,0] opsel_hi:[0,1,1]
    "
    :
    :"v"(a.x),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w),
    "v"(c0.x),"v"(c0.y),"v"(c0.z),"v"(c0.w)
  );
  C[tx] = c0;
}

int main() {
  std::vector<Half4> A(len);
  std::vector<Half8> B(len), C(len);

  for(int i=0;i<len;i++) {
    A[i].x.x = __fp16(1.0f);
    A[i].x.y = __fp16(1.0f);
    A[i].y.x = __fp16(1.0f);
    A[i].y.y = __fp16(1.0f);

    B[i].x.x = __fp16(2.0f);
    B[i].x.y = __fp16(2.0f);
    B[i].x.z = __fp16(2.0f);
    B[i].x.w = __fp16(2.0f);

    B[i].y.x = __fp16(2.0f);
    B[i].y.y = __fp16(2.0f);
    B[i].y.z = __fp16(2.0f);
    B[i].y.w = __fp16(2.0f);

    C[i].x.x = __fp16(2.0f);
    C[i].x.y = __fp16(2.0f);
    C[i].x.z = __fp16(2.0f);
    C[i].x.w = __fp16(2.0f);

    C[i].y.x = __fp16(2.0f);
    C[i].y.y = __fp16(2.0f);
    C[i].y.z = __fp16(2.0f);
    C[i].y.w = __fp16(2.0f);
  }

  Half4 *Ad;
  Half8 *Bd, *Cd;
}
