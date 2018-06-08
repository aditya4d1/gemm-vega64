#include <iostream>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

typedef float Float4 __attribute__((ext_vector_type(4)));

/**
 * Here, we load 128x8 sub-matrix from A and B.
 * No DPP
 */

__global__ void MatMulNoDpp(Float4 *A, Float4 *B, Float4 *C) {
    int tid = hipThreadIdx_x;
    Float4 a = A[tid], b = B[tid];
    __shared__ Float4 sA[32*8], sB[32*8];
    sA[tid] = A[tid];
    sB[tid] = B[tid];

    int tx = tid % 16;
    int ty = tid / 16;

    Float4 a0 = sA[ty];
    Float4 a1 = sA[ty + 16];
    Float4 b0 = sB[(tx%2)*16 + (tx/2)];

    Float4 c[16];


    for(int i=0;i<16;i++) {
        c[i] = C[tid*16 + i];
    }


    c[0].x += a0.x * b0.x + 2.0f;
    c[0].y += a0.x * b0.y + 2.0f;
    c[0].z += a0.x * b0.z + 2.0f;
    c[0].w += a0.x * b0.w + 2.0f;


    c[1].x += a0.y * b0.x + 2.0f;
    c[1].y += a0.y * b0.y + 2.0f;
    c[1].z += a0.y * b0.z + 2.0f;
    c[1].w += a0.y * b0.w + 2.0f;

    c[2].x += a0.z * b0.x + 2.0f;
    c[2].y += a0.z * b0.y + 2.0f;
    c[2].z += a0.z * b0.z + 2.0f;
    c[2].w += a0.z * b0.w;

    c[3].x += a0.w * b0.x;
    c[3].y += a0.w * b0.y;
    c[3].z += a0.w * b0.z;
    c[3].w += a0.w * b0.w;


    c[4].x += a1.x * b0.x;
    c[4].y += a1.x * b0.y;
    c[4].z += a1.x * b0.z;
    c[4].w += a1.x * b0.w;

    c[5].x += a1.y * b0.x;
    c[5].y += a1.y * b0.y;
    c[5].z += a1.y * b0.z;
    c[5].w += a1.y * b0.w;

    c[6].x += a1.z * b0.x;
    c[6].y += a1.z * b0.y;
    c[6].z += a1.z * b0.z;
    c[6].w += a1.z * b0.w;

    c[7].x += a1.w * b0.x;
    c[7].y += a1.w * b0.y;
    c[7].z += a1.w * b0.z;
    c[7].w += a1.w * b0.w;


    c[8].x += a0.x * b0.x + 1.0f;
    c[8].y += a0.x * b0.y + 1.0f;
    c[8].z += a0.x * b0.z + 1.0f;
    c[8].w += a0.x * b0.w + 1.0f;

    c[9].x += a0.y * b0.x + 1.0f;
    c[9].y += a0.y * b0.y + 1.0f;
    c[9].z += a0.y * b0.z + 1.0f;
    c[9].w += a0.y * b0.w + 1.0f;

    c[10].x += a0.z * b0.x + 1.0f;
    c[10].y += a0.z * b0.y + 1.0f;
    c[10].z += a0.z * b0.z + 1.0f;
    c[10].w += a0.z * b0.w + 1.0f;

    c[11].x += a0.w * b0.x + 1.0f;
    c[11].y += a0.w * b0.y + 1.0f;
    c[11].z += a0.w * b0.z + 1.0f;
    c[11].w += a0.w * b0.w + 1.0f;


    c[12].x += a1.x * b0.x + 1.0f;
    c[12].y += a1.x * b0.y + 1.0f;
    c[12].z += a1.x * b0.z + 1.0f;
    c[12].w += a1.x * b0.w + 1.0f;

    c[13].x += a1.y * b0.x + 1.0f;
    c[13].y += a1.y * b0.y + 1.0f;
    c[13].z += a1.y * b0.z + 1.0f;
    c[13].w += a1.y * b0.w + 1.0f;

    c[14].x += a1.z * b0.x + 1.0f;
    c[14].y += a1.z * b0.y + 1.0f;
    c[14].z += a1.z * b0.z + 1.0f;
    c[14].w += a1.z * b0.w + 1.0f;

    c[15].x += a1.w * b0.x + 1.0f;
    c[15].y += a1.w * b0.y + 1.0f;
    c[15].z += a1.w * b0.z + 1.0f;
    c[15].w += a1.w * b0.w + 1.0f;

/** Stores to C is not valid
 * The code below ensures all workitems write to C.
 * Each workitem writes to a chunk of 64 floats coalesced
 */

    for(int i=0;i<16;i++) {
        C[tid*16 + i] = c[i];
    }

}



/**
 * Here, we load 128x8 sub-matrix from A and B.
 * DPP
 * Note: Make a uber asm kernel, seems like the last 2 dpp inline asm
 * blocks, lc is using same registers for input and output causing zero as output
 * The only way to solve it is to write a big kernel which loads C, does mac_dpp
 * and store to C.
 */
