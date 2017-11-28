/**
* Not - Working code for
* 1. Global load from A, B and C (asm)
* 2. Write to LDS (asm)
* 3. Read from LDS (asm)
* 4. 8 iteration of outer product (asm)
* 5. offset based load and stores (asm)
* 6. Store to global (asm)
*/

#include <iostream>
#include <hip/hip_runtime.h>
#include <hip/hip_runtime_api.h>
#include "outer_product.h"
#include "global_ops.h"
#include "shared_ops.h"
#include "dims.h"
#include <fstream>

constexpr uint32_t xDim = 128;
constexpr uint32_t yDim = 8;
constexpr uint32_t xDim4 = 32;
constexpr uint32_t xDim8 = xDim/8;
constexpr size_t Size = xDim * yDim * sizeof(float);

__global__ void SGEMM(Float4 *A, Float4 *B, Float4 *C, int *getGlobalAId, int *getGlobalCId) {
    int tx = hipThreadIdx_x;
    int ty = hipThreadIdx_y;

    Float4 a0, a1, b0, b1;
    Float4 c[16];

    int id = tx + (ty % 2) * 16 + (ty / 2) * xDim4;
    getGlobalAId[tx + ty * 16] = id;

    int cid0 = tx + ty * 4 * xDim4 + 0*32;
/*
    int cid1 = tx + ty * 4 * xDim4 + 1*32;
    int cid2 = tx + ty * 4 * xDim4 + 2*32;
    int cid3 = tx + ty * 4 * xDim4 + 3*32;

    int cid4 = tx + ty * 4 * xDim4 + 16 + 0*32;
    int cid5 = tx + ty * 4 * xDim4 + 16 + 1*32;
    int cid6 = tx + ty * 4 * xDim4 + 16 + 2*32;
    int cid7 = tx + ty * 4 * xDim4 + 16 + 3*32;
*/
    int cid8 = tx + ty * 4 * xDim4 + 0*32 + 64*32;
/*
    int cid9 = tx + ty * 4 * xDim4 + 1*32 + 64*32;
    int cid10= tx + ty * 4 * xDim4 + 2*32 + 64*32;
    int cid11= tx + ty * 4 * xDim4 + 3*32 + 64*32;

    int cid12= tx + ty * 4 * xDim4 + 16 + 64*32 + 0*32;
    int cid13= tx + ty * 4 * xDim4 + 16 + 64*32 + 1*32;
    int cid14= tx + ty * 4 * xDim4 + 16 + 64*32 + 2*32;
    int cid15= tx + ty * 4 * xDim4 + 16 + 64*32 + 3*32;
*/

    global_load<0>(C, c[0], cid0);
    global_load<32>(C, c[1], cid0);
    global_load<2*32>(C, c[2], cid0);
    global_load<3*32>(C, c[3], cid0);

    global_load<16+0>(C, c[4], cid0);
    global_load<16+32>(C, c[5], cid0);;
    global_load<16+2*32>(C, c[6], cid0);
    global_load<16+3*32>(C, c[7], cid0);

    global_load<0>(C, c[8], cid8);
    global_load<32>(C, c[9], cid8);
    global_load<2*32>(C, c[10], cid8);
    global_load<3*32>(C, c[11], cid8);

    global_load<16+0>(C, c[12], cid8);
    global_load<16+32>(C, c[13], cid8);
    global_load<16+2*32>(C, c[14], cid8);
    global_load<16+3*32>(C, c[15], cid8);


    Float4 ra, rb;

    global_load<0>(A, ra, id);
    global_load<0>(B, rb, id);

    vmcnt<0>();

    getGlobalCId[tx + ty * 16] = cid8;

    uint32_t redA = 0;
    uint32_t redB = 4096;
    uint32_t blueA = 8192;
    uint32_t blueB = 12288;

    uint32_t redA0 = redA+id*16;
    uint32_t redB0 = redB+id*16;
    shared_write_b128(ra, redA0);
    shared_write_b128(rb, redB0);

    uint32_t redA1, redB1;

    lgkmcnt<0>();

    for(int i=0;i<8;i++) {

    redA0 = redA + (ty+i*32)*16;
    redA1 = redA + (ty+i*32+16)*16;
    redB0 = redB + (tx+i*32)*16;
    redB1 = redB + (tx+i*32+16)*16;


    asm volatile("\n \
    ds_read_b128 %0, %4 \n \
    ds_read_b128 %1, %5 \n \
    ds_read_b128 %2, %6 \n \
    ds_read_b128 %3, %7 \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA + (ty + i*32)*16), "v"(redA + (ty+16+i*32)*16), "v"(redB + (tx+i*32)*16), "v"(redB + (tx+16+i*32)*16)
    );

    lgkmcnt<0>();

    outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
    outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
    outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
    outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);


}

    global_store<0>(C, c[0], cid0);
    global_store<1*32>(C, c[1], cid0);
    global_store<2*32>(C, c[2], cid0);
    global_store<3*32>(C, c[3], cid0);

    global_store<16+0>(C, c[4], cid0);
    global_store<16+1*32>(C, c[5], cid0);
    global_store<16+2*32>(C, c[6], cid0);
    global_store<16+3*32>(C, c[7], cid0);

    global_store<0>(C, c[8], cid8);
    global_store<1*32>(C, c[9], cid8);
    global_store<2*32>(C, c[10], cid8);
    global_store<3*32>(C, c[11], cid8);

    global_store<16+0>(C, c[12], cid8);
    global_store<16+1*32>(C, c[13], cid8);
    global_store<16+2*32>(C, c[14], cid8);
    global_store<16+3*32>(C, c[15], cid8);


    vmcnt<0>();

}


