// Example program
#include <iostream>
#include <string>
#include <vector>

void doMatMul(float* A, float *B, float *C, size_t dim_x, size_t dim_y) {
  for(size_t j=0;j<dim_y;j++) {
    for(size_t i=0;i<dim_x;i++) {
      float val = C[i+j*dim_x];
      for(size_t k=0;k<dim_x;k++) {
        val += A[k*dim_x+i] * B[k*dim_x+j];
      }
      C[i+j*dim_x] = val;
    }
  }
}

int main()
{
  const size_t dim_x = 4;
  const size_t dim_y = 4;
  std::vector<float> A(dim_x*dim_y), B(dim_x*dim_y), C(dim_x*dim_y);
  for(int j=0;j<dim_y;j++) {
      for(int i=0;i<dim_x;i++) {
          A[i+j*dim_x] = 1.0f + (i + j * dim_x);
          C[i+j*dim_x] = 0.0f;
          if(i == j) {
              B[i + j * dim_x] = 1.0f;
          } else {
              B[i + j * dim_x] = 0.0f;
          }
      }
  }
    for(int j=0;j<dim_y;j++) {
      for(int i=0;i<dim_x;i++) {
        std::cout<<A[i+j*dim_x]<<" ";
      }
      std::cout<<std::endl;
  }
  std::cout<<std::endl;
    for(int j=0;j<dim_y;j++) {
      for(int i=0;i<dim_x;i++) {
        std::cout<<B[i+j*dim_x]<<" ";
      }
      std::cout<<std::endl;
  }
  std::cout<<std::endl;
  doMatMul(A.data(), B.data(), C.data(), dim_x, dim_y);
  for(int j=0;j<dim_y;j++) {
      for(int i=0;i<dim_x;i++) {
        std::cout<<C[i+j*dim_x]<<" ";
      }
      std::cout<<std::endl;
  }
}

