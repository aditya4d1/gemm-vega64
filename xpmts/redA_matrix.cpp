#include "../global_ops.h"
#include "../datatypes.h"
#include "../dims.h"

__global__ void Copy(Float4 *cSrc, Float4 *cDst) {
    int tx = hipThreadIdx_x;
    int ty = hipThreadIdx_y;
    int bx = hipBlockIdx_x;
    int by = hipBlockIdx_y;

    int id = tx + (ty % 2) * 16 + (ty / 2) * dim_x4 + bx * 32 + by * 8192;
    Float4 c[16];
    for(int i = 0; i< 16;i++) {
        c[i] = cSrc[id + i * 262144];
    }
}



int main() {
    Float4 *Ad, *Bd;
    hipHostMalloc(&Ad, size);
    hipHostMalloc(&Bd, size);
    float* ad = reinterpret_cast<float*>(Ad);
    float* bd = reinterpret_cast<float*>(Bd);

    for(int j=0;j<dim_y;j++) {
        for(int i=0;i<dim_x;i++) {
            ad[i] = float(i + j * dim_x) + 1.0f;
            bd[i] = 0.0f;
        }
    }

    hipLaunchKernelGGL(Copy, dim3(dim_x4/(2*16), dim_y4/(2*16), 1), dim3(16,16,1), 0, 0, Ad, Bd);
    hipDeviceSynchronize();
    for(int j=0;j<dim_y;j++) {
    for(int i=0;i<dim_x;i++) {
        if(bd[i+j*dim_x] != ad[i+j*dim_x]) {
            std::cout<<"Bad output at: "<<i+j*dim_x<<std::endl;
            return 0;
        }
    }
    }

}
