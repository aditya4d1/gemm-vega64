/**
* Not - Working code for
* 1. Global load from A, B and C (asm)
* 2. Write to LDS (asm)
* 3. Read from LDS (asm)
* 4. 8 iteration of outer product (asm)
* 5. offset based load and stores (asm)
* 6. Store to global (asm)
* + Double Buffering!
*/

#include <iostream>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#include "outer_product.h"
#include "global_ops.h"
#include "shared_ops.h"
#include "dims.h"
#include <fstream>

constexpr uint32_t xDim = 4096;
constexpr uint32_t yDim = 4096;
constexpr uint32_t xDim4 = xDim/4;
constexpr uint32_t xDim8 = xDim/8;
constexpr uint32_t x32 = 32;
constexpr uint32_t x16 = 16;
constexpr size_t Size = xDim * yDim * sizeof(float);

#define FNAME "file.co"
#define KNAME "_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_"

int main() {
    hipSetDevice(0);
    std::vector<Float4> a(xDim4*yDim), b(xDim4*yDim), c(xDim*xDim4);
    std::fill(c.begin(), c.end(), 0.0f);
    float *_a = reinterpret_cast<float*>(a.data());
    float *_b = reinterpret_cast<float*>(b.data());
    float *_c = reinterpret_cast<float*>(c.data());

    for(int j=0;j<yDim;j++) {
        for(int i=0;i<xDim;i++) {
            _a[i + j * xDim] = (j+i*xDim)*1.0f + 1.0f;
            if(i == j) {
            _b[i + j * xDim] = 1.0f;
            } else {
            _b[i + j * xDim] = 0.0f;
            }
        }
    }

    hipInit(0);
    hipDevice_t device;
    hipCtx_t context;

    hipDeviceGet(&device, 0);
    hipCtxCreate(&context, 0, device);

    Float4 *Ad, *Bd, *Cd;
    int *buffA, *buffB;
    hipHostMalloc(&buffA, 16*16*sizeof(int));
    hipHostMalloc(&buffB, 16*16*sizeof(int));
    hipMalloc(&Ad, a.size()*sizeof(Float4));
    hipMalloc(&Bd, b.size()*sizeof(Float4));
    hipMalloc(&Cd, c.size()*sizeof(Float4));

/*
    hipMemcpy(Ad, a.data(), a.size()*sizeof(Float4), hipMemcpyHostToDevice);
    hipMemcpy(Bd, b.data(), b.size()*sizeof(Float4), hipMemcpyHostToDevice);
    hipMemcpy(Cd, c.data(), c.size()*sizeof(Float4), hipMemcpyHostToDevice);
*/

    hipModule_t Module;
    hipFunction_t Function;

    hipModuleLoad(&Module, FNAME);
    hipModuleGetFunction(&Function, Module, KNAME);

    struct {
        Float4 *Ad, *Bd, *Cd;
    } args;

    args.Ad = Ad;
    args.Bd = Bd;
    args.Cd = Cd;

    size_t size_args = sizeof(args);
    void *config[] = {HIP_LAUNCH_PARAM_BUFFER_POINTER, &args, HIP_LAUNCH_PARAM_BUFFER_SIZE, &size_args, HIP_LAUNCH_PARAM_END};

    auto start = std::chrono::high_resolution_clock::now();
//    hipLaunchKernelGGL(SGEMM, dim3(32,32,1), dim3(16,16,1), 4*sizeof(float)*8*128*2, 0, Ad, Bd, Cd, buffA, buffB);
    hipModuleLaunchKernel(Function, 32, 32, 1, 16, 16, 1, 4*sizeof(float)*8*128*2, 0, NULL, (void**)&config);
    hipDeviceSynchronize();
    auto stop = std::chrono::high_resolution_clock::now();
    double sec = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
    std::cout<<sec<<std::endl;
    double flops = (double)xDim * (double)yDim * (double)yDim * 2 / (double)1.0e12;
    double floppersec = flops / sec;
    std::cout<<flops<<" "<<sec<<" "<<floppersec<<std::endl;
    hipMemcpy(c.data(), Cd, c.size()*sizeof(Float4), hipMemcpyDeviceToHost);
    std::ofstream outfile;
    outfile.open("outfile.txt");

    std::cout<<"writing to outfile"<<std::endl;

    for(int j=0;j<4;j++) {
        for(int i=0;i<xDim;i++) {
            outfile << _c[i+j*xDim] <<" ";
        }
        outfile <<"\n";
    }
    outfile<<"\n\n\n";
/*
    std::cout<<"Done writing to outfile"<<std::endl;
    for(int j=0;j<16;j++) {
        for(int i=0;i<16;i++) {
            outfile << buffA[i+j*16]<<" ";
        }
        outfile << "\n";
    }
    outfile<<"\n\n\n";
    for(int j=0;j<16;j++) {
        for(int i=0;i<16;i++) {
            outfile << buffB[i+j*16]<<" ";
        }
        outfile << "\n";
    }
    outfile<<"\n\n\n";
*/
    outfile.close();
}
