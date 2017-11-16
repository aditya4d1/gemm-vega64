/**
* Working code for
* 1. Global load from A, B and C
* 2. Write to LDS
* 3. Read from LDS
* 4. One iteration of outer product
* 5. Store to global
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
    int cid1 = tx + ty * 4 * xDim4 + 1*32;
    int cid2 = tx + ty * 4 * xDim4 + 2*32;
    int cid3 = tx + ty * 4 * xDim4 + 3*32;

    int cid4 = tx + ty * 4 * xDim4 + 16 + 0*32;
    int cid5 = tx + ty * 4 * xDim4 + 16 + 1*32;
    int cid6 = tx + ty * 4 * xDim4 + 16 + 2*32;
    int cid7 = tx + ty * 4 * xDim4 + 16 + 3*32;

    int cid8 = tx + ty * 4 * xDim4 + 0*32 + 64*32;
    int cid9 = tx + ty * 4 * xDim4 + 1*32 + 64*32;
    int cid10= tx + ty * 4 * xDim4 + 2*32 + 64*32;
    int cid11= tx + ty * 4 * xDim4 + 3*32 + 64*32;

    int cid12= tx + ty * 4 * xDim4 + 16 + 64*32 + 0*32;
    int cid13= tx + ty * 4 * xDim4 + 16 + 64*32 + 1*32;
    int cid14= tx + ty * 4 * xDim4 + 16 + 64*32 + 2*32;
    int cid15= tx + ty * 4 * xDim4 + 16 + 64*32 + 3*32;


    c[0] = C[cid0];
    c[1] = C[cid1];
    c[2] = C[cid2];
    c[3] = C[cid3];

    c[4] = C[cid4];
    c[5] = C[cid5];
    c[6] = C[cid6];
    c[7] = C[cid7];

    c[8] = C[cid8];
    c[9] = C[cid9];
    c[10] = C[cid10];
    c[11] = C[cid11];

    c[12] = C[cid12];
    c[13] = C[cid13];
    c[14] = C[cid14];
    c[15] = C[cid15];

    getGlobalCId[tx + ty * 16] = cid12;

    __shared__ Float4 sA[8*32];
    __shared__ Float4 sB[8*32];

    sA[id] = A[id];
    sB[id] = B[id];

    for(int i=0; i< 8;i++) {
    a0 = sA[ty + i*32];
    a1 = sA[ty+16 + i*32];
    b0 = sB[tx + i*32];
    b1 = sB[tx+16 + i*32];

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
}
    C[cid0] = c[0];
    C[cid1] = c[1];
    C[cid2] = c[2];
    C[cid3] = c[3];

    C[cid4] = c[4];
    C[cid5] = c[5];
    C[cid6] = c[6];
    C[cid7] = c[7];

    C[cid8] = c[8];
    C[cid9] = c[9];
    C[cid10] = c[10];
    C[cid11] = c[11];

    C[cid12] = c[12];
    C[cid13] = c[13];
    C[cid14] = c[14];
    C[cid15] = c[15];


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
    hipLaunchKernelGGL(SGEMM, dim3(1,1,1), dim3(16,16,1), 4*sizeof(float)*8*128, 0, Ad, Bd, Cd, buffA, buffB);
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
