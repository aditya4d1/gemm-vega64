#include <iostream>
#include <CL/cl.h>
#include <fstream>

#include "Tensor.h"
#include "Image.h"

int main() {
    unsigned int width = 64*4;

    typedef float T;

    stinger::Tensor<T> A(width, 1);
    stinger::Tensor<T> B(width, 1);
    stinger::Tensor<T> C(width, 1);

    stinger::fill(A, T(2));
    stinger::fill(B, T(3));
    stinger::fill(C, T(1));

    Init();
    BuildProgram(LoadKernel("./inc/vadd.cl"), context);
    kernel = clCreateKernel(program, "Main", &error);
    CL_CHECK(error);

    stinger::Buffer1D<T, CL_MEM_READ_ONLY> BufferA(A);
    stinger::Buffer1D<T, CL_MEM_READ_ONLY> BufferB(B);
    stinger::Buffer1D<T, CL_MEM_WRITE_ONLY> BufferC(C);

    BufferA.ToGPU();
    BufferB.ToGPU();
    BufferC.ToGPU();

    error = clSetKernelArg(kernel, 0, sizeof(cl_mem), &(BufferA.buff));
    error|= clSetKernelArg(kernel, 1, sizeof(cl_mem), &(BufferB.buff));
    error|= clSetKernelArg(kernel, 2, sizeof(cl_mem), &(BufferC.buff));

    CL_CHECK(error);

    size_t offset[3] = { 0 };
    size_t size[3] = {64, 1, 1};

    error = clEnqueueNDRangeKernel(queue, kernel, 2, offset, size, NULL, 0, NULL, NULL);
    CL_CHECK(error);

    clFinish(queue);

    BufferC.FromGPU();
    std::cout<<C[0]<<" "<<C[1]<<" "<<C[2]<<" "<<C[3]<<std::endl;
    std::cout<<C[4]<<" "<<C[5]<<" "<<C[6]<<" "<<C[7]<<std::endl;
    std::cout<<C[8]<<" "<<C[9]<<" "<<C[10]<<" "<<C[11]<<std::endl;
    std::cout<<C[12]<<" "<<C[13]<<" "<<C[14]<<" "<<C[15]<<std::endl;

}
