#include<iostream>
#include<hip/hip_runtime.h>
#include<hip/hip_runtime_api.h>
#include "outer_product.h"
#include "global_ops.h"
#include "shared_ops.h"

constexpr uint32_t dim_x = 4096;
constexpr uint32_t dim_y = 4096;
constexpr uint32_t dim_x4 = dim_x / 4;
constexpr uint32_t dim_y4 = dim_y / 4;
constexpr uint32_t unroll_factor = 8;
constexpr uint32_t tile = 128;
constexpr uint32_t tilex4 = tile / 4;
constexpr uint32_t half_tile = 64;
constexpr uint32_t half_tilex4 = 64 / 4;
constexpr size_t size = dim_x * dim_y * sizeof(float);

__global__ void SGEMM(Float4 *A, Float4 *B, Float4 *C) {
  int tx = hipThreadIdx_x;
  int ty = hipThreadIdx_y;
  int bx = hipBlockIdx_x;
  int by = hipBlockIdx_y;

/**
* Load C
*/

  int c0_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + dim_x4*0;
  int c1_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + dim_x4*1;
  int c2_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + dim_x4*2;
  int c3_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + dim_x4*3;

  int c4_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + dim_x4*0 + half_tilex4;
  int c5_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + dim_x4*1 + half_tilex4;
  int c6_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + dim_x4*2 + half_tilex4;
  int c7_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + dim_x4*3 + half_tilex4;

  int c8_id  = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + half_tilex4 * dim_x4 + dim_x4*0;
  int c9_id  = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + half_tilex4 * dim_x4 + dim_x4*1;
  int c10_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + half_tilex4 * dim_x4 + dim_x4*2;
  int c11_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + half_tilex4 * dim_x4 + dim_x4*3;

  int c12_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + half_tilex4 * dim_x4 + half_tilex4 + dim_x4*0;
  int c13_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + half_tilex4 * dim_x4 + half_tilex4 + dim_x4*1;
  int c14_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + half_tilex4 * dim_x4 + half_tilex4 + dim_x4*2;
  int c15_id = tx + ty * dim_x4 + bx * tilex4 + by * dim_x4 * tilex4 + half_tilex4 * dim_x4 + half_tilex4 + dim_x4*3;

  int a_shared_id = tx + (ty % 2) * 16 + (ty / 2) * dim_x4;
  int b_shared_id = tx + (ty % 2) * 16 + (ty / 2) * dim_x4;

  int a_global_id = a_shared_id + bx * tilex4 + by * tilex4 * dim_x4;
  int b_global_id = b_shared_id + bx * tilex4 + by * tilex4 * dim_x4;

  Float4 a0, a1, b0, b1;
  Float4 a, b;
  Float4 c[16];

  global_load(A, a, a_id);
  global_load(B, b, a_id);

  uint32_t redA, redB, blueA, blueB;
  shared_init(redA, redB, blueA, blueB);

  uint32_t redA_write_id = redA + a_shared_id;
  uint32_t redB_write_id = redB + b_shared_id;

  uint32_t redA_read_id0 = redA + tx;
  uint32_t redA_read_id1 = redA + tx + 16;
  uint32_t redB_read_id0 = redB + tx;
  uint32_t redB_read_id1 = redB + tx + 16;

  shared_write_b128(a, redA_write_id);
  shared_write_b128(b, redB_write_id);

  shared_read_b128(a0, redA_read_id0);
  shared_read_b128(a1, redA_read_id1);
  shared_read_b128(b0, redA_read_id0);
  shared_read_b128(b1, redA_read_id1);

  global_load(C, c[0], c0_id);
  global_load(C, c[1], c1_id);
  global_load(C, c[2], c2_id);
  global_load(C, c[3], c3_id);

  global_load(C, c[4], c4_id);
  global_load(C, c[5], c5_id);
  global_load(C, c[6], c6_id);
  global_load(C, c[7], c7_id);

  global_load(C, c[8], c8_id);
  global_load(C, c[9], c9_id);
  global_load(C, c[10], c10_id);
  global_load(C, c[11], c11_id);

  global_load(C, c[12], c12_id);
  global_load(C, c[13], c13_id);
  global_load(C, c[14], c14_id);
  global_load(C, c[15], c15_id);

  lgkmcnt<0>();

  shared_read_b128(redA, a0);
  shared_read_b128(redB, );

  outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a1, b0, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a0, b1, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);


  global_store(C, c[0], c0_id);
  global_store(C, c[1], c1_id);
  global_store(C, c[2], c2_id);
  global_store(C, c[3], c3_id);

  global_store(C, c[4], c4_id);
  global_store(C, c[5], c5_id);
  global_store(C, c[6], c6_id);
  global_store(C, c[7], c7_id);

  global_store(C, c[8], c8_id);
  global_store(C, c[9], c9_id);
  global_store(C, c[10], c10_id);
  global_store(C, c[11], c11_id);

  global_store(C, c[12], c12_id);
  global_store(C, c[13], c13_id);
  global_store(C, c[14], c14_id);
  global_store(C, c[15], c15_id);
}


int main() {
  hipSetDevice(1);
  std::vector<Float4> a(dim_x4*dim_y), b(dim_x4*dim_y), c(dim_x4*dim_y);
  std::fill(a.begin(), a.end(), 2.0f);
  std::fill(b.begin(), b.end(), 3.0f);
  std::fill(c.begin(), c.end(), 1.0f);
  Float4 *Ad, *Bd, *Cd;
  hipMalloc(&Ad, size);
  hipMalloc(&Bd, size);
  hipMalloc(&Cd, size);
  hipMemcpy(Ad, a.data(), size, hipMemcpyHostToDevice);
  hipMemcpy(Bd, b.data(), size, hipMemcpyHostToDevice);
  hipMemcpy(Cd, c.data(), size, hipMemcpyHostToDevice);
  hipLaunchKernelGGL(SGEMM, dim3(dim_x/(8*16),dim_y/(8*16),1), dim3(16,16,1), 0, 0, Ad, Bd, Cd);
  hipDeviceSynchronize();
  hipMemcpy(c.data(), Cd, size, hipMemcpyDeviceToHost);
  std::cout<<c[10].x<<std::endl;
}
