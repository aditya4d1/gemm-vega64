

__kernel void Main(__global float4 *A, __global float4 *B, __global float4 *C) {
    int lid = get_local_id(0);
    float4 a, b, c[4];

    __asm(
    "global_load_dwordx4 %0, %4, off \n"
    "global_load_dwordx4 %1, %5, off \n"
    "global_load_dwordx4 %2, %6, off \n"
    "global_load_dwordx4 %3, %7, off \n"
    :"=v"(c[0]), "=v"(c[1]), "=v"(c[2]), "=v"(c[3])
    :"v"(C + 4 * lid + 0), "v"(C + 4 * lid + 1), "v"(C + 4 * lid + 2), "v"(C + 4 * lid + 3)
    );


    __asm(
    "global_load_dwordx4 %0, %1, off \n"
    :"=v"(a)
    :"v"(A + lid)
    );

    __asm(
    "global_load_dwordx4 %0, %1, off \n"
    :"=v"(b)
    :"v"(B + lid)
    );

    __asm(
    "s_waitcnt vmcnt(0)\n"
    ::
    );


    __asm(
    "v_mac_f32 %0, %16, %20\n"
    "v_mac_f32 %1, %16, %21\n"
    "v_mac_f32 %2, %16, %22\n"
    "v_mac_f32 %3, %16, %23\n"

    "v_mac_f32 %4, %17, %20\n"
    "v_mac_f32 %5, %17, %21\n"
    "v_mac_f32 %6, %17, %22\n"
    "v_mac_f32 %7, %17, %23\n"

    "v_mac_f32 %8, %18, %20\n"
    "v_mac_f32 %9, %18, %21\n"
    "v_mac_f32 %10, %18, %22\n"
    "v_mac_f32 %11, %18, %23\n"

    "v_mac_f32 %12, %19, %20\n"
    "v_mac_f32 %13, %19, %21\n"
    "v_mac_f32 %14, %19, %22\n"
    "v_mac_f32 %15, %19, %23\n"
    :
    :"v"(c[0].x),"v"(c[0].y),"v"(c[0].z),"v"(c[0].w),
    "v"(c[1].x),"v"(c[1].y),"v"(c[1].z),"v"(c[1].w),
    "v"(c[2].x),"v"(c[2].y),"v"(c[2].z),"v"(c[2].w),
    "v"(c[3].x),"v"(c[3].y),"v"(c[3].z),"v"(c[3].w),
    "v"(a.x),"v"(a.y),"v"(a.z),"v"(a.w),
    "v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w)
    );

    __asm(
    "global_store_dwordx4 %0, %1, off\n"
    "global_store_dwordx4 %2, %3, off\n"
    "global_store_dwordx4 %4, %5, off\n"
    "global_store_dwordx4 %6, %7, off\n"
    :
    :"v"(C + 4 * lid + 0), "v"(c[0]),
    "v"(C + 4 * lid + 1), "v"(c[1]),
    "v"(C + 4 * lid + 2), "v"(c[2]),
    "v"(C + 4 * lid + 3), "v"(c[3])
    );

}
