#include <iostream>
#include <CL/cl.h>
#include <fstream>

#include "Tensor.h"
#include "Image.h"

int main() {
    unsigned int width = 64*4;

    typedef float T;

    stinger::Tensor<T> A(width, 1);

    stinger::fill(A, T(2));

    Init();
    BuildProgram(LoadKernel("./inc/vadd.cl"), context);
    kernel = clCreateKernel(program, "Main", &error);
    CL_CHECK(error);

    stinger::Buffer1D<T, CL_MEM_READ_ONLY> BufferA(A);

    BufferA.ToGPU();

    error = clSetKernelArg(kernel, 0, sizeof(cl_mem), &(BufferA.buff));
    CL_CHECK(error);

    size_t offset[3] = { 0 };
    size_t size[3] = {64, 1, 1};

    error = clEnqueueNDRangeKernel(queue, kernel, 2, offset, size, NULL, 0, NULL, NULL);
    CL_CHECK(error);

    clFinish(queue);

    BufferA.FromGPU();
    std::cout<<A[0]<<std::endl;
}