int main() {
    hipSetDevice(1);
    std::vector<Float4> a(xDim4*yDim), b(xDim4*yDim), c(xDim*xDim4);
    std::fill(c.begin(), c.end(), 0.0f);
    float *_a = reinterpret_cast<float*>(a.data());
    float *_b = reinterpret_cast<float*>(b.data());
    float *_c = reinterpret_cast<float*>(c.data());

    for(int j=0;j<yDim;j++) {
        for(int i=0;i<xDim;i++) {
            _a[i + j * xDim] = (i+j*xDim) + 1.0f;;
            _b[i + j * xDim] = 1.0f;
        }
    }

    Float4 *Ad, *Bd, *Cd;
    int *buffA, *buffB;
    hipHostMalloc(&buffA, 16*16*sizeof(int));
    hipHostMalloc(&buffB, 16*16*sizeof(int));
    hipMalloc(&Ad, Size);
    hipMalloc(&Bd, Size);
    hipMalloc(&Cd, Size);
    hipMemcpy(Ad, a.data(), a.size()*sizeof(Float4), hipMemcpyHostToDevice);
    hipMemcpy(Bd, b.data(), b.size()*sizeof(Float4), hipMemcpyHostToDevice);
    hipMemcpy(Cd, c.data(), c.size()*sizeof(Float4), hipMemcpyHostToDevice);
    auto start = std::chrono::high_resolution_clock::now();
    hipLaunchKernelGGL(SGEMM, dim3(1,1,1), dim3(16,16,1), 4*sizeof(float)*8*128*2, 0, Ad, Bd, Cd, buffA, buffB);
    hipDeviceSynchronize();
    auto stop = std::chrono::high_resolution_clock::now();
    double sec = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
    std::cout<<sec<<std::endl;
    hipMemcpy(c.data(), Cd, c.size()*sizeof(Float4), hipMemcpyDeviceToHost);
    std::ofstream outfile;
    outfile.open("outfile.txt");

    for(int j=0;j<xDim;j++) {
        for(int i=0;i<xDim;i++) {
            outfile << _c[i+j*xDim] <<" ";
        }
        outfile <<"\n";
    }
    outfile<<"\n\n\n";
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
    outfile.close();
}
