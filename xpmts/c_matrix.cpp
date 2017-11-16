#include "../global_ops.h"
#include "../datatypes.h"
#include "../dims.h"

__global__ void Copy(Float4 *cSrc, Float4 *cDst) {
    int tx = hipThreadIdx_x;
    int ty = hipThreadIdx_y;
    int bx = hipBlockIdx_x;
    int by = hipBlockIdx_y;

    
  int c0_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*0;
  int c1_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*1;
  int c2_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*2;
  int c3_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*3;

  int c4_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*0 + half_tilex4;
  int c5_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*1 + half_tilex4;
  int c6_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*2 + half_tilex4;
  int c7_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + dim_x4*3 + half_tilex4;

  int c8_id  = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + dim_x4*0;
  int c9_id  = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + dim_x4*1;
  int c10_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + dim_x4*2;
  int c11_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + dim_x4*3;

  int c12_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + half_tilex4 + dim_x4*0;
  int c13_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + half_tilex4 + dim_x4*1;
  int c14_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + half_tilex4 + dim_x4*2;
  int c15_id = tx + ty * dim_x + bx * tilex4 + by * dim_x4 * tile + half_tile * dim_x4 + half_tilex4 + dim_x4*3;


    cDst[c0_id] = cSrc[c0_id];
    cDst[c1_id] = cSrc[c1_id];
    cDst[c2_id] = cSrc[c2_id];
    cDst[c3_id] = cSrc[c3_id];

    cDst[c4_id] = cSrc[c4_id];
    cDst[c5_id] = cSrc[c5_id];
    cDst[c6_id] = cSrc[c6_id];
    cDst[c7_id] = cSrc[c7_id];

    cDst[c8_id] = cSrc[c8_id];
    cDst[c9_id] = cSrc[c9_id];
    cDst[c10_id] = cSrc[c10_id];
    cDst[c11_id] = cSrc[c11_id];

    cDst[c12_id] = cSrc[c12_id];
    cDst[c13_id] = cSrc[c13_id];
    cDst[c14_id] = cSrc[c14_id];
    cDst[c15_id] = cSrc[c15_id];

}



int main() {
    Float4 *Ad, *Bd;
    hipHostMalloc(&Ad, size);
    hipHostMalloc(&Bd, size);
    float* ad = reinterpret_cast<float*>(Ad);
    float* bd = reinterpret_cast<float*>(Bd);
    for(int j=0;j<dim_y;j++) {
        for(int i=0;i<dim_x;i++) {
            ad[i+j*dim_x] = float(i+j*dim_x) + 1.0f;
            bd[i+j*dim_x] = 0.0f;
        }
    }
    hipLaunchKernelGGL(Copy, dim3(dim_x4/(2*16), dim_y4/(2*16), 1), dim3(16,16,1), 0, 0, Ad, Bd);
    hipDeviceSynchronize();
    for(int j=0; j<dim_y;j++) {
        for(int i=0;i<dim_x;i++) {
            if(ad[i+j*dim_x] != float(i+j*dim_x) + 1.0f) {
                std::cout<<"Bad output at: "<<i+j*dim_x<<std::endl;
                return 0;
            }
        }
    }

}
