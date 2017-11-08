#pragma once

inline __device__ void global_blocks(float4* &ptr, float4 &val, uint32_t offset) {
asm volatile("\n \
  global_load_dwordx4 %0, %1, off \n \
  "
  :"=v"(val)
  :"v"(ptr));
}