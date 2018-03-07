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

    int cid0 = lid.x + lid.y * 4 * 1024 + gid.x * 32 + gid.y * 1024 * 128;

    int id = lid.x + (lid.y % 2) * 16 + (lid.y / 2) * 32;
    int a_global_id = lid.x + (lid.y % 2) * 16 + (lid.y / 2) * 1024 + gid.y * 32;
    int b_global_id = lid.x + (lid.y % 2) * 16 + (lid.y / 2) * 1024 + gid.x * 32;

    __local float4 *ldsReadA = lds + lid.y;
    __local float4 *ldsReadB = lds + lid.x;

    __local float4 *ldsWriteA = lds + id;
    __local float4 *ldsWriteB = lds + id;

//    global_load_off0_f32x4(A + a_global_id, &ra);
//    global_load_off0_f32x4(B + b_global_id, &rb);

    __asm volatile(
    "global_load_dwordx4 %0, %2, off\n"
    "global_load_dwordx4 %1, %3, off\n"
    "s_waitcnt vmcnt(0)\n"
    :"=v"(ra),"=v"(rb)
    :"v"(A + a_global_id), "v"(B + b_global_id)
    );

    __asm volatile(
    "ds_write_b128 %0, %2 offset:0 \n"
    "ds_write_b128 %1, %3 offset:4096 \n"
    "s_waitcnt lgkmcnt(0)\n"
    :
    :"v"(ldsWriteA), "v"(ldsWriteB), "v"(ra), "v"(rb)
    );

    __asm volatile(
    "ds_read_b128 %0, %8 offset:0\n"
    "ds_read_b128 %1, %8 offset:256\n"
    "ds_read_b128 %2, %9 offset:0\n"
    "ds_read_b128 %3, %9 offset:256\n"

    "ds_read_b128 %4, %8 offset:512\n"
    "ds_read_b128 %5, %8 offset:512+256\n"
    "ds_read_b128 %6, %9 offset:512\n"
    "ds_read_b128 %7, %9 offset:512+256\n"
    "s_waitcnt lgkmcnt(0)\n"
    :"=v"(rA[0]),"=v"(rA[1]),"=v"(rA[2]),"=v"(rA[3]),
    "=v"(rB[0]),"=v"(rB[1]),"=v"(rB[2]),"=v"(rB[3])
    :"v"(ldsReadA),"v"(ldsReadB)
    );

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
//    global_load_off0_f32x4(tmpC, &c[11]);
//    global_load_off16_f32x4(tmpC, &c[15]);

    __asm volatile(
    "global_load_dwordx4 %0, %2, off \n"
    "global_load_dwordx4 %1, %2, off offset:16*4*4\n"
    "s_waitcnt vmcnt(0)\n"
    :"=v"(c[11]),"=v"(c[15])
    :"v"(tmpC));

    c[0].x += rA[0].x * rB[0].x;
    c[0].y += rA[0].y * rB[0].x;
    c[0].z += rA[0].z * rB[0].x;
    c[0].w += rA[0].w * rB[0].x;

    c[1].x += rA[1].x * rB[0].y;
    c[1].y += rA[1].y * rB[0].y;
    c[1].z += rA[1].z * rB[0].y;
    c[1].w += rA[1].w * rB[0].y;

    c[2].x += rA[2].x * rB[0].z;
    c[2].y += rA[2].y * rB[0].z;
    c[2].z += rA[2].z * rB[0].z;
    c[2].w += rA[2].w * rB[0].z;

    c[3].x += rA[3].x * rB[0].w;
    c[3].y += rA[3].y * rB[0].w;
    c[3].z += rA[3].z * rB[0].w;
    c[3].w += rA[3].w * rB[0].w;


    c[4].x += rA[0].x * rB[1].x;
    c[4].y += rA[0].y * rB[1].x;
    c[4].z += rA[0].z * rB[1].x;
    c[4].w += rA[0].w * rB[1].x;

    c[5].x += rA[1].x * rB[1].y;
    c[5].y += rA[1].y * rB[1].y;
    c[5].z += rA[1].z * rB[1].y;
    c[5].w += rA[1].w * rB[1].y;

    c[6].x += rA[2].x * rB[1].z;
    c[6].y += rA[2].y * rB[1].z;
    c[6].z += rA[2].z * rB[1].z;
    c[6].w += rA[2].w * rB[1].z;

    c[7].x += rA[3].x * rB[1].w;
    c[7].y += rA[3].y * rB[1].w;
    c[7].z += rA[3].z * rB[1].w;
    c[7].w += rA[3].w * rB[1].w;


    c[8].x += rA[0].x * rB[2].x;
    c[8].y += rA[0].y * rB[2].x;
    c[8].z += rA[0].z * rB[2].x;
    c[8].w += rA[0].w * rB[2].x;

    c[9].x += rA[1].x * rB[2].y;
    c[9].y += rA[1].y * rB[2].y;
    c[9].z += rA[1].z * rB[2].y;
    c[9].w += rA[1].w * rB[2].y;

    c[10].x += rA[2].x * rB[2].z;
    c[10].y += rA[2].y * rB[2].z;
    c[10].z += rA[2].z * rB[2].z;
    c[10].w += rA[2].w * rB[2].z;

    c[11].x += rA[3].x * rB[2].w;
    c[11].y += rA[3].y * rB[2].w;
    c[11].z += rA[3].z * rB[2].w;
    c[11].w += rA[3].w * rB[2].w;


    c[12].x += rA[0].x * rB[3].x;
    c[12].y += rA[0].y * rB[3].x;
    c[12].z += rA[0].z * rB[3].x;
    c[12].w += rA[0].w * rB[3].x;

    c[13].x += rA[1].x * rB[3].y;
    c[13].y += rA[1].y * rB[3].y;
    c[13].z += rA[1].z * rB[3].y;
    c[13].w += rA[1].w * rB[3].y;

    c[14].x += rA[2].x * rB[3].z;
    c[14].y += rA[2].y * rB[3].z;
    c[14].z += rA[2].z * rB[3].z;
    c[14].w += rA[2].w * rB[3].z;

    c[15].x += rA[3].x * rB[3].w;
    c[15].y += rA[3].y * rB[3].w;
    c[15].z += rA[3].z * rB[3].w;
    c[15].w += rA[3].w * rB[3].w;





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

    tmpC = C + 64*1024 + cid0;
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
