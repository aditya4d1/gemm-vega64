#include"/home/aditya/gemm-vega64/opencl/inc/global_ops.h"
#include"/home/aditya/gemm-vega64/opencl/inc/outer_product.h"

__kernel void Main(__global float4 *A, __global float4 *B, __global float4 *C) {
    int lid = get_local_id(0);
    float4 a, b, c[4];

    global_load_off0_f32x4(A, &a);
    global_load_off0_f32x4(B, &b);

    global_load_off0_f32x4(C + 4 * lid + 0, &c[0]);
    global_load_off0_f32x4(C + 4 * lid + 1, &c[1]);
    global_load_off0_f32x4(C + 4 * lid + 2, &c[2]);
    global_load_off0_f32x4(C + 4 * lid + 3, &c[3]);

    vmcnt0();

    __local float4 s[2];

    __asm(
    "ds_write_b128 %0, %1\n"
    :
    :"v"(s),"v"(a)
    );

    __asm(
    "ds_write_b128 %0, %1\n"
    :
    :"v"(s+1),"v"(b)
    );

    op_4x4f(&a, &b, &c[0], &c[1], &c[2], &c[3]);

    global_store_off0_f32x4(C + 4 * lid + 0, &c[0]);
    global_store_off0_f32x4(C + 4 * lid + 1, &c[1]);
    global_store_off0_f32x4(C + 4 * lid + 2, &c[2]);
    global_store_off0_f32x4(C + 4 * lid + 3, &c[3]);
}
