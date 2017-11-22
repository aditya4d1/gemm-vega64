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

/*
    asm volatile("\n \
    ds_write_b128 %0, %2 \n \
    ds_write_b128 %1, %3 \n \
    s_waitcnt lgkmcnt(0) \n \
    "
    :
    :"v"(redA + id*16), "v"(redB + id*16), "v"(ra), "v"(rb)
    );
*/

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

/*
    c[0].x += a0.x * b0.x;
    c[0].y += a0.x * b0.y;
    c[0].z += a0.x * b0.z;
    c[0].w += a0.x * b0.w;

    c[1].x += a0.y * b0.x;
    c[1].y += a0.y * b0.y;
    c[1].z += a0.y * b0.z;
    c[1].w += a0.y * b0.w;

    c[2].x += a0.z * b0.x;
    c[2].y += a0.z * b0.y;
    c[2].z += a0.z * b0.z;
    c[2].w += a0.z * b0.w;

    c[3].x += a0.w * b0.x;
    c[3].y += a0.w * b0.y;
    c[3].z += a0.w * b0.z;
    c[3].w += a0.w * b0.w;


    c[4].x += a0.x * b1.x;
    c[4].y += a0.x * b1.y;
    c[4].z += a0.x * b1.z;
    c[4].w += a0.x * b1.w;

    c[5].x += a0.y * b1.x;
    c[5].y += a0.y * b1.y;
    c[5].z += a0.y * b1.z;
    c[5].w += a0.y * b1.w;

    c[6].x += a0.z * b1.x;
    c[6].y += a0.z * b1.y;
    c[6].z += a0.z * b1.z;
    c[6].w += a0.z * b1.w;

    c[7].x += a0.w * b1.x;
    c[7].y += a0.w * b1.y;
    c[7].z += a0.w * b1.z;
    c[7].w += a0.w * b1.w;

    c[8].x += a1.x * b0.x;
    c[8].y += a1.x * b0.y;
    c[8].z += a1.x * b0.z;
    c[8].w += a1.x * b0.w;

    c[9].x += a1.y * b0.x;
    c[9].y += a1.y * b0.y;
    c[9].z += a1.y * b0.z;
    c[9].w += a1.y * b0.w;

    c[10].x += a1.z * b0.x;
    c[10].y += a1.z * b0.y;
    c[10].z += a1.z * b0.z;
    c[10].w += a1.z * b0.w;

    c[11].x += a1.z * b0.x;
    c[11].y += a1.z * b0.y;
    c[11].z += a1.z * b0.z;
    c[11].w += a1.z * b0.w;


    c[12].x += a1.x * b1.x;
    c[12].y += a1.x * b1.y;
    c[12].z += a1.x * b1.z;
    c[12].w += a1.x * b1.w;

    c[13].x += a1.y * b1.x;
    c[13].y += a1.y * b1.y;
    c[13].z += a1.y * b1.z;
    c[13].w += a1.y * b1.w;

    c[14].x += a1.z * b1.x;
    c[14].y += a1.z * b1.y;
    c[14].z += a1.z * b1.z;
    c[14].w += a1.z * b1.w;

    c[15].x += a1.w * b1.x;
    c[15].y += a1.w * b1.y;
    c[15].z += a1.w * b1.z;
    c[15].w += a1.w * b1.w;
*/

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
