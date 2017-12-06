/**
* Not - Working code for
* 1. Global load from A, B and C (asm)
* 2. Write to LDS (asm)
* 3. Read from LDS (asm)
* 4. 8 iteration of outer product (asm)
* 5. offset based load and stores (asm)
* 6. Store to global (asm)
* + Double Buffering!
*/

#include <iostream>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#include "outer_product.h"
#include "global_ops.h"
#include "shared_ops.h"
#include "dims.h"
#include <fstream>

constexpr uint32_t xDim = 4096;
constexpr uint32_t yDim = 4096;
constexpr uint32_t xDim4 = xDim/4;
constexpr uint32_t xDim8 = xDim/8;
constexpr uint32_t x32 = 32;
constexpr uint32_t x16 = 16;
constexpr size_t Size = xDim * yDim * sizeof(float);

__global__ void SGEMM(Float4 *A, Float4 *B, Float4 *C, int *getGlobalAId, int *getGlobalCId) {
    int tx = hipThreadIdx_x;
    int ty = hipThreadIdx_y;
    int bx = hipBlockIdx_x;
    int by = hipBlockIdx_y;

    Float4 rA[4], rB[4];
    Float4 c[16];
    asm volatile ("\n \
    v_mov_b32 %0, 0\n \
    v_mov_b32 %1, 0\n \
    v_mov_b32 %2, 0\n \
    v_mov_b32 %3, 0\n \
    v_mov_b32 %4, 0\n \
    v_mov_b32 %5, 0\n \
    v_mov_b32 %6, 0\n \
    v_mov_b32 %7, 0\n \
    v_mov_b32 %8, 0\n \
    v_mov_b32 %9, 0\n \
    v_mov_b32 %10, 0\n \
    v_mov_b32 %11, 0\n \
    v_mov_b32 %12, 0\n \
    v_mov_b32 %13, 0\n \
    v_mov_b32 %14, 0\n \
    v_mov_b32 %15, 0\n "
    :"=v"(c[0].x),"=v"(c[0].y),"=v"(c[0].z),"=v"(c[0].w),
    "=v"(c[1].x),"=v"(c[1].y),"=v"(c[1].z),"=v"(c[1].w),
    "=v"(c[2].x),"=v"(c[2].y),"=v"(c[2].z),"=v"(c[2].w),
    "=v"(c[3].x),"=v"(c[3].y),"=v"(c[3].z),"=v"(c[3].w)
    :
    );


    asm volatile ("\n \
    v_mov_b32 %0, 0\n \
    v_mov_b32 %1, 0\n \
    v_mov_b32 %2, 0\n \
    v_mov_b32 %3, 0\n \
    v_mov_b32 %4, 0\n \
    v_mov_b32 %5, 0\n \
    v_mov_b32 %6, 0\n \
    v_mov_b32 %7, 0\n \
    v_mov_b32 %8, 0\n \
    v_mov_b32 %9, 0\n \
    v_mov_b32 %10, 0\n \
    v_mov_b32 %11, 0\n \
    v_mov_b32 %12, 0\n \
    v_mov_b32 %13, 0\n \
    v_mov_b32 %14, 0\n \
    v_mov_b32 %15, 0\n "
    :"=v"(c[4].x),"=v"(c[4].y),"=v"(c[4].z),"=v"(c[4].w),
    "=v"(c[5].x),"=v"(c[5].y),"=v"(c[5].z),"=v"(c[5].w),
    "=v"(c[6].x),"=v"(c[6].y),"=v"(c[6].z),"=v"(c[6].w),
    "=v"(c[7].x),"=v"(c[7].y),"=v"(c[7].z),"=v"(c[7].w)
    :
    );

    asm volatile ("\n \
    v_mov_b32 %0, 0\n \
    v_mov_b32 %1, 0\n \
    v_mov_b32 %2, 0\n \
    v_mov_b32 %3, 0\n \
    v_mov_b32 %4, 0\n \
    v_mov_b32 %5, 0\n \
    v_mov_b32 %6, 0\n \
    v_mov_b32 %7, 0\n \
    v_mov_b32 %8, 0\n \
    v_mov_b32 %9, 0\n \
    v_mov_b32 %10, 0\n \
    v_mov_b32 %11, 0\n \
    v_mov_b32 %12, 0\n \
    v_mov_b32 %13, 0\n \
    v_mov_b32 %14, 0\n \
    v_mov_b32 %15, 0\n "
    :"=v"(c[8].x),"=v"(c[8].y),"=v"(c[8].z),"=v"(c[8].w),
    "=v"(c[9].x),"=v"(c[9].y),"=v"(c[9].z),"=v"(c[9].w),
    "=v"(c[10].x),"=v"(c[10].y),"=v"(c[10].z),"=v"(c[10].w),
    "=v"(c[11].x),"=v"(c[11].y),"=v"(c[11].z),"=v"(c[11].w)
    :
    );

    asm volatile ("\n \
    v_mov_b32 %0, 0\n \
    v_mov_b32 %1, 0\n \
    v_mov_b32 %2, 0\n \
    v_mov_b32 %3, 0\n \
    v_mov_b32 %4, 0\n \
    v_mov_b32 %5, 0\n \
    v_mov_b32 %6, 0\n \
    v_mov_b32 %7, 0\n \
    v_mov_b32 %8, 0\n \
    v_mov_b32 %9, 0\n \
    v_mov_b32 %10, 0\n \
    v_mov_b32 %11, 0\n \
    v_mov_b32 %12, 0\n \
    v_mov_b32 %13, 0\n \
    v_mov_b32 %14, 0\n \
    v_mov_b32 %15, 0\n "
    :"=v"(c[12].x),"=v"(c[12].y),"=v"(c[12].z),"=v"(c[12].w),
    "=v"(c[13].x),"=v"(c[13].y),"=v"(c[13].z),"=v"(c[13].w),
    "=v"(c[14].x),"=v"(c[14].y),"=v"(c[14].z),"=v"(c[14].w),
    "=v"(c[15].x),"=v"(c[15].y),"=v"(c[15].z),"=v"(c[15].w)
    :
    );

    Float4 ra, rb;

    uint32_t redA = 0;
    uint32_t redB = 4096;

    uint32_t ldsReadA = 0;
    uint32_t ldsReadB = 4096;
    uint32_t ldsWriteA = 0;
    uint32_t ldsWriteB = 4096;

    int id = tx + (ty % 2) * x16 + (ty / 2) * x32;
    int a_global_id = tx + (ty % 2) * x16 + (ty / 2) * 1024 + by * x32;
    int b_global_id = tx + (ty % 2) * x16 + (ty / 2) * 1024 + bx * x32;

    int cid0 = tx + ty * 4 * xDim4 + 0*1024 + bx * 32 + by * 1024 * 128;
    int cid1 = tx + ty * 4 * xDim4 + 1*1024 + bx * 32 + by * 1024 * 128;
    int cid2 = tx + ty * 4 * xDim4 + 2*1024 + bx * 32 + by * 1024 * 128;
    int cid3 = tx + ty * 4 * xDim4 + 3*1024 + bx * 32 + by * 1024 * 128;

    int cid4 = tx + ty * 4 * xDim4 + 16 + 0*1024 + bx * 32 + by * 1024 * 128;
    int cid5 = tx + ty * 4 * xDim4 + 16 + 1*1024 + bx * 32 + by * 1024 * 128;
    int cid6 = tx + ty * 4 * xDim4 + 16 + 2*1024 + bx * 32 + by * 1024 * 128;
    int cid7 = tx + ty * 4 * xDim4 + 16 + 3*1024 + bx * 32 + by * 1024 * 128;

    int cid8 = tx + ty * 4 * xDim4 + 0*1024 + 64*1024 + bx * 32 + by * 1024 * 128;
    int cid9 = tx + ty * 4 * xDim4 + 1*1024 + 64*1024 + bx * 32 + by * 1024 * 128;
    int cid10= tx + ty * 4 * xDim4 + 2*1024 + 64*1024 + bx * 32 + by * 1024 * 128;
    int cid11= tx + ty * 4 * xDim4 + 3*1024 + 64*1024 + bx * 32 + by * 1024 * 128;

    int cid12= tx + ty * 4 * xDim4 + 16 + 64*1024 + 0*1024 + bx * 32 + by * 1024 * 128;
    int cid13= tx + ty * 4 * xDim4 + 16 + 64*1024 + 1*1024 + bx * 32 + by * 1024 * 128;
    int cid14= tx + ty * 4 * xDim4 + 16 + 64*1024 + 2*1024 + bx * 32 + by * 1024 * 128;
    int cid15= tx + ty * 4 * xDim4 + 16 + 64*1024 + 3*1024 + bx * 32 + by * 1024 * 128;

    global_load<0>(A, ra, a_global_id);
    global_load<0>(B, rb, b_global_id);
    a_global_id += 8 * 1024;
    b_global_id += 8 * 1024;

    ldsReadA = redA+ty*16;
    ldsReadB = redB+tx*16;

    ldsWriteA = redA+id*16;
    ldsWriteB = redB+id*16;

    vmcnt<0>();
    shared_write_b128(ra, ldsWriteA);
    shared_write_b128(rb, ldsWriteB);
    lgkmcnt<0>();

    asm volatile("\n \
    ds_read_b128 %0, %4 offset:0      \n \
    ds_read_b128 %1, %4 offset:256   \n \
    ds_read_b128 %2, %5 offset:0      \n \
    ds_read_b128 %3, %5 offset:256   \n \
    "
    :"=v"(rA[0]),"=v"(rA[1]), "=v"(rB[0]), "=v"(rB[1])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

for(int j=1;j<yDim/8;j++) {

    global_load<0>(A, ra, a_global_id);
    global_load<0>(B, rb, b_global_id);
    a_global_id += 8 * 1024;
    b_global_id += 8 * 1024;

    asm volatile("\n \
    ds_read_b128 %0, %4 offset:1*512      \n \
    ds_read_b128 %1, %4 offset:1*512+256  \n \
    ds_read_b128 %2, %5 offset:1*512      \n \
    ds_read_b128 %3, %5 offset:1*512+256  \n \
    "
    :"=v"(rA[2]),"=v"(rA[3]), "=v"(rB[2]), "=v"(rB[3])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

    lgkmcnt<4>();

    // i = 0
    outerProduct4x4(rA[0], rB[0], c[0], c[1], c[2], c[3]);
    outerProduct4x4(rA[0], rB[1], c[4], c[5], c[6], c[7]);
    outerProduct4x4(rA[1], rB[0], c[8], c[9], c[10], c[11]);
    outerProduct4x4(rA[1], rB[1], c[12], c[13], c[14], c[15]);

    asm volatile("\n \
    ds_read_b128 %0, %4 offset:2*512 \n \
    ds_read_b128 %1, %4 offset:2*512+256 \n \
    ds_read_b128 %2, %5 offset:2*512 \n \
    ds_read_b128 %3, %5 offset:2*512+256 \n \
    "
    :"=v"(rA[0]),"=v"(rA[1]), "=v"(rB[0]), "=v"(rB[1])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

    lgkmcnt<4>();

    // i = 1
    outerProduct4x4(rA[2], rB[2], c[0], c[1], c[2], c[3]);
    outerProduct4x4(rA[2], rB[3], c[4], c[5], c[6], c[7]);
    outerProduct4x4(rA[3], rB[2], c[8], c[9], c[10], c[11]);
    outerProduct4x4(rA[3], rB[3], c[12], c[13], c[14], c[15]);


    asm volatile("\n \
    ds_read_b128 %0, %4 offset:3*512      \n \
    ds_read_b128 %1, %4 offset:3*512+256  \n \
    ds_read_b128 %2, %5 offset:3*512      \n \
    ds_read_b128 %3, %5 offset:3*512+256  \n \
    "
    :"=v"(rA[2]),"=v"(rA[3]), "=v"(rB[2]), "=v"(rB[3])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

    lgkmcnt<4>();

    // i = 2
    outerProduct4x4(rA[0], rB[0], c[0], c[1], c[2], c[3]);
    outerProduct4x4(rA[0], rB[1], c[4], c[5], c[6], c[7]);
    outerProduct4x4(rA[1], rB[0], c[8], c[9], c[10], c[11]);
    outerProduct4x4(rA[1], rB[1], c[12], c[13], c[14], c[15]);

    asm volatile("\n \
    ds_read_b128 %0, %4 offset:4*512 \n \
    ds_read_b128 %1, %4 offset:4*512+256 \n \
    ds_read_b128 %2, %5 offset:4*512 \n \
    ds_read_b128 %3, %5 offset:4*512+256 \n \
    "
    :"=v"(rA[0]),"=v"(rA[1]), "=v"(rB[0]), "=v"(rB[1])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

    lgkmcnt<4>();

    // i = 3
    outerProduct4x4(rA[2], rB[2], c[0], c[1], c[2], c[3]);
    outerProduct4x4(rA[2], rB[3], c[4], c[5], c[6], c[7]);
    outerProduct4x4(rA[3], rB[2], c[8], c[9], c[10], c[11]);
    outerProduct4x4(rA[3], rB[3], c[12], c[13], c[14], c[15]);

    asm volatile("\n \
    ds_read_b128 %0, %4 offset:5*512      \n \
    ds_read_b128 %1, %4 offset:5*512+256  \n \
    ds_read_b128 %2, %5 offset:5*512      \n \
    ds_read_b128 %3, %5 offset:5*512+256  \n \
    "
    :"=v"(rA[2]),"=v"(rA[3]), "=v"(rB[2]), "=v"(rB[3])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

    lgkmcnt<4>();

    // i = 4
    outerProduct4x4(rA[0], rB[0], c[0], c[1], c[2], c[3]);
    outerProduct4x4(rA[0], rB[1], c[4], c[5], c[6], c[7]);
    outerProduct4x4(rA[1], rB[0], c[8], c[9], c[10], c[11]);
    outerProduct4x4(rA[1], rB[1], c[12], c[13], c[14], c[15]);

    asm volatile("\n \
    ds_read_b128 %0, %4 offset:6*512 \n \
    ds_read_b128 %1, %4 offset:6*512+256 \n \
    ds_read_b128 %2, %5 offset:6*512 \n \
    ds_read_b128 %3, %5 offset:6*512+256 \n \
    "
    :"=v"(rA[0]),"=v"(rA[1]), "=v"(rB[0]), "=v"(rB[1])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

    lgkmcnt<4>();

    // i = 5
    outerProduct4x4(rA[2], rB[2], c[0], c[1], c[2], c[3]);
    outerProduct4x4(rA[2], rB[3], c[4], c[5], c[6], c[7]);
    outerProduct4x4(rA[3], rB[2], c[8], c[9], c[10], c[11]);
    outerProduct4x4(rA[3], rB[3], c[12], c[13], c[14], c[15]);

    asm volatile("\n \
    ds_read_b128 %0, %4 offset:7*512 \n \
    ds_read_b128 %1, %4 offset:7*512+256 \n \
    ds_read_b128 %2, %5 offset:7*512 \n \
    ds_read_b128 %3, %5 offset:7*512+256 \n \
    "
    :"=v"(rA[2]),"=v"(rA[3]), "=v"(rB[2]), "=v"(rB[3])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

    redA = redA ^ 0x2000;
    redB = redB ^ 0x2000;

    ldsWriteA = redA+id*16;
    ldsWriteB = redB+id*16;
    ldsReadA = redA+ty*16;
    ldsReadB = redB+tx*16;

    vmcnt<0>();

    shared_write_b128(ra, ldsWriteA);
    shared_write_b128(rb, ldsWriteB);

    lgkmcnt<2>();

    // i = 6
    outerProduct4x4(rA[0], rB[0], c[0], c[1], c[2], c[3]);
    outerProduct4x4(rA[0], rB[1], c[4], c[5], c[6], c[7]);
    outerProduct4x4(rA[1], rB[0], c[8], c[9], c[10], c[11]);
    outerProduct4x4(rA[1], rB[1], c[12], c[13], c[14], c[15]);

    lgkmcnt<0>();
    __syncthreads();

    asm volatile("\n \
    ds_read_b128 %0, %4 offset:0      \n \
    ds_read_b128 %1, %4 offset:256   \n \
    ds_read_b128 %2, %5 offset:0      \n \
    ds_read_b128 %3, %5 offset:256   \n \
    "
    :"=v"(rA[0]),"=v"(rA[1]), "=v"(rB[0]), "=v"(rB[1])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

    // i = 7
    outerProduct4x4(rA[2], rB[2], c[0], c[1], c[2], c[3]);
    outerProduct4x4(rA[2], rB[3], c[4], c[5], c[6], c[7]);
    outerProduct4x4(rA[3], rB[2], c[8], c[9], c[10], c[11]);
    outerProduct4x4(rA[3], rB[3], c[12], c[13], c[14], c[15]);

}


Float4 d[16];

global_load<0>(C, d[0], cid0);
global_load<0>(C, d[1], cid1);
global_load<0>(C, d[2], cid2);
global_load<0>(C, d[3], cid3);

global_load<16>(C, d[4], cid0);
global_load<16>(C, d[5], cid1);
global_load<16>(C, d[6], cid2);
global_load<16>(C, d[7], cid3);

global_load<0>(C, d[8], cid8);
global_load<0>(C, d[9], cid9);
global_load<0>(C, d[10], cid10);
global_load<0>(C, d[11], cid11);

global_load<16>(C, d[12], cid8);
global_load<16>(C, d[13], cid9);
global_load<16>(C, d[14], cid10);
global_load<16>(C, d[15], cid11);

asm volatile("ds_read_b128 %0, %4 offset:1*512      \n \
ds_read_b128 %1, %4 offset:1*512+256  \n \
ds_read_b128 %2, %5 offset:1*512      \n \
ds_read_b128 %3, %5 offset:1*512+256"
:"=v"(rA[2]),"=v"(rA[3]), "=v"(rB[2]), "=v"(rB[3])
:"v"(ldsReadA), "v"(ldsReadB)
);

lgkmcnt<4>();

// i = 0
outerProduct4x4(rA[0], rB[0], c[0], c[1], c[2], c[3]);
outerProduct4x4(rA[0], rB[1], c[4], c[5], c[6], c[7]);
outerProduct4x4(rA[1], rB[0], c[8], c[9], c[10], c[11]);
outerProduct4x4(rA[1], rB[1], c[12], c[13], c[14], c[15]);

asm volatile("\n \
ds_read_b128 %0, %4 offset:2*512 \n \
ds_read_b128 %1, %4 offset:2*512+256 \n \
ds_read_b128 %2, %5 offset:2*512 \n \
ds_read_b128 %3, %5 offset:2*512+256 \n \
"
:"=v"(rA[0]),"=v"(rA[1]), "=v"(rB[0]), "=v"(rB[1])
:"v"(ldsReadA), "v"(ldsReadB)
);

lgkmcnt<4>();

// i = 1
outerProduct4x4(rA[2], rB[2], c[0], c[1], c[2], c[3]);
outerProduct4x4(rA[2], rB[3], c[4], c[5], c[6], c[7]);
outerProduct4x4(rA[3], rB[2], c[8], c[9], c[10], c[11]);
outerProduct4x4(rA[3], rB[3], c[12], c[13], c[14], c[15]);


asm volatile("\n \
ds_read_b128 %0, %4 offset:3*512      \n \
ds_read_b128 %1, %4 offset:3*512+256  \n \
ds_read_b128 %2, %5 offset:3*512      \n \
ds_read_b128 %3, %5 offset:3*512+256  \n \
"
:"=v"(rA[2]),"=v"(rA[3]), "=v"(rB[2]), "=v"(rB[3])
:"v"(ldsReadA), "v"(ldsReadB)
);

lgkmcnt<4>();

// i = 2
outerProduct4x4(rA[0], rB[0], c[0], c[1], c[2], c[3]);
outerProduct4x4(rA[0], rB[1], c[4], c[5], c[6], c[7]);
outerProduct4x4(rA[1], rB[0], c[8], c[9], c[10], c[11]);
outerProduct4x4(rA[1], rB[1], c[12], c[13], c[14], c[15]);

asm volatile("\n \
ds_read_b128 %0, %4 offset:4*512 \n \
ds_read_b128 %1, %4 offset:4*512+256 \n \
ds_read_b128 %2, %5 offset:4*512 \n \
ds_read_b128 %3, %5 offset:4*512+256 \n \
"
:"=v"(rA[0]),"=v"(rA[1]), "=v"(rB[0]), "=v"(rB[1])
:"v"(ldsReadA), "v"(ldsReadB)
);

lgkmcnt<4>();

// i = 3
outerProduct4x4(rA[2], rB[2], c[0], c[1], c[2], c[3]);
outerProduct4x4(rA[2], rB[3], c[4], c[5], c[6], c[7]);
outerProduct4x4(rA[3], rB[2], c[8], c[9], c[10], c[11]);
outerProduct4x4(rA[3], rB[3], c[12], c[13], c[14], c[15]);

asm volatile("\n \
ds_read_b128 %0, %4 offset:5*512      \n \
ds_read_b128 %1, %4 offset:5*512+256  \n \
ds_read_b128 %2, %5 offset:5*512      \n \
ds_read_b128 %3, %5 offset:5*512+256  \n \
"
:"=v"(rA[2]),"=v"(rA[3]), "=v"(rB[2]), "=v"(rB[3])
:"v"(ldsReadA), "v"(ldsReadB)
);

lgkmcnt<4>();

// i = 4
outerProduct4x4(rA[0], rB[0], c[0], c[1], c[2], c[3]);
outerProduct4x4(rA[0], rB[1], c[4], c[5], c[6], c[7]);
outerProduct4x4(rA[1], rB[0], c[8], c[9], c[10], c[11]);
outerProduct4x4(rA[1], rB[1], c[12], c[13], c[14], c[15]);

asm volatile("\n \
ds_read_b128 %0, %4 offset:6*512 \n \
ds_read_b128 %1, %4 offset:6*512+256 \n \
ds_read_b128 %2, %5 offset:6*512 \n \
ds_read_b128 %3, %5 offset:6*512+256 \n \
"
:"=v"(rA[0]),"=v"(rA[1]), "=v"(rB[0]), "=v"(rB[1])
:"v"(ldsReadA), "v"(ldsReadB)
);

lgkmcnt<4>();

// i = 5
outerProduct4x4(rA[2], rB[2], c[0], c[1], c[2], c[3]);
outerProduct4x4(rA[2], rB[3], c[4], c[5], c[6], c[7]);
outerProduct4x4(rA[3], rB[2], c[8], c[9], c[10], c[11]);
outerProduct4x4(rA[3], rB[3], c[12], c[13], c[14], c[15]);

asm volatile("\n \
ds_read_b128 %0, %4 offset:7*512 \n \
ds_read_b128 %1, %4 offset:7*512+256 \n \
ds_read_b128 %2, %5 offset:7*512 \n \
ds_read_b128 %3, %5 offset:7*512+256 \n \
"
:"=v"(rA[2]),"=v"(rA[3]), "=v"(rB[2]), "=v"(rB[3])
:"v"(ldsReadA), "v"(ldsReadB)
);
lgkmcnt<4>();
// i = 6
outerProduct4x4(rA[0], rB[0], c[0], c[1], c[2], c[3]);
outerProduct4x4(rA[0], rB[1], c[4], c[5], c[6], c[7]);
outerProduct4x4(rA[1], rB[0], c[8], c[9], c[10], c[11]);
outerProduct4x4(rA[1], rB[1], c[12], c[13], c[14], c[15]);

lgkmcnt<4>();

// i = 5
outerProduct4x4(rA[2], rB[2], c[0], c[1], c[2], c[3]);
outerProduct4x4(rA[2], rB[3], c[4], c[5], c[6], c[7]);
outerProduct4x4(rA[3], rB[2], c[8], c[9], c[10], c[11]);
outerProduct4x4(rA[3], rB[3], c[12], c[13], c[14], c[15]);

vmcnt<0>();

c[0] += d[0];
c[1] += d[1];
c[2] += d[2];
c[3] += d[3];

c[4] += d[4];
c[5] += d[5];
c[6] += d[6];
c[7] += d[7];

c[8] += d[8];
c[9] += d[9];
c[10] += d[10];
c[11] += d[11];

c[12] += d[12];
c[13] += d[13];
c[14] += d[14];
c[15] += d[15];

    global_store<0>(C, c[0], cid0);
    global_store<0>(C, c[1], cid1);
    global_store<0>(C, c[2], cid2);
    global_store<0>(C, c[3], cid3);

    global_store<16>(C, c[4], cid0);
    global_store<16>(C, c[5], cid1);
    global_store<16>(C, c[6], cid2);
    global_store<16>(C, c[7], cid3);

    global_store<0>(C, c[8], cid8);
    global_store<0>(C, c[9], cid9);
    global_store<0>(C, c[10], cid10);
    global_store<0>(C, c[11], cid11);

    global_store<16>(C, c[12], cid8);
    global_store<16>(C, c[13], cid9);
    global_store<16>(C, c[14], cid10);
    global_store<16>(C, c[15], cid11);

    vmcnt<0>();
}


int main() {
    hipSetDevice(1);
    std::vector<Float4> a(xDim4*yDim), b(xDim4*yDim), c(xDim*xDim4);
    std::fill(c.begin(), c.end(), 0.0f);
    float *_a = reinterpret_cast<float*>(a.data());
    float *_b = reinterpret_cast<float*>(b.data());
    float *_c = reinterpret_cast<float*>(c.data());

    for(int j=0;j<yDim;j++) {
        for(int i=0;i<xDim;i++) {
            _a[i + j * xDim] = (j+i*xDim)*1.0f + 1.0f;
            if(i == j) {
            _b[i + j * xDim] = 1.0f;
            } else {
            _b[i + j * xDim] = 0.0f;
            }
        }
    }

    Float4 *Ad, *Bd, *Cd;
    int *buffA, *buffB;
    hipHostMalloc(&buffA, 16*16*sizeof(int));
    hipHostMalloc(&buffB, 16*16*sizeof(int));
    hipMalloc(&Ad, a.size()*sizeof(Float4));
    hipMalloc(&Bd, b.size()*sizeof(Float4));
    hipMalloc(&Cd, c.size()*sizeof(Float4));
    hipMemcpy(Ad, a.data(), a.size()*sizeof(Float4), hipMemcpyHostToDevice);
    hipMemcpy(Bd, b.data(), b.size()*sizeof(Float4), hipMemcpyHostToDevice);
    hipMemcpy(Cd, c.data(), c.size()*sizeof(Float4), hipMemcpyHostToDevice);
    auto start = std::chrono::high_resolution_clock::now();
    hipLaunchKernelGGL(SGEMM, dim3(32,32,1), dim3(16,16,1), 4*sizeof(float)*8*128*2, 0, Ad, Bd, Cd, buffA, buffB);
    hipDeviceSynchronize();
    auto stop = std::chrono::high_resolution_clock::now();
    double sec = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
    std::cout<<sec<<std::endl;
    double flops = (double)xDim * (double)yDim * (double)yDim * 2 / (double)1.0e12;
    double floppersec = flops / sec;
    std::cout<<flops<<" "<<sec<<" "<<floppersec<<std::endl;
    hipMemcpy(c.data(), Cd, c.size()*sizeof(Float4), hipMemcpyDeviceToHost);
    std::ofstream outfile;
    outfile.open("outfile.txt");

    std::cout<<"writing to outfile"<<std::endl;

    for(int j=0;j<4;j++) {
        for(int i=0;i<xDim;i++) {
            outfile << _c[i+j*xDim] <<" ";
        }
        outfile <<"\n";
    }
    outfile<<"\n\n\n";
/*
    std::cout<<"Done writing to outfile"<<std::endl;
    for(int j=0;j<16;j++) {
        for(int i=0;i<16;i++) {
            outfile << buffA[i+j*16]<<" ";
        }
        outfile << "\n";
    }
    outfile<<"\n\n\n";
    for(int j=0;j<16;j++) {
        for(int i=0;i<16;i++) {
            outfile << buffB[i+j*16]<<" ";
        }
        outfile << "\n";
    }
    outfile<<"\n\n\n";
*/
    outfile.close();
}
