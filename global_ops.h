#pragma once

#include <hip/hip_runtime.h>
#include "datatypes.h"

inline __device__ void global_load(Float4* &ptr, Float4 &val, uint32_t offset) {
asm volatile("\n \
  global_load_dwordx4 %0, %1, off \n \
  "
  :"=v"(val)
  :"v"(ptr+offset));
}

inline __device__ void global_load_16(Float4* &ptr, Float4 &val, uint32_t offset) {
asm volatile("\n \
  global_load_dwordx4 %0, %1, off offset:256\n \
  "
  :"=v"(val)
  :"v"(ptr+offset));
}

inline __device__ void global_store(Float4* &ptr, Float4 &val, uint32_t offset) {
asm volatile("\n \
  global_store_dwordx4 %1, %0, off \n \
  "
  :
  :"v"(val), "v"(ptr+offset));
}

inline __device__ void global_store_16(Float4* &ptr, Float4 &val, uint32_t offset) {
asm volatile("\n \
  global_store_dwordx4 %1, %0, off offset:256 \n \
  "
  :
  :"v"(val), "v"(ptr+offset));
}

template<uint32_t cnt>
inline __device__ void lgkmcnt(){
  if(cnt == 0) {
    asm volatile("\n \
    s_waitcnt lgkmcnt(0) \n \
    "::);
  }
  if(cnt == 1) {
    asm volatile("\n \
    s_waitcnt lgkmcnt(1) \n \
    "::);
  }
  if(cnt == 2) {
    asm volatile("\n \
    s_waitcnt lgkmcnt(2) \n \
    "::);
  }
  if(cnt == 3) {
    asm volatile("\n \
    s_waitcnt lgkmcnt(3) \n \
    "::);
  }
  if(cnt == 4) {
    asm volatile("\n \
    s_waitcnt lgkmcnt(4) \n \
    "::);
  }
  if(cnt == 5) {
    asm volatile("\n \
    s_waitcnt lgkmcnt(5) \n \
    "::);
  }
  if(cnt == 6) {
    asm volatile("\n \
    s_waitcnt lgkmcnt(6) \n \
    "::);
  }

/**
* Disabling as 16 is to high to fit in 4bits (15 max)
  if(cnt == 16) {
    asm volatile("\n \
    s_waitcnt lgkmcnt(16) \n \
    "::);
  }
*/
}

template<uint32_t cnt>
inline __device__ void vmcnt() {
    if(cnt == 0) {
      asm volatile ("\n \
      s_waitcnt vmcnt(0) \n \
      "::);
    }
    if(cnt == 1) {
      asm volatile ("\n \
      s_waitcnt vmcnt(1) \n \
      "::);
    }
    if(cnt == 2) {
      asm volatile ("\n \
      s_waitcnt vmcnt(2) \n \
      "::);
    }
    if(cnt == 4) {
      asm volatile ("\n \
      s_waitcnt vmcnt(2) \n \
      "::);
    }
}
