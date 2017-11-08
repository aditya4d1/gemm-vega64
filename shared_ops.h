#pragma once

inline __device__ void lds_blocks(uint32_t &redA, uint32_t &redB, uint32_t &blueA, uint32_t &blueB) {
asm volatile (
" \n \
v_mov_b32 %0, 0     \n \
v_mov_b32 %1, 4096  \n \
v_mov_b32 %2, 8192  \n \
v_mov_b32 %3, 12288"
:"=v"(redA),"=v"(redB),"=v"(blueA),"=v"(blueB):);
}
