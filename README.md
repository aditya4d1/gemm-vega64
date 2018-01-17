# gemm-vega64
Implement asm gemm on vega64 for 4096x4096 fp32 matrix

## Results
v10 is the highest performing kernel

| Card | Shader Clock | Memory Clock | TFLOPs (fp32) | TFLOPs Peak (fp32) | Efficiency |
----|------|---------|---|----|----|
MI25 | 1500Mhz | 945Mhz | 10.6 | 12.3 | 86% |
RXVega64 | 1630Mhz | 945Mhz | 11.2 | 13.35 | 84% |
VegaFE | | | | | |

As the code is not written in pure isa, compiler tries to move instructions around causing drop in performance.

For RXVega64, when we launch 1024 sgemm kernels (sgemm\_v11.cpp), the performance drops to 9.6 TFLOPs. I see the clocks go down to as low as 1400MHz, 1536MHz.
For RXVega64, when we do 1024 iterations of sgemm in the same kernel (sgemm\_12.cpp), the performance drops to 9.5 TFLOPs. I see the clocks go down to as low as 1138MHz, 1200MHz, 1401MHz and never on 1536MHz and 1630MHz.
