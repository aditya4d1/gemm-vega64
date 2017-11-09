#include "../global_ops.h"
#include "../datatypes.h"
#include "../dims.h"

__global__ void Copy(Float4 *cSrc, Float4 *cDst) {
    int tx = hipThreadIdx_x;
    int ty = hipThreadIdx_y;
    int bx = hipBlockIdx_x;
    int by = hipBlockIdx_y;

    int id = tx + (ty % 2) * 16 + (ty / 2) * dim_x4 + bx * 32 + by * 8192;
    for(int i = 0; i< 16;i++) {
        cDst[id + i * 262144] = cSrc[id + i * 262144];
    }
}



int main() {
    Float4 *Ad, *Bd;
    hipHostMalloc(&Ad, size);
    hipHostMalloc(&Bd, size);
    for(int i=0;i<dim_x4*dim_y;i++) {
        Ad[i] = Float4(1.0f);
        Bd[i] = Float4(0.0f);
    }
    hipLaunchKernelGGL(Copy, dim3(dim_x4/(2*16), dim_y4/(2*16), 1), dim3(16,16,1), 0, 0, Ad, Bd);
    hipDeviceSynchronize();
    for(int i=0;i<dim_x4*dim_y;i++) {
        if(Bd[i].x != Ad[i].x || Bd[i].y != Ad[i].y || Bd[i].z != Ad[i].z || Bd[i].w != Ad[i].w) {
            std::cout<<"Bad output at: "<<i<<std::endl;
            return 0;
        }
    }

}
