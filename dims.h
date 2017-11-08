#pragma once

constexpr uint32_t dim_x = 4096;
constexpr uint32_t dim_y = 4096;
constexpr uint32_t dim_x4 = dim_x / 4;
constexpr uint32_t dim_y4 = dim_y / 4;
constexpr uint32_t unroll_factor = 8;
constexpr uint32_t tile = 128;
constexpr uint32_t tilex4 = tile / 4;
constexpr uint32_t half_tile = 64;
constexpr uint32_t half_tilex4 = 64 / 4;
constexpr size_t size = dim_x * dim_y * sizeof(float);
