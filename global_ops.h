#pragma once

inline __device__ void global_load(float4* &ptr, float4 &val, uint32_t offset) {
asm volatile("\n \
  global_load_dwordx4 %0, %1, off \n \
  "
  :"=v"(val)
  :"v"(ptr));
}

inline __device__ void global_load_16(float4* &ptr, float4 &val, uint32_t offset) {
asm volatile("\n \
  global_load_dwordx4 %0, %1, off offset:256\n \
  "
  :"=v"(val)
  :"v"(ptr));
}
