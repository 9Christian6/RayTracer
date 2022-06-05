#include "CUDA.h"
#include <iostream>

__global__ void vector_add(double *result, const double *lhs, const double *rhs)
{
    *result = 0;
}

void test(double *asdf)
{
    double *d;
    cudaMalloc(&d, sizeof(*d));
    cudaMemcpy(d, asdf, sizeof(double), cudaMemcpyHostToDevice);
    vector_add<<<1, 10>>>(d, nullptr, nullptr);
    cudaMemcpy(asdf, d, sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(d);
}