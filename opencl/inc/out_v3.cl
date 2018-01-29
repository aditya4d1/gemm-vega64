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

    global_load_off0_f32x4(A + a_global_id, &ra);
    global_load_off0_f32x4(B + b_global_id, &rb);

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

    __asm(
    "ds_write_b128 %0, %2 offset:0\n"
    "ds_write_b128 %1, %3 offset:4096\n"
    "s_waitcnt lgkmcnt(0)\n"
    ::"v"(ldsWriteA), "v"(ldsWriteB), "v"(ra), "v"(rb)
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
    "s_waitcnt lgkmcnt(0)\n"
    :"=v"(rA[0]),"=v"(rA[1]),"=v"(rA[2]),"=v"(rA[3]),
    "=v"(rB[0]),"=v"(rB[1]),"=v"(rB[2]),"=v"(rB[3])
    :"v"(ldsReadA),"v"(ldsReadB)
    );

    __asm(
    "v_add_f32 %0, %4, 1.0\n"
    "v_add_f32 %1, %4, 1.0\n"
    "v_add_f32 %2, %4, 1.0\n"
    "v_add_f32 %3, %4, 1.0\n":
    "=v"(c[0].x),"=v"(c[0].y),"=v"(c[0].z),"=v"(c[0].w):
    "v"(rA[0].x)
    );

    __asm(
    "v_add_f32 %0, %4, 1.0\n"
    "v_add_f32 %1, %4, 1.0\n"
    "v_add_f32 %2, %4, 1.0\n"
    "v_add_f32 %3, %4, 1.0\n":
    "=v"(c[1].x),"=v"(c[1].y),"=v"(c[1].z),"=v"(c[1].w):
    "v"(rA[1].x)
    );

    __asm(
    "v_add_f32 %0, %4, 1.0\n"
    "v_add_f32 %1, %4, 1.0\n"
    "v_add_f32 %2, %4, 1.0\n"
    "v_add_f32 %3, %4, 1.0\n":
    "=v"(c[2].x),"=v"(c[2].y),"=v"(c[2].z),"=v"(c[2].w):
    "v"(rA[2].x)
    );

    __asm(
    "v_add_f32 %0, %4, 1.0\n"
    "v_add_f32 %1, %4, 1.0\n"
    "v_add_f32 %2, %4, 1.0\n"
    "v_add_f32 %3, %4, 1.0\n":
    "=v"(c[3].x),"=v"(c[3].y),"=v"(c[3].z),"=v"(c[3].w):
    "v"(rA[3].x)
    );

    __asm(
    "v_add_f32 %0, %4, 1.0\n"
    "v_add_f32 %1, %4, 1.0\n"
    "v_add_f32 %2, %4, 1.0\n"
    "v_add_f32 %3, %4, 1.0\n":
    "=v"(c[4].x),"=v"(c[4].y),"=v"(c[4].z),"=v"(c[4].w):
    "v"(rB[0].x)
    );

    __asm(
    "v_add_f32 %0, %4, 1.0\n"
    "v_add_f32 %1, %4, 1.0\n"
    "v_add_f32 %2, %4, 1.0\n"
    "v_add_f32 %3, %4, 1.0\n":
    "=v"(c[5].x),"=v"(c[5].y),"=v"(c[5].z),"=v"(c[5].w):
    "v"(rB[1].x)
    );

    __asm(
    "v_add_f32 %0, %4, 1.0\n"
    "v_add_f32 %1, %4, 1.0\n"
    "v_add_f32 %2, %4, 1.0\n"
    "v_add_f32 %3, %4, 1.0\n":
    "=v"(c[6].x),"=v"(c[6].y),"=v"(c[6].z),"=v"(c[6].w):
    "v"(rB[2].x)
    );

    __asm(
    "v_add_f32 %0, %4, 1.0\n"
    "v_add_f32 %1, %4, 1.0\n"
    "v_add_f32 %2, %4, 1.0\n"
    "v_add_f32 %3, %4, 1.0\n":
    "=v"(c[7].x),"=v"(c[7].y),"=v"(c[7].z),"=v"(c[7].w):
    "v"(rB[3].x)
    );




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
