#pragma once

#include <hip/hip_runtime.h>
#include "datatypes.h"

template<uint32_t offset>
inline __device__ void global_load(Float4* ptr, Float4 &val) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_load_dwordx4 %0, %1, off \n \
    "
    :"=v"(val)
    :"v"(ptr));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_load_dwordx4 %0, %1, off offset:16*4*4 \n \
    "
    :"=v"(val)
    :"v"(ptr));
    }
}

template<uint32_t offset>
inline __device__ void global_load(Half4* ptr, Half4& val) {
    if(offset == 0*32) {
      asm volatile("\n \
      global_load_dwordx2 %0, %1, off \n \
      "
      :"=v"(val)
      :"v"(ptr));
    }
    if(offset == 16) {
      asm volatile("\n \
      global_load_dwordx2 %0, %1, off offset:16*4*2 \n \
      "
      :"=v"(val)
      :"v"(ptr));
    }
}

template<uint32_t offset>
inline __device__ void global_load(Half2x4* ptr, Half2x4 &val) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_load_dwordx4 %0, %1, off \n \
    "
    :"=v"(val)
    :"v"(ptr));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_load_dwordx4 %0, %1, off offset:16*4*4 \n \
    "
    :"=v"(val)
    :"v"(ptr));
    }
}

template<uint32_t offset>
inline __device__ void global_load(Float4* ptr, Float4 &val, uint32_t off) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_load_dwordx4 %0, %1, off \n \
    "
    :"=v"(val)
    :"v"(ptr + off));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_load_dwordx4 %0, %1, off offset:16*4*4 \n \
    "
    :"=v"(val)
    :"v"(ptr + off));
    }
}

template<uint32_t offset>
inline __device__ void global_load(Half2x4* ptr, Half2x4 &val, uint32_t off) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_load_dwordx4 %0, %1, off \n \
    "
    :"=v"(val)
    :"v"(ptr + off));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_load_dwordx4 %0, %1, off offset:16*4*4 \n \
    "
    :"=v"(val)
    :"v"(ptr + off));
    }
}

template<uint32_t offset>
inline __device__ void global_load(Half4* ptr, Half4 &val, uint32_t off) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_load_dwordx2 %0, %1, off \n \
    "
    :"=v"(val)
    :"v"(ptr + off));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_load_dwordx2 %0, %1, off offset:16*4*4 \n \
    "
    :"=v"(val)
    :"v"(ptr + off));
    }
}


template<uint32_t offset>
inline __device__ void global_store(Float4* ptr, Float4 &val) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_store_dwordx4 %1, %0, off \n \
    "
    :
    :"v"(val), "v"(ptr));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_store_dwordx4 %1, %0, off offset:16*4*4 \n \
    "
    :
    :"v"(val), "v"(ptr));
    }
}


template<uint32_t offset>
inline __device__ void global_store(Half2x4* ptr, Half2x4 &val) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_store_dwordx4 %1, %0, off \n \
    "
    :
    :"v"(val), "v"(ptr));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_store_dwordx4 %1, %0, off offset:16*4*4 \n \
    "
    :
    :"v"(val), "v"(ptr));
    }
}

template<uint32_t offset>
inline __device__ void global_store(Float4* ptr, Float4 &val, uint32_t off) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_store_dwordx4 %1, %0, off \n \
    "
    :
    :"v"(val), "v"(ptr + off));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_store_dwordx4 %1, %0, off offset:16*4*4 \n \
    "
    :
    :"v"(val), "v"(ptr + off));
    }
}

template<uint32_t offset>
inline __device__ void global_store(Half2x4* ptr, Half2x4 &val, uint32_t off) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_store_dwordx4 %1, %0, off \n \
    "
    :
    :"v"(val), "v"(ptr + off));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_store_dwordx4 %1, %0, off offset:16*4*4 \n \
    "
    :
    :"v"(val), "v"(ptr + off));
    }
}


template<uint32_t offset>
inline __device__ void global_store(Half4* ptr, Half4 &val) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_store_dwordx2 %1, %0, off \n \
    "
    :
    :"v"(val), "v"(ptr));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_store_dwordx2 %1, %0, off offset:16*4*4 \n \
    "
    :
    :"v"(val), "v"(ptr));
    }
}

template<uint32_t offset>
inline __device__ void global_store(Half4* ptr, Half4 &val, uint32_t off) {
    if(offset == 0*32) {
    asm volatile("\n \
    global_store_dwordx2 %1, %0, off \n \
    "
    :
    :"v"(val), "v"(ptr + off));
    return;
    }
    if(offset == 16) {
    asm volatile("\n \
    global_store_dwordx2 %1, %0, off offset:16*4*4 \n \
    "
    :
    :"v"(val), "v"(ptr + off));
    }
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
