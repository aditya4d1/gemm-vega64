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

__global__ void SGEMM(Float4 *A, Float4 *B, Float4 *C, int *getGlobalAId, int *getGlobalCId) {
    int tx = hipThreadIdx_x;
    int ty = hipThreadIdx_y;
    int bx = hipBlockIdx_x;
    int by = hipBlockIdx_y;

    Float4 rA0, rA1, rB0, rB1, bA0, bA1, bB0, bB1;
    Float4 a0, a1, b0, b1;
    Float4 c[16];// = {0};

    Float4 ra, rb;

    uint32_t redA = 0;
    uint32_t redB = 4096;

    uint32_t ldsReadA = 0;
    uint32_t ldsReadB = 4096;
    uint32_t ldsWriteA = 0;
    uint32_t ldsWriteB = 4096;

    int id = tx + (ty % 2) * x16 + (ty / 2) * x32;
    int a_global_id = tx + (ty % 2) * x16 + (ty / 2) * 1024 + by * x32;
    int b_global_id = tx + (ty % 2) * x16 + (ty / 2) * 1024 + bx * x32;

    int cid0 = tx + ty * 4 * xDim4 + 0*1024 + bx * 32 + by * 1024 * 128;
    int cid1 = tx + ty * 4 * xDim4 + 1*1024 + bx * 32 + by * 1024 * 128;
    int cid2 = tx + ty * 4 * xDim4 + 2*1024 + bx * 32 + by * 1024 * 128;
    int cid3 = tx + ty * 4 * xDim4 + 3*1024 + bx * 32 + by * 1024 * 128;

    int cid4 = tx + ty * 4 * xDim4 + 16 + 0*1024 + bx * 32 + by * 1024 * 128;
    int cid5 = tx + ty * 4 * xDim4 + 16 + 1*1024 + bx * 32 + by * 1024 * 128;
    int cid6 = tx + ty * 4 * xDim4 + 16 + 2*1024 + bx * 32 + by * 1024 * 128;
    int cid7 = tx + ty * 4 * xDim4 + 16 + 3*1024 + bx * 32 + by * 1024 * 128;

    int cid8 = tx + ty * 4 * xDim4 + 0*1024 + 64*1024 + bx * 32 + by * 1024 * 128;
    int cid9 = tx + ty * 4 * xDim4 + 1*1024 + 64*1024 + bx * 32 + by * 1024 * 128;
    int cid10= tx + ty * 4 * xDim4 + 2*1024 + 64*1024 + bx * 32 + by * 1024 * 128;
    int cid11= tx + ty * 4 * xDim4 + 3*1024 + 64*1024 + bx * 32 + by * 1024 * 128;

    int cid12= tx + ty * 4 * xDim4 + 16 + 64*1024 + 0*1024 + bx * 32 + by * 1024 * 128;
    int cid13= tx + ty * 4 * xDim4 + 16 + 64*1024 + 1*1024 + bx * 32 + by * 1024 * 128;
    int cid14= tx + ty * 4 * xDim4 + 16 + 64*1024 + 2*1024 + bx * 32 + by * 1024 * 128;
    int cid15= tx + ty * 4 * xDim4 + 16 + 64*1024 + 3*1024 + bx * 32 + by * 1024 * 128;

    global_load<0>(C, c[0], cid0);
    global_load<0>(C, c[1], cid1);
    global_load<0>(C, c[2], cid2);
    global_load<0>(C, c[3], cid3);

    global_load<16>(C, c[4], cid0);
    global_load<16>(C, c[5], cid1);
    global_load<16>(C, c[6], cid2);
    global_load<16>(C, c[7], cid3);

    global_load<0>(C, c[8], cid8);
    global_load<0>(C, c[9], cid9);
    global_load<0>(C, c[10], cid10);
    global_load<0>(C, c[11], cid11);

    global_load<16>(C, c[12], cid8);
    global_load<16>(C, c[13], cid9);
    global_load<16>(C, c[14], cid10);
    global_load<16>(C, c[15], cid11);

for(int j=0;j<yDim/8;j++) {
    global_load<0>(A, ra, a_global_id);
    global_load<0>(B, rb, b_global_id);

    a_global_id += 8 * 1024;
    b_global_id += 8 * 1024;

    vmcnt<0>();
    __syncthreads();

    uint32_t redA0 = redA+id*16;
    uint32_t redB0 = redB+id*16;
    shared_write_b128(ra, redA0);
    shared_write_b128(rb, redB0);

    uint32_t redA1, redB1;

    lgkmcnt<0>();

//    for(int i=0;i<8;i++) {

    redA0 = redA + (ty+0*32)*16;
    redA1 = redA + (ty+0*32+16)*16;
    redB0 = redB + (tx+0*32)*16;
    redB1 = redB + (tx+0*32+16)*16;

/*
    asm volatile("\n \
    ds_read_b128 %0, %4 \n \
    ds_read_b128 %1, %5 \n \
    ds_read_b128 %2, %6 \n \
    ds_read_b128 %3, %7 \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA + (ty + 0*32)*16), "v"(redA + (ty+16+0*32)*16), "v"(redB + (tx+0*32)*16), "v"(redB + (tx+16+0*32)*16)
    );
*/


    asm volatile("\n \
    ds_read_b128 %0, %4 offset:0      \n \
    ds_read_b128 %1, %5 offset:256   \n \
    ds_read_b128 %2, %6 offset:0      \n \
    ds_read_b128 %3, %7 offset:256   \n \
    s_waitcnt lgkmcnt(0) \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA0), "v"(redA0), "v"(redB0), "v"(redB0)
    );

    lgkmcnt<0>();

    outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
    outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
    outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
    outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

// i = 1
    redA0 = redA + (ty+1*32)*16;
    redA1 = redA + (ty+1*32+16)*16;
    redB0 = redB + (tx+1*32)*16;
    redB1 = redB + (tx+1*32+16)*16;


    asm volatile("\n \
    ds_read_b128 %0, %4 \n \
    ds_read_b128 %1, %5 \n \
    ds_read_b128 %2, %6 \n \
    ds_read_b128 %3, %7 \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA + (ty + 1*32)*16), "v"(redA + (ty+16+1*32)*16), "v"(redB + (tx+1*32)*16), "v"(redB + (tx+16+1*32)*16)
    );

    lgkmcnt<0>();

    outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
    outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
    outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
    outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

// i = 2
    redA0 = redA + (ty+2*32)*16;
    redA1 = redA + (ty+2*32+16)*16;
    redB0 = redB + (tx+2*32)*16;
    redB1 = redB + (tx+2*32+16)*16;


    asm volatile("\n \
    ds_read_b128 %0, %4 \n \
    ds_read_b128 %1, %5 \n \
    ds_read_b128 %2, %6 \n \
    ds_read_b128 %3, %7 \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA + (ty + 2*32)*16), "v"(redA + (ty+16+2*32)*16), "v"(redB + (tx+2*32)*16), "v"(redB + (tx+16+2*32)*16)
    );

    lgkmcnt<0>();

    outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
    outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
    outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
    outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

// i = 3
    redA0 = redA + (ty+3*32)*16;
    redA1 = redA + (ty+3*32+16)*16;
    redB0 = redB + (tx+3*32)*16;
    redB1 = redB + (tx+3*32+16)*16;


    asm volatile("\n \
    ds_read_b128 %0, %4 \n \
    ds_read_b128 %1, %5 \n \
    ds_read_b128 %2, %6 \n \
    ds_read_b128 %3, %7 \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA + (ty + 3*32)*16), "v"(redA + (ty+16+3*32)*16), "v"(redB + (tx+3*32)*16), "v"(redB + (tx+16+3*32)*16)
    );

    lgkmcnt<0>();

    outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
    outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
    outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
    outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

// i = 4
    redA0 = redA + (ty+4*32)*16;
    redA1 = redA + (ty+4*32+16)*16;
    redB0 = redB + (tx+4*32)*16;
    redB1 = redB + (tx+4*32+16)*16;


    asm volatile("\n \
    ds_read_b128 %0, %4 \n \
    ds_read_b128 %1, %5 \n \
    ds_read_b128 %2, %6 \n \
    ds_read_b128 %3, %7 \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA + (ty + 4*32)*16), "v"(redA + (ty+16+4*32)*16), "v"(redB + (tx+4*32)*16), "v"(redB + (tx+16+4*32)*16)
    );

    lgkmcnt<0>();

    outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
    outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
    outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
    outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

// i = 5
    redA0 = redA + (ty+5*32)*16;
    redA1 = redA + (ty+5*32+16)*16;
    redB0 = redB + (tx+5*32)*16;
    redB1 = redB + (tx+5*32+16)*16;


    asm volatile("\n \
    ds_read_b128 %0, %4 \n \
    ds_read_b128 %1, %5 \n \
    ds_read_b128 %2, %6 \n \
    ds_read_b128 %3, %7 \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA + (ty + 5*32)*16), "v"(redA + (ty+16+5*32)*16), "v"(redB + (tx+5*32)*16), "v"(redB + (tx+16+5*32)*16)
    );

    lgkmcnt<0>();

    outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
    outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
    outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
    outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

// i = 6
    redA0 = redA + (ty+6*32)*16;
    redA1 = redA + (ty+6*32+16)*16;
    redB0 = redB + (tx+6*32)*16;
    redB1 = redB + (tx+6*32+16)*16;


    asm volatile("\n \
    ds_read_b128 %0, %4 \n \
    ds_read_b128 %1, %5 \n \
    ds_read_b128 %2, %6 \n \
    ds_read_b128 %3, %7 \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA + (ty + 6*32)*16), "v"(redA + (ty+16+6*32)*16), "v"(redB + (tx+6*32)*16), "v"(redB + (tx+16+6*32)*16)
    );

    lgkmcnt<0>();

    outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
    outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
    outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
    outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

// i = 7
    redA0 = redA + (ty+7*32)*16;
    redA1 = redA + (ty+7*32+16)*16;
    redB0 = redB + (tx+7*32)*16;
    redB1 = redB + (tx+7*32+16)*16;


    asm volatile("\n \
    ds_read_b128 %0, %4 \n \
    ds_read_b128 %1, %5 \n \
    ds_read_b128 %2, %6 \n \
    ds_read_b128 %3, %7 \n \
    "
    :"=v"(a0),"=v"(a1), "=v"(b0), "=v"(b1)
    :"v"(redA + (ty + 7*32)*16), "v"(redA + (ty+16+7*32)*16), "v"(redB + (tx+7*32)*16), "v"(redB + (tx+16+7*32)*16)
    );

    lgkmcnt<0>();

    outerProduct4x4(a0, b0, c[0], c[1], c[2], c[3]);
    outerProduct4x4(a0, b1, c[4], c[5], c[6], c[7]);
    outerProduct4x4(a1, b0, c[8], c[9], c[10], c[11]);
    outerProduct4x4(a1, b1, c[12], c[13], c[14], c[15]);

    redA = redA ^ 0x2000;
    redB = redB ^ 0x2000;

//}




}
    global_store<0>(C, c[0], cid0);
    global_store<0>(C, c[1], cid1);
    global_store<0>(C, c[2], cid2);
    global_store<0>(C, c[3], cid3);

    global_store<16>(C, c[4], cid0);
    global_store<16>(C, c[5], cid1);
    global_store<16>(C, c[6], cid2);
    global_store<16>(C, c[7], cid3);

    global_store<0>(C, c[8], cid8);
    global_store<0>(C, c[9], cid9);
    global_store<0>(C, c[10], cid10);
    global_store<0>(C, c[11], cid11);

    global_store<16>(C, c[12], cid8);
    global_store<16>(C, c[13], cid9);
    global_store<16>(C, c[14], cid10);
    global_store<16>(C, c[15], cid11);


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
            _a[i + j * xDim] = (j+i*xDim)*1.0f + 1.0f;
            if(i == j) {
            _b[i + j * xDim] = 1.0f;
            } else {
            _b[i + j * xDim] = 0.0f;
            }
        }
    }

    Float4 *Ad, *Bd, *Cd;
    int *buffA, *buffB;
    hipHostMalloc(&buffA, 16*16*sizeof(int));
    hipHostMalloc(&buffB, 16*16*sizeof(int));
    hipMalloc(&Ad, a.size()*sizeof(Float4));
    hipMalloc(&Bd, b.size()*sizeof(Float4));
    hipMalloc(&Cd, c.size()*sizeof(Float4));
    hipMemcpy(Ad, a.data(), a.size()*sizeof(Float4), hipMemcpyHostToDevice);
    hipMemcpy(Bd, b.data(), b.size()*sizeof(Float4), hipMemcpyHostToDevice);
    hipMemcpy(Cd, c.data(), c.size()*sizeof(Float4), hipMemcpyHostToDevice);
    auto start = std::chrono::high_resolution_clock::now();
    hipLaunchKernelGGL(SGEMM, dim3(32,32,1), dim3(16,16,1), 4*sizeof(float)*8*128*2, 0, Ad, Bd, Cd, buffA, buffB);
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
