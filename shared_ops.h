#pragma once

/**
* Format:   v_mov_b32 dst, src
* Example:  v_mov_b32 v4, 65536
*/
inline __device__ void shared_init(uint32_t &redA, uint32_t &redB, uint32_t &blueA, uint32_t &blueB) {
    asm volatile ("\n \
        v_mov_b32 %0, 0     \n \
        v_mov_b32 %1, 4096  \n \
        v_mov_b32 %2, 8192  \n \
        v_mov_b32 %3, 12288 \n \
        "
    :"=v"(redA),"=v"(redB),"=v"(blueA),"=v"(blueB)
    :
    );
}

/**
* Format:   ds_write_b128 src, dst
* Example:  ds_write_b128 v2, v[4:7]
*/
template<uint32_t offset>
inline __device__ void shared_write_b128_off(Float4 &val, uint32_t &lds) {
    if(offset == 0) {
    asm volatile("\n \
        ds_write_b128 %0, %1 \n \
        "
    :
    :"v"(lds),"v"(val)
    );
    return;
    }
    if(offset == 4096) {
      asm volatile("\n \
          ds_write_b128 %0, %1 offset:4096 \n \
          "
      :
      :"v"(lds),"v"(val)
      );
    }
}

template<uint32_t offset>
inline __device__ void shared_write_b128_off(Half2x4 &val, uint32_t &lds) {
    if(offset == 0) {
    asm volatile("\n \
        ds_write_b128 %0, %1 \n \
        "
    :
    :"v"(lds),"v"(val)
    );
    return;
    }
    if(offset == 4096) {
      asm volatile("\n \
          ds_write_b128 %0, %1 offset:4096 \n \
          "
      :
      :"v"(lds),"v"(val)
      );
    }
}

template<uint32_t offset>
inline __device__ void shared_write_b64_off(Half4 &val, uint32_t &lds) {
    if(offset == 0) {
    asm volatile("\n \
        ds_write_b64 %0, %1 \n \
        "
    :
    :"v"(lds),"v"(val)
    );
    return;
    }
    if(offset == 2048) {
      asm volatile("\n \
          ds_write_b64 %0, %1 offset:2048 \n \
          "
      :
      :"v"(lds),"v"(val)
      );
    }
}


inline __device__ void shared_write_b128(Float4 &val, uint32_t &lds) {
    asm volatile("\n \
    ds_write_b128 %0, %1 \n \
    "
    :
    :"v"(lds),"v"(val)
    );
}

inline __device__ void shared_write_b128(Half2x4 &val, uint32_t &lds) {
    asm volatile("\n \
    ds_write_b128 %0, %1 \n \
    "
    :
    :"v"(lds),"v"(val)
    );
}

template<uint32_t off>
inline __device__ void shared_read_b128(Float4 &a0, Float4 &a1, Float4 &b0, Float4 &b1, uint32_t &ldsA, uint32_t &ldsB) {
    if(off == 0) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:0 \n \
    ds_read_b128 %1, %4 offset:256 \n \
    ds_read_b128 %2, %5 offset:0 \n \
    ds_read_b128 %3, %5 offset:256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 1*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:1*512 \n \
    ds_read_b128 %1, %4 offset:1*512+256 \n \
    ds_read_b128 %2, %5 offset:1*512 \n \
    ds_read_b128 %3, %5 offset:1*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 2*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:2*512 \n \
    ds_read_b128 %1, %4 offset:2*512+256 \n \
    ds_read_b128 %2, %5 offset:2*512 \n \
    ds_read_b128 %3, %5 offset:2*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 3*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:3*512 \n \
    ds_read_b128 %1, %4 offset:3*512+256 \n \
    ds_read_b128 %2, %5 offset:3*512 \n \
    ds_read_b128 %3, %5 offset:3*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }

    if(off == 4*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:4*512 \n \
    ds_read_b128 %1, %4 offset:4*512+256 \n \
    ds_read_b128 %2, %5 offset:4*512 \n \
    ds_read_b128 %3, %5 offset:4*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 5*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:5*512 \n \
    ds_read_b128 %1, %4 offset:5*512+256 \n \
    ds_read_b128 %2, %5 offset:5*512 \n \
    ds_read_b128 %3, %5 offset:5*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 6*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:6*512 \n \
    ds_read_b128 %1, %4 offset:6*512+256 \n \
    ds_read_b128 %2, %5 offset:6*512 \n \
    ds_read_b128 %3, %5 offset:6*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 7*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:7*512 \n \
    ds_read_b128 %1, %4 offset:7*512+256 \n \
    ds_read_b128 %2, %5 offset:7*512 \n \
    ds_read_b128 %3, %5 offset:7*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
}

