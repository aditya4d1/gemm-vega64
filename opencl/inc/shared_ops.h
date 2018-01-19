#pragma once

inline void shared_read_b128_0(__local float4 *ldsA, \
                                __local float4 *ldsB, \
                                float4 *a0, float4 *a1, \
                                float4 *b0, float4 *b1)
{
    __asm(
    "ds_read_b128 %0, %4 offset:0\n"
    "ds_read_b128 %1, %4 offset:256\n"
    "ds_read_b128 %2, %5 offset:0\n"
    "ds_read_b128 %3, %5 offset:256\n"
    :"=v"(*a0),"=v"(*a1),"=v"(*b0),"=v"(*b1)
    :"v"(ldsA), "v"(ldsB)
    );
}

inline void shared_read_b128_512(__local float4 *ldsA, \
                                __local float4 *ldsB, \
                                float4 *a0, float4 *a1, \
                                float4 *b0, float4 *b1)
{
    __asm(
    "ds_read_b128 %0, %4 offset:512+0\n"
    "ds_read_b128 %1, %4 offset:512+256\n"
    "ds_read_b128 %2, %5 offset:512+0\n"
    "ds_read_b128 %3, %5 offset:512+256\n"
    :"=v"(*a0),"=v"(*a1),"=v"(*b0),"=v"(*b1)
    :"v"(ldsA), "v"(ldsB)
    );
}

inline void shared_read_b128_1024(__local float4 *ldsA, \
                                __local float4 *ldsB, \
                                float4 *a0, float4 *a1, \
                                float4 *b0, float4 *b1)
{
    __asm(
    "ds_read_b128 %0, %4 offset:1024+0\n"
    "ds_read_b128 %1, %4 offset:1024+256\n"
    "ds_read_b128 %2, %5 offset:1024+0\n"
    "ds_read_b128 %3, %5 offset:1024+256\n"
    :"=v"(*a0),"=v"(*a1),"=v"(*b0),"=v"(*b1)
    :"v"(ldsA), "v"(ldsB)
    );
}

inline void shared_read_b128_1536(__local float4 *ldsA, \
                                __local float4 *ldsB, \
                                float4 *a0, float4 *a1, \
                                float4 *b0, float4 *b1)
{
    __asm(
    "ds_read_b128 %0, %4 offset:3*512+0\n"
    "ds_read_b128 %1, %4 offset:3*512+256\n"
    "ds_read_b128 %2, %5 offset:3*512+0\n"
    "ds_read_b128 %3, %5 offset:3*512+256\n"
    :"=v"(*a0),"=v"(*a1),"=v"(*b0),"=v"(*b1)
    :"v"(ldsA), "v"(ldsB)
    );
}

inline void shared_read_b128_2048(__local float4 *ldsA, \
                                __local float4 *ldsB, \
                                float4 *a0, float4 *a1, \
                                float4 *b0, float4 *b1)
{
    __asm(
    "ds_read_b128 %0, %4 offset:4*512+0\n"
    "ds_read_b128 %1, %4 offset:4*512+256\n"
    "ds_read_b128 %2, %5 offset:4*512+0\n"
    "ds_read_b128 %3, %5 offset:4*512+256\n"
    :"=v"(*a0),"=v"(*a1),"=v"(*b0),"=v"(*b1)
    :"v"(ldsA), "v"(ldsB)
    );
}

inline void shared_read_b128_2560(__local float4 *ldsA, \
                                __local float4 *ldsB, \
                                float4 *a0, float4 *a1, \
                                float4 *b0, float4 *b1)
{
    __asm(
    "ds_read_b128 %0, %4 offset:5*512+0\n"
    "ds_read_b128 %1, %4 offset:5*512+256\n"
    "ds_read_b128 %2, %5 offset:5*512+0\n"
    "ds_read_b128 %3, %5 offset:5*512+256\n"
    :"=v"(*a0),"=v"(*a1),"=v"(*b0),"=v"(*b1)
    :"v"(ldsA), "v"(ldsB)
    );
}

inline void shared_read_b128_3072(__local float4 *ldsA, \
                                __local float4 *ldsB, \
                                float4 *a0, float4 *a1, \
                                float4 *b0, float4 *b1)
{
    __asm(
    "ds_read_b128 %0, %4 offset:6*512+0\n"
    "ds_read_b128 %1, %4 offset:6*512+256\n"
    "ds_read_b128 %2, %5 offset:6*512+0\n"
    "ds_read_b128 %3, %5 offset:6*512+256\n"
    :"=v"(*a0),"=v"(*a1),"=v"(*b0),"=v"(*b1)
    :"v"(ldsA), "v"(ldsB)
    );
}

inline void shared_read_b128_3584(__local float4 *ldsA, \
                                __local float4 *ldsB, \
                                float4 *a0, float4 *a1, \
                                float4 *b0, float4 *b1)
{
    __asm(
    "ds_read_b128 %0, %4 offset:7*512+0\n"
    "ds_read_b128 %1, %4 offset:7*512+256\n"
    "ds_read_b128 %2, %5 offset:7*512+0\n"
    "ds_read_b128 %3, %5 offset:7*512+256\n"
    :"=v"(*a0),"=v"(*a1),"=v"(*b0),"=v"(*b1)
    :"v"(ldsA), "v"(ldsB)
    );
}


inline void shared_write_b128_0(__local float4 *lds, float4 *val) {
    __asm(
    "ds_write_b128 %0, %1 \n"
    :
    :"v"(lds), "v"(*val)
    );
}

inline void shared_write_b128_4096(__local float4 *lds, float4 *val) {
    __asm(
    "ds_write_b128 %0, %1 offset:4096 \n"
    :
    :"v"(lds), "v"(*val)
    );
}