__global__ void MatMulDpp(Float4 *A, Float4 *B, Float4 *C) {
    int tid = hipThreadIdx_x;
    Float4 a = A[tid], b = B[tid];
    __shared__ Float4 sA[32*8], sB[32*8];
    sA[tid] = A[tid];
    sB[tid] = B[tid];

    int tx = tid % 16;
    int ty = tid / 16;

    Float4 a0 = sA[ty];
    Float4 a1 = sA[ty + 16];
    Float4 b0 = sB[tx];
    Float4 b1 = sB[tx + 16];

    Float4 c[16];


/*
    for(int i=0;i<16;i++) {
        c[i] = C[tid*16 + i];
    }
*/
/*
    c[0].x += a0.x * b0.x;
    c[0].y += a0.x * b0.y;
    c[0].z += a0.x * b0.z;
    c[0].w += a0.x * b0.w;
*/

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[0].x),"=v"(c[0].y),"=v"(c[0].z),"=v"(c[0].w)
    :"v"(a0.x),"v"(b0.x),"v"(b0.y),"v"(b0.z),"v"(b0.w)
    );
/*
    c[1].x += a0.y * b0.x;
    c[1].y += a0.y * b0.y;
    c[1].z += a0.y * b0.z;
    c[1].w += a0.y * b0.w;
*/
    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[1].x),"=v"(c[1].y),"=v"(c[1].z),"=v"(c[1].w)
    :"v"(a0.y),"v"(b0.x),"v"(b0.y),"v"(b0.z),"v"(b0.w)
    );


/*
    c[2].x += a0.z * b0.x;
    c[2].y += a0.z * b0.y;
    c[2].z += a0.z * b0.z;
    c[2].w += a0.z * b0.w;
*/
    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[2].x),"=v"(c[2].y),"=v"(c[2].z),"=v"(c[2].w)
    :"v"(a0.z),"v"(b0.x),"v"(b0.y),"v"(b0.z),"v"(b0.w)
    );


/*
    c[3].x += a0.w * b0.x;
    c[3].y += a0.w * b0.y;
    c[3].z += a0.w * b0.z;
    c[3].w += a0.w * b0.w;
*/
    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[3].x),"=v"(c[3].y),"=v"(c[3].z),"=v"(c[3].w)
    :"v"(a0.w),"v"(b0.x),"v"(b0.y),"v"(b0.z),"v"(b0.w)
    );

