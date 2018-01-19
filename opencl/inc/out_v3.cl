#include"/home/aditya/gemm-vega64/opencl/inc/global_ops.h"
#include"/home/aditya/gemm-vega64/opencl/inc/shared_ops.h"
#include"/home/aditya/gemm-vega64/opencl/inc/outer_product.h"


__kernel void Main(__global float4 *A, __global float4 *B, __global float4 *C) {
    int2 lid = { get_local_id(0), get_local_id(1) };
    int2 gid = { get_group_id(0), get_group_id(1) };

    float4 rA[4], rB[4];
    float4 c[16];

    float4 ra, rb;

    /**
    16 workitems
    2 float4s per workitem
    8 is the unroll factor
    4 is the total number of tiles needed
    */
    __local float4 lds[16*2*8*4];


    int track = 0;

    __local float4 *ldsReadA, *ldsReadB, *ldsWriteA, *ldsWriteB;

    int id = lid.x + (lid.y / 2) * 16 + (lid.y / 2) * 32;
    int a_global_id = lid.x + (lid.y % 2) * 16 + (lid.y / 2) * 1024 + gid.y * 32;
    int b_global_id = lid.x + (lid.y % 2) * 16 + (lid.y / 2) * 1024 + gid.x * 32;

    int cid0 = lid.x + lid.y * 4 * 1024 + gid.x * 32 + gid.y * 1024 * 128;

    ldsReadA = lds + lid.y;
    ldsReadB = lds + lid.x;

    ldsWriteA = lds + id;
    ldsWriteB = lds + id;

    global_load_off0_f32x4(A + a_global_id, &ra);
    global_load_off0_f32x4(B + b_global_id, &rb);

    a_global_id += 8 * 1024;
    b_global_id += 8 * 1024;

    __global float4 *tmpC = C + cid0;
    global_load_off0_f32x4(tmpC, &c[0]);
    global_load_off16_f32x4(tmpC, &c[4]);
    tmpC += 1024; 
    global_load_off0_f32x4(tmpC, &c[1]);
    global_load_off16_f32x4(tmpC, &c[5]);
    tmpC += 1024;
    global_load_off0_f32x4(tmpC, &c[2]);
    global_load_off16_f32x4(tmpC, &c[6]);
    tmpC += 1024;
    global_load_off0_f32x4(tmpC, &c[3]);
    global_load_off16_f32x4(tmpC, &c[7]);

    tmpC = C + 64*1024 + cid0;
    global_load_off0_f32x4(tmpC, &c[8]);
    global_load_off16_f32x4(tmpC, &c[12]);
    tmpC += 1024;
    global_load_off0_f32x4(tmpC, &c[9]);
    global_load_off16_f32x4(tmpC, &c[13]);
    tmpC += 1024;
    global_load_off0_f32x4(tmpC, &c[10]);
    global_load_off16_f32x4(tmpC, &c[14]);
    tmpC += 1024;
    global_load_off0_f32x4(tmpC, &c[11]);
    global_load_off16_f32x4(tmpC, &c[15]);

    vmcnt0();
/*
    shared_write_b128_0(ldsWriteA, &ra);
    shared_write_b128_4096(ldsWriteB, &rb);
    lgkmcnt0();

    shared_read_b128_0(ldsReadA, ldsReadB, &rA[0], &rA[1], &rB[0], &rB[1]);
    shared_read_b128_512(ldsReadA, ldsReadB, &rA[2], &rA[3], &rB[2], &rB[3]);
    lgkmcnt4();
*/

    __asm(
    "ds_write_b128 %0, %2 offset:0 \n"
    "ds_write_b128 %1, %3 offset:4096 \n"
    "s_waitcnt lgkmcnt(0)\n"
    :
    :"v"(ldsWriteA), "v"(ldsWriteB), "v"(ra), "v"(rb)
    );

    __asm(
    "ds_read_b128 %0, %8 offset:0\n"
    "ds_read_b128 %1, %8 offset:256\n"
    "ds_read_b128 %4, %9 offset:0\n"
    "ds_read_b128 %5, %9 offset:256\n"

    "ds_read_b128 %2, %8 offset:512\n"
    "ds_read_b128 %3, %8 offset:512+256\n"
    "ds_read_b128 %6, %9 offset:512\n"
    "ds_read_b128 %7, %9 offset:512+256\n"
    "s_waitcnt lgkmcnt(4)\n"
    :"=v"(rA[0]),"=v"(rA[1]),"=v"(rA[2]),"=v"(rA[3]),
    "=v"(rB[0]),"=v"(rB[1]),"=v"(rB[2]),"=v"(rB[3])
    :"v"(ldsReadA), "v"(ldsReadB)
    );

    op_4x4f(&rA[0], &rB[0], &c[0], &c[1], &c[2], &c[3]);
    op_4x4f(&rA[0], &rB[1], &c[4], &c[5], &c[6], &c[7]);
    op_4x4f(&rA[1], &rB[0], &c[8], &c[9], &c[10], &c[11]);
    op_4x4f(&rA[1], &rB[1], &c[12], &c[13], &c[14], &c[15]);

//    shared_read_b128_1024(ldsReadA, ldsReadB, &rA[0], &rA[1], &rB[0], &rB[1]);
//    lgkmcnt4();

    __asm(
    "ds_read_b128 %0, %4 offset:1024+0\n"
    "ds_read_b128 %1, %4 offset:1024+256\n"
    "ds_read_b128 %2, %5 offset:1024+0\n"
    "ds_read_b128 %3, %5 offset:1024+256\n"
    "s_waitcnt lgkmcnt(4)\n"
    :"=v"(rA[0]),"=v"(rA[1]),"=v"(rB[0]),"=v"(rB[1])
    :"v"(ldsReadA),"v"(ldsReadB)
    );

    op_4x4f(&rA[2], &rB[2], &c[0], &c[1], &c[2], &c[3]);
    op_4x4f(&rA[2], &rB[3], &c[4], &c[5], &c[6], &c[7]);
    op_4x4f(&rA[3], &rB[2], &c[8], &c[9], &c[10], &c[11]);
    op_4x4f(&rA[3], &rB[3], &c[12], &c[13], &c[14], &c[15]);

    shared_read_b128_1536(ldsReadA, ldsReadB, &rA[2], &rA[3], &rB[0], &rB[1]);
    lgkmcnt4();

    op_4x4f(&rA[0], &rB[0], &c[0], &c[1], &c[2], &c[3]);
    op_4x4f(&rA[0], &rB[1], &c[4], &c[5], &c[6], &c[7]);
    op_4x4f(&rA[1], &rB[0], &c[8], &c[9], &c[10], &c[11]);
    op_4x4f(&rA[1], &rB[1], &c[12], &c[13], &c[14], &c[15]);

    shared_read_b128_2048(ldsReadA, ldsReadB, &rA[0], &rA[1], &rB[0], &rB[1]);
    lgkmcnt4();

    op_4x4f(&rA[2], &rB[2], &c[0], &c[1], &c[2], &c[3]);
    op_4x4f(&rA[2], &rB[3], &c[4], &c[5], &c[6], &c[7]);
    op_4x4f(&rA[3], &rB[2], &c[8], &c[9], &c[10], &c[11]);
    op_4x4f(&rA[3], &rB[3], &c[12], &c[13], &c[14], &c[15]);

    shared_read_b128_2560(ldsReadA, ldsReadB, &rA[2], &rA[3], &rB[0], &rB[1]);
    lgkmcnt4();

    op_4x4f(&rA[0], &rB[0], &c[0], &c[1], &c[2], &c[3]);
    op_4x4f(&rA[0], &rB[1], &c[4], &c[5], &c[6], &c[7]);
    op_4x4f(&rA[1], &rB[0], &c[8], &c[9], &c[10], &c[11]);
    op_4x4f(&rA[1], &rB[1], &c[12], &c[13], &c[14], &c[15]);

    shared_read_b128_3072(ldsReadA, ldsReadB, &rA[0], &rA[1], &rB[0], &rB[1]);
    lgkmcnt4();

    op_4x4f(&rA[2], &rB[2], &c[0], &c[1], &c[2], &c[3]);
    op_4x4f(&rA[2], &rB[3], &c[4], &c[5], &c[6], &c[7]);
    op_4x4f(&rA[3], &rB[2], &c[8], &c[9], &c[10], &c[11]);
    op_4x4f(&rA[3], &rB[3], &c[12], &c[13], &c[14], &c[15]);

    shared_read_b128_3584(ldsReadA, ldsReadB, &rA[2], &rA[3], &rB[0], &rB[1]);
    lgkmcnt4();

    op_4x4f(&rA[0], &rB[0], &c[0], &c[1], &c[2], &c[3]);
    op_4x4f(&rA[0], &rB[1], &c[4], &c[5], &c[6], &c[7]);
    op_4x4f(&rA[1], &rB[0], &c[8], &c[9], &c[10], &c[11]);
    op_4x4f(&rA[1], &rB[1], &c[12], &c[13], &c[14], &c[15]);

    lgkmcnt0();

    op_4x4f(&rA[2], &rB[2], &c[0], &c[1], &c[2], &c[3]);
    op_4x4f(&rA[2], &rB[3], &c[4], &c[5], &c[6], &c[7]);
    op_4x4f(&rA[3], &rB[2], &c[8], &c[9], &c[10], &c[11]);
    op_4x4f(&rA[3], &rB[3], &c[12], &c[13], &c[14], &c[15]);

    tmpC = C + cid0;
    global_store_off0_f32x4(tmpC, &c[0]);
    global_store_off16_f32x4(tmpC, &c[4]);
    tmpC += 1024;
    global_store_off0_f32x4(tmpC, &c[1]);
    global_store_off16_f32x4(tmpC, &c[5]);
    tmpC += 1024;
    global_store_off0_f32x4(tmpC, &c[2]);
    global_store_off16_f32x4(tmpC, &c[6]);
    tmpC += 1024;
    global_store_off0_f32x4(tmpC, &c[3]);
    global_store_off16_f32x4(tmpC, &c[7]);

    tmpC = C + 64*1024;
    global_store_off0_f32x4(tmpC, &c[8]);
    global_store_off16_f32x4(tmpC, &c[12]);
    tmpC += 1024;
    global_store_off0_f32x4(tmpC, &c[9]);
    global_store_off16_f32x4(tmpC, &c[13]);
    tmpC += 1024;
    global_store_off0_f32x4(tmpC, &c[10]);
    global_store_off16_f32x4(tmpC, &c[14]);
    tmpC += 1024;
    global_store_off0_f32x4(tmpC, &c[11]);
    global_store_off16_f32x4(tmpC, &c[15]);
    vmcnt0();
}
