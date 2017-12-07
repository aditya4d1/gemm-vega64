#include <iostream>
#include <vector>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

#include "../datatypes.h"

constexpr uint32_t len = 16;

template<uint32_t offset>
__global__ void Kernel(b64 *A, b128 *B, b128 *C) {
  int tx = hipThreadIdx_x;
  b64 a0 = A[tx];
  b128 b = B[tx];
  b128 c0 = C[tx];
  b128 c1 = C[tx + offset];
  b128 c2 = C[tx + 2*offset];
  b128 c3 = C[tx + 3*offset];
  asm volatile(
    "\n \
    v_pk_fma_f16 %5, %0, %1, %5 op_sel:[1,0,0] op_sel_hi:[1,1,1] \n \
    v_pk_fma_f16 %5, %0, %1, %5 op_sel:[0,0,0] op_sel_hi:[0,1,1] \n \
;    \n \
;    v_pk_fma_f16 %6, %0, %2, %6 op_sel:[1,0,0] op_sel_hi:[1,1,1] \n \
;    v_pk_fma_f16 %6, %0, %2, %6 op_sel:[0,0,0] op_sel_hi:[0,1,1] \n \
;    \n \
;    v_pk_fma_f16 %7, %0, %3, %7 op_sel:[1,0,0] op_sel_hi:[1,1,1] \n \
;    v_pk_fma_f16 %7, %0, %3, %7 op_sel:[0,0,0] op_sel_hi:[0,1,1] \n \
;    \n \
;    v_pk_fma_f16 %8, %0, %4, %8 op_sel:[1,0,0] op_sel_hi:[1,1,1] \n \
;    v_pk_fma_f16 %8, %0, %4, %8 op_sel:[0,0,0] op_sel_hi:[0,1,1] \n \
    "
    :
    :"v"(a0.x),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w),
    "v"(c0.x),"v"(c0.y),"v"(c0.z),"v"(c0.w)
  );
  C[tx] = c0;
}

int main() {
  std::vector<Half4> A(len);
  std::vector<Half8> B(len), C(len);

  for(int i=0;i<len;i++) {
    A[i].x = __fp16(3.0f);
    A[i].y = __fp16(3.0f);
    A[i].z = __fp16(3.0f);
    A[i].w = __fp16(3.0f);

    B[i][0] = __fp16(2.0f);
    B[i][1] = __fp16(2.0f);
    B[i][2] = __fp16(2.0f);
    B[i][3] = __fp16(2.0f);

    B[i][4] = __fp16(2.0f);
    B[i][5] = __fp16(2.0f);
    B[i][6] = __fp16(2.0f);
    B[i][7] = __fp16(2.0f);

    C[i][0] = __fp16(1.0f);
    C[i][1] = __fp16(1.0f);
    C[i][2] = __fp16(1.0f);
    C[i][3] = __fp16(1.0f);

    C[i][4] = __fp16(1.0f);
    C[i][5] = __fp16(1.0f);
    C[i][6] = __fp16(1.0f);
    C[i][7] = __fp16(1.0f);
  }


  Half4 *Ad;
  Half8 *Bd, *Cd;
    hipMalloc(&Ad, A.size()*sizeof(Half4));
    hipMalloc(&Bd, B.size()*sizeof(Half8));
    hipMalloc(&Cd, C.size()*sizeof(Half8));

    hipMemcpy(Ad, A.data(), A.size()*sizeof(Half4), hipMemcpyHostToDevice);
    hipMemcpy(Bd, B.data(), B.size()*sizeof(Half8), hipMemcpyHostToDevice);
    hipMemcpy(Cd, C.data(), C.size()*sizeof(Half8), hipMemcpyHostToDevice);

    hipLaunchKernelGGL((Kernel<16>), dim3(1,1,1), dim3(1,1,1), 0, 0, reinterpret_cast<b64*>(Ad), reinterpret_cast<b128*>(Bd), reinterpret_cast<b128*>(Cd));
    hipDeviceSynchronize();

    hipMemcpy(C.data(), Cd, C.size()*sizeof(Half8), hipMemcpyDeviceToHost);
    for(int i=0;i<len;i++) {
        for(int j=0;j<8;j++) {
            std::cout<<float(C[i][j])<<" ";
        }
        std::cout<<std::endl;
    }
}
