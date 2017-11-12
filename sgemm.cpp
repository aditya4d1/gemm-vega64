#include <iostream>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#include "outer_product.h"
#include "global_ops.h"
#include "shared_ops.h"
#include "dims.h"

__global__ void SGEMM(Float4 *A, Float4 *B, Float4 *C, Float4 *buffA, Float4 *buffB) {
  int tx = hipThreadIdx_x;
  int ty = hipThreadIdx_y;
  int bx = hipBlockIdx_x;
  int by = hipBlockIdx_y;

/**
* Initial order of instructions
* 1. Calculate A and B load indices
* 2. Load A and B into registers
* 3. Calculate C load indices
* 4. Load C to c[16]
* 5. Calculate lds read and write indices for A and B (this can move to point 3)
* 6. Wait for A and B loads
* 7. Write loaded A (a) and B (b) into lds
* 8. Wait for writes to lds
* 9. Read LDS to a0, a1, b0, b1
* 10. Wait for C
* 11. Wait for LDS reads of a0, a1, b0, b1
* 12. Operate on c[16], a0, a1, b0, b1
* 13. Write c[16] to C
*/


  Float4 a0, a1, a2, a3, b0, b1, b2, b3;
  Float4 rA0, rA1, rB0, rB1;
  Float4 c[16];

  int a_global_id = tx + (ty % 2) * 16 + (ty / 2) * dim_x4 + bx * 32 + by * 8192;
  int b_global_id = tx + (ty % 2) * 16 + (ty / 2) * dim_x4 + bx * 32 + by * 8192;

  global_load(A, rA0, a_global_id);
  global_load(B, rB0, b_global_id);
 
  int c0_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*0;
  int c1_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*1;
  int c2_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*2;
  int c3_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*3;

  int c4_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*0 + half_tilex4;
  int c5_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*1 + half_tilex4;
  int c6_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*2 + half_tilex4;
  int c7_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*3 + half_tilex4;

  int c8_id  = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + dim_x4*0;
  int c9_id  = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + dim_x4*1;
  int c10_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + dim_x4*2;
  int c11_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + dim_x4*3;

  int c12_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + half_tilex4 + dim_x4*0;
  int c13_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + half_tilex4 + dim_x4*1;
  int c14_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + half_tilex4 + dim_x4*2;
  int c15_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + half_tilex4 + dim_x4*3;

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

  int a_shared_id = (tx + (ty % 2) * 16 + (ty / 2) * 32);
  int b_shared_id = (tx + (ty % 2) * 16 + (ty / 2) * 32);

/*
  uint32_t redA_read_id0 = tx;
  uint32_t redA_read_id1 = (tx + 16);
  uint32_t redB_read_id0 = ty;
  uint32_t redB_read_id1 = (ty + 16);

  __shared__ Float4 sA[256];
  __shared__ Float4 sB[256];
  sA[a_shared_id] = a;
  sB[b_shared_id] = b;

  a0 = sA[redA_read_id0];
  a1 = sA[redA_read_id1];

  b0 = sB[redB_read_id0];
  b1 = sB[redB_read_id1];
*/

  uint32_t redA, redB, blueA, blueB;
  shared_init(redA, redB, blueA, blueB);

  uint32_t redA_write_id = redA + a_shared_id*16;
  uint32_t redB_write_id = redB + b_shared_id*16;
  uint32_t blueA_write_id = blueA + a_shared_id*16;
  uint32_t blueB_write_id = blueB + a_shared_id*16;

  uint32_t redA_read_id0 = redA + tx * 16;
  uint32_t redA_read_id1 = redA + (tx + 16) * 16;
  uint32_t redB_read_id0 = redB + ty * 16;
  uint32_t redB_read_id1 = redB + (ty + 16) * 16;

  uint32_t blueA_read_id0 = blueA + tx * 16;
  uint32_t blueA_read_id1 = blueA + (tx + 16) * 16;
  uint32_t blueB_read_id0 = blueB + tx * 16;
  uint32_t blueB_read_id1 = blueB + (tx + 16) * 16;

/**
* Wait for A and B
  As 16 is too high, wait for C too
  vmcnt<0>();
*/
  vmcnt<0>();

/**
Prefetch to blue lds
*/

/**
* Unroll loop for unroll_factor
* Do global_load 
* Do lds_write
*/

/**
* global to registers
* registers to lds
* read i0
* loop starts
* Do global to register (for next iter)
* do iter0
* read iter2
* do iter1
* read iter3
* do iter2
* ....
* read iter6
* do iter5
* vmcnt() (for next iter)
* registers to lds (for next iter)
* read iter7
* do iter6
* lgkmcnt<>(); (wait for registers to lds)
* read iter 0
* do iter7
*/

  a_global_id = tx + (ty % 2) * 16 + (ty / 2) * dim_x4 + bx * 32 + by * 8192 + 8 * dim_x4;
  b_global_id = tx + (ty % 2) * 16 + (ty / 2) * dim_x4 + bx * 32 + by * 8192 + 8 * dim_x4;
 
  global_load(A, rA1, a_global_id);
  global_load(B, rB1, b_global_id);

  shared_write_b128(rA0, redA_write_id);
  shared_write_b128(rB0, redB_write_id);

  // Wait until writes are written
  lgkmcnt<0>();

  shared_read_b128(a0, redA_read_id0);
  shared_read_b128(a1, redA_read_id1);
  shared_read_b128(b0, redB_read_id0);
  shared_read_b128(b1, redB_read_id1);

  redA_read_id0 += 512;
  redA_read_id1 += 512;
  redB_read_id0 += 512;
  redB_read_id1 += 512;

  // Start prefetching 
  shared_read_b128(a2, redA_read_id0);
  shared_read_b128(a3, redA_read_id1);
  shared_read_b128(b2, redB_read_id0);
  shared_read_b128(b3, redB_read_id1);

  redA_read_id0 += 512;
  redA_read_id1 += 512;
  redB_read_id0 += 512;
  redB_read_id1 += 512;

  // Wait for reads to a0, a1, b0, b1
  lgkmcnt<4>();

  // Operate on a0, a1, b0, b1 - Iteration 0
  outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

  // Start prefetching to a0, a1, b0, b1
  shared_read_b128(a0, redA_read_id0);
  shared_read_b128(a1, redA_read_id1);
  shared_read_b128(b0, redB_read_id0);
  shared_read_b128(b1, redB_read_id1);

  redA_read_id0 += 512;
  redA_read_id1 += 512;
  redB_read_id0 += 512;
  redB_read_id1 += 512;

  // Wait for reads to a2, a3, b2, b3
  lgkmcnt<4>();

  // Operate on a2, a3, b2, b3 - Iteration 1
  outerProduct4x4(a2, b2, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a3, b3, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a2, b2, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a3, b3, c[12], c[13], c[14], c[15]);

  shared_read_b128(a2, redA_read_id0);
  shared_read_b128(a3, redA_read_id1);
  shared_read_b128(b2, redB_read_id0);
  shared_read_b128(b3, redB_read_id1);

  redA_read_id0 += 512;
  redA_read_id1 += 512;
  redB_read_id0 += 512;
  redB_read_id1 += 512;

  // Wait for reads to a0, a1, b0, b1
  lgkmcnt<4>();

  // Operate on a0, a1, b0, b1 - Iteration 2
  outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

  shared_read_b128(a0, redA_read_id0);
  shared_read_b128(a1, redA_read_id1);
  shared_read_b128(b0, redB_read_id0);
  shared_read_b128(b1, redB_read_id1);

  redA_read_id0 += 512;
  redA_read_id1 += 512;
  redB_read_id0 += 512;
  redB_read_id1 += 512;

  // Wait for reads to a2, a3, b2, b3
  lgkmcnt<4>();

  // Operate on a2, a3, b2, b3 - Iteration 3
  outerProduct4x4(a2, b2, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a3, b3, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a2, b2, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a3, b3, c[12], c[13], c[14], c[15]);

  shared_read_b128(a2, redA_read_id0);
  shared_read_b128(a3, redA_read_id1);
  shared_read_b128(b2, redB_read_id0);
  shared_read_b128(b3, redB_read_id1);

  redA_read_id0 += 512;
  redA_read_id1 += 512;
  redB_read_id0 += 512;
  redB_read_id1 += 512;

  // Wait for reads to a0, a1, b0, b1
  lgkmcnt<4>();

  // Operate on a0, a1, b0, b1 - Iteration 4
  outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

  shared_read_b128(a0, redA_read_id0);
  shared_read_b128(a1, redA_read_id1);
  shared_read_b128(b0, redB_read_id0);
  shared_read_b128(b1, redB_read_id1);

  redA_read_id0 += 512;
  redA_read_id1 += 512;
  redB_read_id0 += 512;
  redB_read_id1 += 512;

  // Wait for reads to a2, a3, b2, b3
  lgkmcnt<4>();

  // Operate on a2, a3, b2, b3 - Iteration 5
  outerProduct4x4(a2, b2, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a3, b3, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a2, b2, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a3, b3, c[12], c[13], c[14], c[15]);

  shared_read_b128(a2, redA_read_id0);
  shared_read_b128(a3, redA_read_id1);
  shared_read_b128(b2, redB_read_id0);
  shared_read_b128(b3, redB_read_id1);

  redA_read_id0 += 512;
  redA_read_id1 += 512;
  redB_read_id0 += 512;
  redB_read_id1 += 512;

  // Wait for reads to a0, a1, b0, b1
  lgkmcnt<4>();

  // Operate on a0, a1, b0, b1 - Iteration 6
  outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

/** Dont need these!
  shared_read_b128(a0, redA_read_id0);
  shared_read_b128(a1, redA_read_id1);
  shared_read_b128(b0, redB_read_id0);
  shared_read_b128(b1, redB_read_id1);

  redA_read_id0 += 512;
  redA_read_id1 += 512;
  redB_read_id0 += 512;
  redB_read_id1 += 512;
*/
  // Wait for reads to a2, a3, b2, b3
  lgkmcnt<4>();

  // Operate on a2, a3, b2, b3 - Iteration 7
  outerProduct4x4(a2, b2, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a3, b3, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a2, b2, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a3, b3, c[12], c[13], c[14], c[15]);



/**
for(int i=0;i<unroll_factor;i++) {
  shared_read_b128(a0, blueA_read_id0);
  shared_read_b128(a1, blueA_read_id1);
  shared_read_b128(b0, blueB_read_id0);
  shared_read_b128(b1, blueB_read_id1);

  // Wait for reads from A and B lds
  lgkmcnt<0>();

  outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
  outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
  outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
  outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

/**
TODO: The following pattern can be changed to use offset for lds loads
  redA_read_id0 += 256;
  redA_read_id1 += 256;
  redB_read_id0 += 256;
  redB_read_id1 += 256;


  blueA_read_id0 += 512;
  blueA_read_id1 += 512;
  blueB_read_id0 += 512;
  blueB_read_id1 += 512;
}
*/

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

  buffA[a_global_id] = rA0;
  buffB[b_global_id] = rB0;

}


