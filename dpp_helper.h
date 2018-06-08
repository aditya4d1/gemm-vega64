#pragma once

template<unsigned off>
inline void __device__ shared_read_b128(Float4 &a0, Float4 &a1, Float4 &b, unsigned ldsReadA, unsigned ldsReadB) {
    if(off == 0) {
        asm volatile("\n\
        ds_read_b128 %0, %3 offset:0 \n\
        ds_read_b128 %1, %4 offset:0 \n\
        ds_read_b128 %2, %4 offset:256 \n\
        "
        :"=v"(b),"=v"(a0),"=v"(a1)
        :"v"(ldsReadA),"v"(ldsReadB)
        );
    }
    if(off == 512) {
        asm volatile("\n\
        ds_read_b128 %0, %3 offset:512 \n\
        ds_read_b128 %1, %4 offset:512 \n\
        ds_read_b128 %2, %4 offset:256+512 \n\
        "
        :"=v"(b),"=v"(a0),"=v"(a1)
        :"v"(ldsReadA),"v"(ldsReadB)
        );
    }
    if(off == 2*512) {
        asm volatile("\n\
        ds_read_b128 %0, %3 offset:0+2*512 \n\
        ds_read_b128 %1, %4 offset:0+2*512 \n\
        ds_read_b128 %2, %4 offset:256+2*512 \n\
        "
        :"=v"(b),"=v"(a0),"=v"(a1)
        :"v"(ldsReadA),"v"(ldsReadB)
        );
    }
    if(off == 3*512) {
        asm volatile("\n\
        ds_read_b128 %0, %3 offset:0+3*512 \n\
        ds_read_b128 %1, %4 offset:0+3*512 \n\
        ds_read_b128 %2, %4 offset:256+3*512 \n\
        "
        :"=v"(b),"=v"(a0),"=v"(a1)
        :"v"(ldsReadA),"v"(ldsReadB)
        );
    }
    if(off == 4*512) {
        asm volatile("\n\
        ds_read_b128 %0, %3 offset:0+4*512 \n\
        ds_read_b128 %1, %4 offset:0+4*512 \n\
        ds_read_b128 %2, %4 offset:256+4*512 \n\
        "
        :"=v"(b),"=v"(a0),"=v"(a1)
        :"v"(ldsReadA),"v"(ldsReadB)
        );
    }
    if(off == 5*512) {
        asm volatile("\n\
        ds_read_b128 %0, %3 offset:5*512 \n\
        ds_read_b128 %1, %4 offset:5*512 \n\
        ds_read_b128 %2, %4 offset:256+5*512 \n\
        "
        :"=v"(b),"=v"(a0),"=v"(a1)
        :"v"(ldsReadA),"v"(ldsReadB)
        );
    }
    if(off == 6*512) {
        asm volatile("\n\
        ds_read_b128 %0, %3 offset:6*512 \n\
        ds_read_b128 %1, %4 offset:6*512 \n\
        ds_read_b128 %2, %4 offset:256+6*512 \n\
        "
        :"=v"(b),"=v"(a0),"=v"(a1)
        :"v"(ldsReadA),"v"(ldsReadB)
        );
    }
    if(off == 7*512) {
        asm volatile("\n\
        ds_read_b128 %0, %3 offset:7*512 \n\
        ds_read_b128 %1, %4 offset:7*512 \n\
        ds_read_b128 %2, %4 offset:256+7*512 \n\
        "
        :"=v"(b),"=v"(a0),"=v"(a1)
        :"v"(ldsReadA),"v"(ldsReadB)
        );
    }
}


