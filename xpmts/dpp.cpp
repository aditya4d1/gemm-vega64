#include <iostream>
#include <vector>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#include <fstream>

typedef float Float4 __attribute__((ext_vector_type(4)));

constexpr unsigned a_x = 128/4;
constexpr unsigned b_x = a_x;
constexpr unsigned a_y = 8;
constexpr unsigned b_y = a_y;
constexpr unsigned c_x = 128/4;
constexpr unsigned c_y = 128;
constexpr size_t a_size = sizeof(Float4) * a_x * a_y;
constexpr size_t b_size = sizeof(Float4) * b_x * b_y;
constexpr size_t c_size = sizeof(Float4) * c_x * c_y;

#define HIPCHECK(status) \
if(status != hipSuccess) { std::cout<<"Got: "<<hipGetErrorString(status)<<" at: "<<__LINE__<<std::endl; }

#define name "_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_"
#define file_name "dpp.co"

int main() {
    HIPCHECK(hipInit(0));
    hipDevice_t device;
    hipCtx_t context;
    HIPCHECK(hipDeviceGet(&device, 0));
    HIPCHECK(hipCtxCreate(&context, 0, device));
    hipModule_t Module;
    hipFunction_t Function;
    Float4 *A, *B, *C;
    HIPCHECK(hipHostMalloc(&A, a_size));
    HIPCHECK(hipHostMalloc(&B, b_size));
    HIPCHECK(hipHostMalloc(&C, c_size));
    for(int i=0;i<a_x*a_y;i++) {
        A[i].x = i * 4 + 0;
        A[i].y = i * 4 + 1;
        A[i].z = i * 4 + 2;
        A[i].w = i * 4 + 3;
    }

    for(int i=0;i<b_x*b_y;i++) {
        B[i].x = 1.0f;
        B[i].y = 1.0f;
        B[i].z = 1.0f;
        B[i].w = 1.0f;
    }

    for(int i=0;i<c_x*c_y;i++) {
        C[i].x = -1.0f;
        C[i].y = -1.0f;
        C[i].z = -1.0f;
        C[i].w = -1.0f;
    }

    HIPCHECK(hipModuleLoad(&Module, file_name));
    HIPCHECK(hipModuleGetFunction(&Function, Module, name));
/*
    void *args[3] = {&A, &B, &C};
    HIPCHECK(hipModuleLaunchKernel(Function,1,1,1,256,1,1,0,0,args,0));
*/

    struct {
        void *A, *B, *C;
    } args;

    args.A = A;
    args.B = B;
    args.C = C;

    size_t size = sizeof(args);

    void *config[] = {
        HIP_LAUNCH_PARAM_BUFFER_POINTER, &args,
        HIP_LAUNCH_PARAM_BUFFER_SIZE, &size,
        HIP_LAUNCH_PARAM_END
    };

    HIPCHECK(hipModuleLaunchKernel(Function,1,1,1,256,1,1,0,0,NULL,(void**)&config));

    HIPCHECK(hipDeviceSynchronize());

    std::ofstream outfile;
    outfile.open("outfile.txt");
    for(int i=0;i<c_y;i++) {
        for(int j=0;j<c_x;j++) {
            outfile << C[i].x <<" "<<C[i].y<<" "<<C[i].z<<" "<<C[i].w<<" ";
        }
        outfile<<"\n";
    }
    outfile.close();
}
