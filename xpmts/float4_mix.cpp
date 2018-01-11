#include <iostream>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>

typedef __fp16 Half4 __attribute__((ext_vector_type(4)));
typedef float Float4 __attribute__((ext_vector_type(4)));
typedef __fp16 Half2 __attribute__((ext_vector_type(2)));

constexpr uint32_t a_width = 16;
constexpr size_t a_size = a_width*sizeof(Half4);
constexpr uint32_t b_width = 16;
constexpr size_t b_size = b_width*sizeof(Half4);
constexpr uint32_t c_width = 16;
constexpr size_t c_size = c_width*sizeof(Float4);

__global__ void Out(Half4 *A, Half4 *B, Float4 *C) {
    int tx = hipThreadIdx_x;
    Half4 a = A[tx];
    Half4 b = B[tx];
    Float4 c = C[tx];
    Half2 _a, _b;
    _a.x = __fp16(1.0f);
    _a.y = __fp16(2.0f);
    _b.x = __fp16(3.0f);
    _b.y = __fp16(4.0f);

    asm volatile("\n \
    v_mad_mix_f32 %0, %1, %2, %3 op_sel:[1,1,0] op_sel_hi:[1,1,0]\n \
    "
    :
    :"v"(c.x),"v"(_a), "v"(_b), "v"(c.x));

    C[tx] = c;
}

int main() {
    std::vector<Half4> A(a_width);
    std::vector<Half4> B(a_width);
    std::vector<Float4> C(c_width);
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
        C[i].x = 0.0f;
        C[i].y = 0.0f;
        C[i].z = 0.0f;
        C[i].w = 0.0f;
    }
    Float4 *Cd;
    Half4 *Ad, *Bd;
    hipMalloc(&Ad, a_size);
    hipMalloc(&Bd, b_size);
    hipMalloc(&Cd, c_size);
    hipMemcpy(Cd, C.data(), c_size, hipMemcpyHostToDevice);
    hipMemcpy(Ad, A.data(), a_size, hipMemcpyHostToDevice);
    hipMemcpy(Bd, B.data(), b_size, hipMemcpyHostToDevice);
    hipLaunchKernelGGL(Out, dim3(1,1,1), dim3(16,1,1), 0, 0, Ad, Bd, Cd);
    hipDeviceSynchronize();
    hipMemcpy(C.data(), Cd, c_size, hipMemcpyDeviceToHost);
    for(int i=0;i<a_width;i++) {
        std::cout<<C[i].x<<" "<<C[i].y<<" "<<C[i].z<<" "<<C[i].w<<std::endl;
    }
}