inline __device__ void outerProduct4x4(Float4 &a0, Float4 &a1, Float4 &b, \
    Float4 &c0, Float4 &c1, Float4 &c2, Float4 &c3, \
    Float4 &c4, Float4 &c5, Float4 &c6, Float4 &c7, \
    Float4 &c8, Float4 &c9, Float4 &c10, Float4 &c11, \
    Float4 &c12, Float4 &c13, Float4 &c14, Float4 &c15)
{
    asm volatile("\n\
    v_mac_f32_dpp %0, %8, %9 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %1, %8, %10 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %2, %8, %11 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %3, %8, %12 quad_perm:[0,0,2,2] \n\
    \
    v_mac_f32_dpp %4, %8, %9 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %5, %8, %10 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %6, %8, %11 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %7, %8, %12 quad_perm:[1,1,3,3] \n\
    "
    :"=v"(c0.x),"=v"(c0.y),"=v"(c0.z),"=v"(c0.w),
    "=v"(c4.x),"=v"(c4.y),"=v"(c4.z),"=v"(c4.w)
    :"v"(a0.x),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w)
    );

    asm volatile("\n\
    v_mac_f32_dpp %0, %8, %9 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %1, %8, %10 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %2, %8, %11 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %3, %8, %12 quad_perm:[0,0,2,2] \n\
    \
    v_mac_f32_dpp %4, %8, %9 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %5, %8, %10 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %6, %8, %11 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %7, %8, %12 quad_perm:[1,1,3,3] \n\
    "
    :"=v"(c1.x),"=v"(c1.y),"=v"(c1.z),"=v"(c1.w),
    "=v"(c5.x),"=v"(c5.y),"=v"(c5.z),"=v"(c5.w)
    :"v"(a0.y),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w)
    );

        asm volatile("\n\
    v_mac_f32_dpp %0, %8, %9 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %1, %8, %10 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %2, %8, %11 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %3, %8, %12 quad_perm:[0,0,2,2] \n\
    \
    v_mac_f32_dpp %4, %8, %9 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %5, %8, %10 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %6, %8, %11 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %7, %8, %12 quad_perm:[1,1,3,3] \n\
    "
    :"=v"(c2.x),"=v"(c2.y),"=v"(c2.z),"=v"(c2.w),
    "=v"(c6.x),"=v"(c6.y),"=v"(c6.z),"=v"(c6.w)
    :"v"(a0.z),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w)
    );

        asm volatile("\n\
    v_mac_f32_dpp %0, %8, %9 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %1, %8, %10 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %2, %8, %11 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %3, %8, %12 quad_perm:[0,0,2,2] \n\
    \
    v_mac_f32_dpp %4, %8, %9 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %5, %8, %10 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %6, %8, %11 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %7, %8, %12 quad_perm:[1,1,3,3] \n\
    "
    :"=v"(c3.x),"=v"(c3.y),"=v"(c3.z),"=v"(c3.w),
    "=v"(c7.x),"=v"(c7.y),"=v"(c7.z),"=v"(c7.w)
    :"v"(a0.w),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w)
    );

        asm volatile("\n\
    v_mac_f32_dpp %0, %8, %9 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %1, %8, %10 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %2, %8, %11 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %3, %8, %12 quad_perm:[0,0,2,2] \n\
    \
    v_mac_f32_dpp %4, %8, %9 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %5, %8, %10 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %6, %8, %11 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %7, %8, %12 quad_perm:[1,1,3,3] \n\
    "
    :"=v"(c8.x),"=v"(c8.y),"=v"(c8.z),"=v"(c8.w),
    "=v"(c12.x),"=v"(c12.y),"=v"(c12.z),"=v"(c12.w)
    :"v"(a1.x),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w)
    );


        asm volatile("\n\
    v_mac_f32_dpp %0, %8, %9 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %1, %8, %10 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %2, %8, %11 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %3, %8, %12 quad_perm:[0,0,2,2] \n\
    \
    v_mac_f32_dpp %4, %8, %9 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %5, %8, %10 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %6, %8, %11 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %7, %8, %12 quad_perm:[1,1,3,3] \n\
    "
    :"=v"(c9.x),"=v"(c9.y),"=v"(c9.z),"=v"(c9.w),
    "=v"(c13.x),"=v"(c13.y),"=v"(c13.z),"=v"(c13.w)
    :"v"(a1.y),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w)
    );


        asm volatile("\n\
    v_mac_f32_dpp %0, %8, %9 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %1, %8, %10 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %2, %8, %11 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %3, %8, %12 quad_perm:[0,0,2,2] \n\
    \
    v_mac_f32_dpp %4, %8, %9 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %5, %8, %10 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %6, %8, %11 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %7, %8, %12 quad_perm:[1,1,3,3] \n\
    "
    :"=v"(c10.x),"=v"(c10.y),"=v"(c10.z),"=v"(c10.w),
    "=v"(c14.x),"=v"(c14.y),"=v"(c14.z),"=v"(c14.w)
    :"v"(a1.z),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w)
    );


        asm volatile("\n\
    v_mac_f32_dpp %0, %8, %9 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %1, %8, %10 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %2, %8, %11 quad_perm:[0,0,2,2] \n\
    v_mac_f32_dpp %3, %8, %12 quad_perm:[0,0,2,2] \n\
    \
    v_mac_f32_dpp %4, %8, %9 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %5, %8, %10 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %6, %8, %11 quad_perm:[1,1,3,3] \n\
    v_mac_f32_dpp %7, %8, %12 quad_perm:[1,1,3,3] \n\
    "
    :"=v"(c11.x),"=v"(c11.y),"=v"(c11.z),"=v"(c11.w),
    "=v"(c15.x),"=v"(c15.y),"=v"(c15.z),"=v"(c15.w)
    :"v"(a1.w),"v"(b.x),"v"(b.y),"v"(b.z),"v"(b.w)
    );
}