template<uint32_t off>
inline __device__ void shared_read_b128(Half2x4 &a0, Half2x4 &a1, Half2x4 &b0, Half2x4 &b1, uint32_t &ldsA, uint32_t &ldsB) {
    if(off == 0) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:0 \n \
    ds_read_b128 %1, %4 offset:256 \n \
    ds_read_b128 %2, %5 offset:0 \n \
    ds_read_b128 %3, %5 offset:256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 1*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:1*512 \n \
    ds_read_b128 %1, %4 offset:1*512+256 \n \
    ds_read_b128 %2, %5 offset:1*512 \n \
    ds_read_b128 %3, %5 offset:1*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 2*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:2*512 \n \
    ds_read_b128 %1, %4 offset:2*512+256 \n \
    ds_read_b128 %2, %5 offset:2*512 \n \
    ds_read_b128 %3, %5 offset:2*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 3*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:3*512 \n \
    ds_read_b128 %1, %4 offset:3*512+256 \n \
    ds_read_b128 %2, %5 offset:3*512 \n \
    ds_read_b128 %3, %5 offset:3*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }

    if(off == 4*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:4*512 \n \
    ds_read_b128 %1, %4 offset:4*512+256 \n \
    ds_read_b128 %2, %5 offset:4*512 \n \
    ds_read_b128 %3, %5 offset:4*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 5*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:5*512 \n \
    ds_read_b128 %1, %4 offset:5*512+256 \n \
    ds_read_b128 %2, %5 offset:5*512 \n \
    ds_read_b128 %3, %5 offset:5*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 6*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:6*512 \n \
    ds_read_b128 %1, %4 offset:6*512+256 \n \
    ds_read_b128 %2, %5 offset:6*512 \n \
    ds_read_b128 %3, %5 offset:6*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 7*512) {
    asm volatile("\n \
    ds_read_b128 %0, %4 offset:7*512 \n \
    ds_read_b128 %1, %4 offset:7*512+256 \n \
    ds_read_b128 %2, %5 offset:7*512 \n \
    ds_read_b128 %3, %5 offset:7*512+256 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
}
template<uint32_t off>
inline __device__ void shared_read_b64(Half4 &a0, Half4 &a1, Half4 &b0, Half4 &b1, uint32_t &ldsA, uint32_t &ldsB) {
    if(off == 0) {
    asm volatile("\n \
    ds_read_b64 %0, %4 offset:0 \n \
    ds_read_b64 %1, %4 offset:128 \n \
    ds_read_b64 %2, %5 offset:0 \n \
    ds_read_b64 %3, %5 offset:128 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 1*512) {
    asm volatile("\n \
    ds_read_b64 %0, %4 offset:1*256 \n \
    ds_read_b64 %1, %4 offset:1*256+128 \n \
    ds_read_b64 %2, %5 offset:1*256 \n \
    ds_read_b64 %3, %5 offset:1*256+128 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 2*512) {
    asm volatile("\n \
    ds_read_b64 %0, %4 offset:2*256 \n \
    ds_read_b64 %1, %4 offset:2*256+128 \n \
    ds_read_b64 %2, %5 offset:2*256 \n \
    ds_read_b64 %3, %5 offset:2*256+128 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 3*512) {
    asm volatile("\n \
    ds_read_b64 %0, %4 offset:3*256 \n \
    ds_read_b64 %1, %4 offset:3*256+128 \n \
    ds_read_b64 %2, %5 offset:3*256 \n \
    ds_read_b64 %3, %5 offset:3*256+128 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }

    if(off == 4*512) {
    asm volatile("\n \
    ds_read_b64 %0, %4 offset:4*256 \n \
    ds_read_b64 %1, %4 offset:4*256+128 \n \
    ds_read_b64 %2, %5 offset:4*256 \n \
    ds_read_b64 %3, %5 offset:4*256+128 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 5*512) {
    asm volatile("\n \
    ds_read_b64 %0, %4 offset:5*256 \n \
    ds_read_b64 %1, %4 offset:5*256+128 \n \
    ds_read_b64 %2, %5 offset:5*256 \n \
    ds_read_b64 %3, %5 offset:5*256+128 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 6*512) {
    asm volatile("\n \
    ds_read_b64 %0, %4 offset:6*256 \n \
    ds_read_b64 %1, %4 offset:6*256+128 \n \
    ds_read_b64 %2, %5 offset:6*256 \n \
    ds_read_b64 %3, %5 offset:6*256+128 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
    if(off == 7*512) {
    asm volatile("\n \
    ds_read_b64 %0, %4 offset:7*256 \n \
    ds_read_b64 %1, %4 offset:7*256+128 \n \
    ds_read_b64 %2, %5 offset:7*256 \n \
    ds_read_b64 %3, %5 offset:7*256+128 \n \
    "
    :"=v"(a0),"=v"(a1),"=v"(b0),"=v"(b1)
    :"v"(ldsA),"v"(ldsB));
    }
}


/**
* Format:   ds_read_b128 dst, src
* Example:  ds_read_b128 v[8:11], v2
*/
inline __device__ void shared_read_b128(Float4 &val, uint32_t &lds) {
    asm volatile ("\n \
        ds_read_b128 %0, %1 \n \
        "
    :"=v"(val)
    :"v"(lds)
    );
}
inline __device__ void shared_read_b128(Half2x4 &val, uint32_t &lds) {
    asm volatile ("\n \
        ds_read_b128 %0, %1 \n \
        "
    :"=v"(val)
    :"v"(lds)
    );
}