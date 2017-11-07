#include<iostream>
#include<hip/hip_runtime.h>
#include<hip/hip_runtime_api.h>
#include "outer_product.h"

constexpr uint32_t dim_x = 4096;
constexpr uint32_t dim_y = 4096;
constexpr uint32_t dim_x4 = dim_x / 4;
constexpr uint32_t dim_y4 = dim_y / 4;
constexpr uint32_t unroll_factor = 8;
constexpr uint32_t tile = 128;
constexpr uint32_t tilex4 = tile / 4;
constexpr uint32_t half_tile = 64;
constexpr uint32_t half_tilex4 = 64 / 4;

__global__ void SGEMM(Float4 *A, Float4 *B, Float4 *C) {
  int tx = hipThreadIdx_x;
  int ty = hipThreadIdx_y;
  int bx = hipBlockIdx_x;
  int by = hipBlockIdx_y;

Float4 a0 = A[tx + bx * tilex4];
Float4 a1 = A[tx + bx * tilex4 + half_tilex4];
Float4 b0 = B[ty + by * tilex4];
Float4 b1 = B[ty + by * tilex4 + half_tilex4];

Float4 c0, c1, c2, c3, c4, c5, c6, c7;
Float4 c8, c9, c10, c11, c12, c13, c14, c15;


__shared__ Float4  redA[unroll_factor * tilex4];
__shared__ Float4  redB[unroll_factor * tilex4];
__shared__ Float4 blueA[unroll_factor * tilex4];
__shared__ Float4 blueB[unroll_factor * tilex4];

redA[tx] = a0;
redA[tx + half_tilex4] = a1;
redB[ty] = b0;
redB[ty + half_tilex4] = b1;

/**
int c0_id = tx + (dim_x/4)*0 + 00 + ty + bx * 32 + by * (dim_x/4) * 32;
int c1_id = tx + (dim_x/4)*1 + 00 + ty + bx * 32 + by * (dim_x/4) * 32;
int c2_id = tx + (dim_x/4)*2 + 00 + ty + bx * 32 + by * (dim_x/4) * 32;
int c3_id = tx + (dim_x/4)*4 + 00 + ty + bx * 32 + by * (dim_x/4) * 32;

int c4_id = tx + (dim_x/4)*0 + 16 + ty + bx * 32 + by * (dim_x/4) * 32;
int c5_id = tx + (dim_x/4)*1 + 16 + ty + bx * 32 + by * (dim_x/4) * 32;
int c6_id = tx + (dim_x/4)*2 + 16 + ty + bx * 32 + by * (dim_x/4) * 32;
int c7_id = tx + (dim_x/4)*4 + 16 + ty + bx * 32 + by * (dim_x/4) * 32;

int c8_id = tx + (dim_x/4)*0 + 00 + ty + 16 * (dim_x/4) + bx * 32 + by * (dim_x/4) * 32;
int c9_id = tx + (dim_x/4)*1 + 00 + ty + 16 * (dim_x/4) + bx * 32 + by * (dim_x/4) * 32;
int c10_id = tx + (dim_x/4)*2 + 00 + ty + 16 * (dim_x/4) + bx * 32 + by * (dim_x/4) * 32;
int c11_id = tx + (dim_x/4)*4 + 00 + ty + 16 * (dim_x/4) + bx * 32 + by * (dim_x/4) * 32;

int c8_id = tx + (dim_x/4)*0 + 16 + ty + 16 * (dim_x/4) + bx * 32 + by * (dim_x/4) * 32;
int c9_id = tx + (dim_x/4)*1 + 16 + ty + 16 * (dim_x/4) + bx * 32 + by * (dim_x/4) * 32;
int c10_id = tx + (dim_x/4)*2 + 16 + ty + 16 * (dim_x/4) + bx * 32 + by * (dim_x/4) * 32;
int c11_id = tx + (dim_x/4)*4 + 16 + ty + 16 * (dim_x/4) + bx * 32 + by * (dim_x/4) * 32
*/

/**
* Below, we try to load to registers using inline asm
*/

asm volatile(
  "\n \
    global_load_dwordx4 %0, %4, off \n \
    global_load_dwordx4 %1, %5, off \n \
    global_load_dwordx4 %2, %6, off \n \
    global_load_dwordx4 %3, %7, off \n \
  "
  :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
  :"v"(A + tx + bx * tilex4),"v"(A + tx + bx * tilex4 + half_tilex4),
    "v"(B + tx + bx * tilex4),"v"(B + tx + bx * tilex4 + half_tilex4)
);

outerProduct4x4(a0, b0, c0, c1, c2, c3);
outerProduct4x4(a1, b0, c4, c5, c6, c7);
outerProduct4x4(a0, b1, c8, c9, c10, c11);
outerProduct4x4(a1, b1, c12, c13, c14, c15);


}


int main() {
Float4 *a, *b, *c;
hipLaunchKernelGGL(SGEMM, dim3(1,1,1), dim3(1,1,1), 0, 0, a, b, c);
}
