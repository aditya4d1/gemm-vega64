#pragma once

inline void global_load_off0_f32x4(__global float4* ptr, float4 *val) {
    __asm volatile(
    "\n \
    global_load_dwordx4 %0, %1 off \n \
    "
    :"=v"(*val)
    :"v"(ptr)
    );
}

inline void global_load_off16_f32x4(__global float4 *ptr, float4 *val) {
    __asm volatile(
    "\n \
    global_load_dwordx4 %0, %1 off offset:16*4*4 \n \
    "
    :"=v"(*val)
    :"v"(ptr)
    );
}

inline void global_load_off0_f32x4_off(__global float4 *ptr, float4 *val, unsigned off) {
    __asm volatile(
    "\n \
    global_load_dwordx4 %0, %1 off \n \
    "
    :"=v"(*val)
    :"v"(ptr + off)
    );
}

inline void global_load_off16_f32x4_off(__global float4 *ptr, float4 *val, unsigned off) {
    __asm volatile(
    "\n \
    global_load_dwordx4 %0, %1 off offset:16*4*4 \n \
    "
    :"=v"(*val)
    :"v"(ptr + off)
    );
}


inline void global_store_off0_f32x4(__global float4* ptr, float4 *val) {
    __asm volatile(
    "\n \
    global_store_dwordx4 %1, %0 off \n \
    "
    :
    :"v"(*val), "v"(ptr)
    );
}

inline void global_store_off16_f32x4(__global float4 *ptr, float4 *val) {
    __asm volatile(
    "\n \
    global_store_dwordx4 %1, %0 off offset:16*4*4 \n \
    "
    :
    :"v"(*val), "v"(ptr)
    );
}

inline void global_store_off0_f32x4_off(__global float4 *ptr, float4 *val, unsigned off) {
    __asm volatile(
    "\n \
    global_store_dwordx4 %1, %0 off \n \
    "
    :
    :"v"(*val), "v"(ptr + off)
    );
}

inline void global_store_off16_f32x4_off(__global float4 *ptr, float4 *val, unsigned off) {
    __asm volatile(
    "\n \
    global_store_dwordx4 %1, %0 off offset:16*4*4 \n \
    "
    :
    :"v"(*val), "v"(ptr + off)
    );
}