/*

    c[4].x += a1.x * b0.x;
    c[4].y += a1.x * b0.y;
    c[4].z += a1.x * b0.z;
    c[4].w += a1.x * b0.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[4].x),"=v"(c[4].y),"=v"(c[4].z),"=v"(c[4].w)
    :"v"(a1.x),"v"(b0.x),"v"(b0.y),"v"(b0.z),"v"(b0.w)
    );



    c[5].x += a1.y * b0.x;
    c[5].y += a1.y * b0.y;
    c[5].z += a1.y * b0.z;
    c[5].w += a1.y * b0.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[5].x),"=v"(c[5].y),"=v"(c[5].z),"=v"(c[5].w)
    :"v"(a1.y),"v"(b0.x),"v"(b0.y),"v"(b0.z),"v"(b0.w)
    );



    c[6].x += a1.z * b0.x;
    c[6].y += a1.z * b0.y;
    c[6].z += a1.z * b0.z;
    c[6].w += a1.z * b0.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[6].x),"=v"(c[6].y),"=v"(c[6].z),"=v"(c[6].w)
    :"v"(a1.z),"v"(b0.x),"v"(b0.y),"v"(b0.z),"v"(b0.w)
    );



    c[7].x += a1.w * b0.x;
    c[7].y += a1.w * b0.y;
    c[7].z += a1.w * b0.z;
    c[7].w += a1.w * b0.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[7].x),"=v"(c[7].y),"=v"(c[7].z),"=v"(c[7].w)
    :"v"(a1.w),"v"(b0.x),"v"(b0.y),"v"(b0.z),"v"(b0.w)
    );




    c[8].x += a0.x * b1.x;
    c[8].y += a0.x * b1.y;
    c[8].z += a0.x * b1.z;
    c[8].w += a0.x * b1.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[8].x),"=v"(c[8].y),"=v"(c[8].z),"=v"(c[8].w)
    :"v"(a0.x),"v"(b1.x),"v"(b1.y),"v"(b1.z),"v"(b1.w)
    );



    c[9].x += a0.y * b1.x;
    c[9].y += a0.y * b1.y;
    c[9].z += a0.y * b1.z;
    c[9].w += a0.y * b1.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[9].x),"=v"(c[9].y),"=v"(c[9].z),"=v"(c[9].w)
    :"v"(a0.y),"v"(b1.x),"v"(b1.y),"v"(b1.z),"v"(b1.w)
    );



    c[10].x += a0.z * b1.x;
    c[10].y += a0.z * b1.y;
    c[10].z += a0.z * b1.z;
    c[10].w += a0.z * b1.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[10].x),"=v"(c[10].y),"=v"(c[10].z),"=v"(c[10].w)
    :"v"(a0.z),"v"(b1.x),"v"(b1.y),"v"(b1.z),"v"(b1.w)
    );



    c[11].x += a0.w * b1.x;
    c[11].y += a0.w * b1.y;
    c[11].z += a0.w * b1.z;
    c[11].w += a0.w * b1.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[11].x),"=v"(c[11].y),"=v"(c[11].z),"=v"(c[11].w)
    :"v"(a0.w),"v"(b1.x),"v"(b1.y),"v"(b1.z),"v"(b1.w)
    );



    c[12].x += a1.x * b1.x;
    c[12].y += a1.x * b1.y;
    c[12].z += a1.x * b1.z;
    c[12].w += a1.x * b1.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[12].x),"=v"(c[12].y),"=v"(c[12].z),"=v"(c[12].w)
    :"v"(a1.x),"v"(b1.x),"v"(b1.y),"v"(b1.z),"v"(b1.w)
    );


    c[13].x += a1.y * b1.x;
    c[13].y += a1.y * b1.y;
    c[13].z += a1.y * b1.z;
    c[13].w += a1.y * b1.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[13].x),"=v"(c[13].y),"=v"(c[13].z),"=v"(c[13].w)
    :"v"(a1.y),"v"(b1.x),"v"(b1.y),"v"(b1.z),"v"(b1.w)
    );



    c[14].x += a1.z * b1.x;
    c[14].y += a1.z * b1.y;
    c[14].z += a1.z * b1.z;
    c[14].w += a1.z * b1.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[14].x),"=v"(c[14].y),"=v"(c[14].z),"=v"(c[14].w)
    :"v"(a1.z),"v"(b1.x),"v"(b1.y),"v"(b1.z),"v"(b1.w)
    );



    c[15].x += a1.w * b1.x;
    c[15].y += a1.w * b1.y;
    c[15].z += a1.w * b1.z;
    c[15].w += a1.w * b1.w;

    asm volatile("\n\
        v_mov_b32 %0, 0\n\
        v_mov_b32 %1, 0\n\
        v_mov_b32 %2, 0\n\
        v_mov_b32 %3, 0\n\
        v_mac_f32 %0, %4, %5 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %1, %4, %6 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %2, %4, %7 quad_perm:[0,1,2,3] \n\
        v_mac_f32 %3, %4, %8 quad_perm:[0,1,2,3] \n\
    "
    :"=v"(c[15].x),"=v"(c[15].y),"=v"(c[15].z),"=v"(c[15].w)
    :"v"(a1.w),"v"(b1.x),"v"(b1.y),"v"(b1.z),"v"(b1.w)
    );
*/



/** Stores to C is not valid
 * The code below ensures all workitems write to C.
 * Each workitem writes to a chunk of 64 floats coalesced
 */

    for(int i=0;i<16;i++) {
        C[tid*16 + i] = c[i];
    }

}


int main() {
    std::vector<Float4> A(32*8), B(32*8), C(32*128);
    Float4 a = {0.0f, 0.0f, 0.0f, 0.0f};
    Float4 b = {0.0f, 0.0f, 0.0f, 0.0f};
    Float4 c = {1.0f, 1.0f, 1.0f, 1.0f};
    std::fill(A.begin(), A.end(), a);
    std::fill(B.begin(), B.end(), b);
    std::fill(C.begin(), C.end(), c);
    for(int i=0;i<32;i++) {
        A[i] = {i * 4 + 1.0f, i * 4 + 2.0f, i * 4 + 3.0f, i * 4 + 4.0f};
        B[i] = {1.0f, 1.0f, 1.0f, 1.0f};
    }
    Float4 *Ad, *Bd, *Cd;
    hipMalloc(&Ad, sizeof(Float4)*A.size());
    hipMalloc(&Bd, sizeof(Float4)*B.size());
    hipMalloc(&Cd, sizeof(Float4)*C.size());

    hipMemcpy(Ad, A.data(), sizeof(Float4)*A.size(), hipMemcpyHostToDevice);
    hipMemcpy(Bd, B.data(), sizeof(Float4)*B.size(), hipMemcpyHostToDevice);
    hipMemcpy(Cd, C.data(), sizeof(Float4)*C.size(), hipMemcpyHostToDevice);

#if ENABLE_DPP == 0
    hipLaunchKernelGGL(MatMulNoDpp, dim3(1,1,1), dim3(256,1,1), 0, 0, Ad, Bd, Cd);
#else
    hipLaunchKernelGGL(MatMulDpp, dim3(1,1,1), dim3(256,1,1), 0, 0, Ad, Bd, Cd);
#endif
    hipDeviceSynchronize();

    hipMemcpy(C.data(), Cd, sizeof(Float4)*C.size(), hipMemcpyDeviceToHost);
    // print out limit * 4. Every 64 floats is from a workitem
    for(int i=0;i<16;i++) {
        std::cout<<C[i].x<<" "<<C[i].y<<" "<<C[i].z<<" "<<C[i].w<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
