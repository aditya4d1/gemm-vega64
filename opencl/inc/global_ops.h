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

inline void vmcnt0() {
    __asm(
    "s_waitcnt vmcnt(0)\n"
    :
    :
    );
}

inline void lgkmcnt0(){
    __asm(
    "s_waitcnt lgkmcnt(0)\n"
    :
    :
    );
}

inline void lgkmcnt1(){
    __asm(
    "s_waitcnt lgkmcnt(1)\n"
    :
    :
    );
}

inline void lgkmcnt2(){
    __asm(
    "s_waitcnt lgkmcnt(2)\n"
    :
    :
    );
}

inline void lgkmcnt3(){
    __asm(
    "s_waitcnt lgkmcnt(3)\n"
    :
    :
    );
}

inline void lgkmcnt4(){
    __asm(
    "s_waitcnt lgkmcnt(4)\n"
    :
    :
    );
}