int main() {
  hipSetDevice(1);
  std::vector<Float4> a(dim_x4*dim_y), b(dim_x4*dim_y), c(dim_x4*dim_y);
  std::fill(a.begin(), a.end(), 2.0f);
  std::fill(b.begin(), b.end(), 3.0f);
  std::fill(c.begin(), c.end(), 1.0f);
  Float4 *Ad, *Bd, *Cd;
  Float4 *buffA, *buffB;
  hipHostMalloc(&buffA, size);
  hipHostMalloc(&buffB, size);
  hipMalloc(&Ad, size);
  hipMalloc(&Bd, size);
  hipMalloc(&Cd, size);
  hipMemcpy(Ad, a.data(), size, hipMemcpyHostToDevice);
  hipMemcpy(Bd, b.data(), size, hipMemcpyHostToDevice);
  hipMemcpy(Cd, c.data(), size, hipMemcpyHostToDevice);
  hipLaunchKernelGGL(SGEMM, dim3(dim_x4/(2*16),dim_y4/(2*16),1), dim3(16,16,1), 4*sizeof(float)*8*128, 0, Ad, Bd, Cd, buffA, buffB);
  hipDeviceSynchronize();
  hipMemcpy(c.data(), Cd, size, hipMemcpyDeviceToHost);

  for(int i=0;i<dim_x4*dim_y;i++) {
    if(c[i].x != 7.0f) {
        std::cout<<"Bad output at: "<<i<<" "<<c[i].x<<" "<<a[i].x<<std::endl;
        return 0;
    }
  }
  std::cout<<buffA[10].x<<" "<<buffB[10].x<<std::endl;
  std::cout<<c[10].x<<std::endl;
}
