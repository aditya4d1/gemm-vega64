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
