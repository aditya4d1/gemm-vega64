#include <iostream>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

typedef __fp16 Half4 __attribute__((ext_vector_type(4)));

constexpr uint32_t a_width = 16;
constexpr size_t a_size = a_width*sizeof(Half4);
constexpr uint32_t b_width = 16;
constexpr size_t b_size = b_width*sizeof(Half4);
constexpr uint32_t c_width = a_width * b_width * 4;
constexpr size_t c_size = c_width*sizeof(Half4);

__global__ void Out(Half4 *A, Half4 *B, Half4 *C) {
    int tx = hipThreadIdx_x;
    int ty = hipThreadIdx_y;
    Half4 a = A[ty];
    Half4 b = B[tx];
    int c0_id = tx + ty * 16 * 4;
    int c1_id = tx + ty * 16 * 4 + 16;
    int c2_id = tx + ty * 16 * 4 + 32;
    int c3_id = tx + ty * 16 * 4 + 48;
    Half4 c0 = C[c0_id];
    Half4 c1 = C[c1_id];
    Half4 c2 = C[c2_id];
    Half4 c3 = C[c3_id];

    asm volatile("\n \
    v_pk_fma_f16 %0, %1, %2, %3 op_sel:[0,0,0] op_sel_hi:[0,1,1] \n \
    "
    :
    :"v"(c0.xy), "v"(a.xy), "v"(b.xy), "v"(c0.xy));
    asm volatile("\n \
    v_pk_fma_f16 %0, %1, %2, %3 op_sel:[0,0,0] op_sel_hi:[0,1,1] \n \
    "
    :
    :"v"(c0.zw), "v"(a.xy), "v"(b.zw), "v"(c0.zw));
    asm volatile("\n \
    v_pk_fma_f16 %0, %1, %2, %3 op_sel:[1,0,0] op_sel_hi:[1,1,1] \n \
    "
    :
    :"v"(c1.xy), "v"(a.xy), "v"(b.xy), "v"(c1.xy));
    asm volatile("\n \
    v_pk_fma_f16 %0, %1, %2, %3 op_sel:[1,0,0] op_sel_hi:[1,1,1] \n \
    "
    :
    :"v"(c1.zw), "v"(a.xy), "v"(b.zw), "v"(c1.zw));


    asm volatile("\n \
    v_pk_fma_f16 %0, %1, %2, %3 op_sel:[0,0,0] op_sel_hi:[0,1,1] \n \
    "
    :
    :"v"(c2.xy), "v"(a.zw), "v"(b.xy), "v"(c2.xy));
    asm volatile("\n \
    v_pk_fma_f16 %0, %1, %2, %3 op_sel:[0,0,0] op_sel_hi:[0,1,1] \n \
    "
    :
    :"v"(c2.zw), "v"(a.zw), "v"(b.zw), "v"(c2.zw));
    asm volatile("\n \
    v_pk_fma_f16 %0, %1, %2, %3 op_sel:[1,0,0] op_sel_hi:[1,1,1] \n \
    "
    :
    :"v"(c3.xy), "v"(a.zw), "v"(b.xy), "v"(c3.xy));
    asm volatile("\n \
    v_pk_fma_f16 %0, %1, %2, %3 op_sel:[1,0,0] op_sel_hi:[1,1,1] \n \
    "
    :
    :"v"(c3.zw), "v"(a.zw), "v"(b.zw), "v"(c3.zw));



    C[c0_id] = c0;
    C[c1_id] = c1;
    C[c2_id] = c2;
    C[c3_id] = c3;
}

int main() {
    std::vector<Half4> A(a_width);
    std::vector<Half4> B(a_width);
    std::vector<Half4> C(c_width);
    for(int i=0;i<a_width;i++) {
        A[i].x = __fp16(4 * i + 0.0f);
        A[i].y = __fp16(4 * i + 1.0f);
        A[i].z = __fp16(4 * i + 2.0f);
        A[i].w = __fp16(4 * i + 3.0f);

        B[i].x = __fp16(1.0f);
        B[i].y = __fp16(1.0f);
        B[i].z = __fp16(1.0f);
        B[i].w = __fp16(1.0f);
    }
    for(int i=0;i<c_width;i++) {
        C[i].x = __fp16(0.0f);
        C[i].y = __fp16(0.0f);
        C[i].z = __fp16(0.0f);
        C[i].w = __fp16(0.0f);
    }
    Half4 *Cd, *Ad, *Bd;
    hipMalloc(&Ad, a_size);
    hipMalloc(&Bd, b_size);
    hipMalloc(&Cd, c_size);
    hipMemcpy(Cd, C.data(), c_size, hipMemcpyHostToDevice);
    hipMemcpy(Ad, A.data(), a_size, hipMemcpyHostToDevice);
    hipMemcpy(Bd, B.data(), b_size, hipMemcpyHostToDevice);
    hipLaunchKernelGGL(Out, dim3(1,1,1), dim3(16,16,1), 0, 0, Ad, Bd, Cd);
    hipDeviceSynchronize();
    hipMemcpy(C.data(), Cd, c_size, hipMemcpyDeviceToHost);
    for(int i=0;i<a_width;i++) {
        for(int j=0;j<16;j++) {
            std::cout<<float(C[j+i*16].x)<<" "<<float(C[j+i*16].y)<<" "<<float(C[j+i*16].z)<<" "<<float(C[j+i*16].w)<<"  ";
        }
        std::cout<<std::endl;
    }
}
