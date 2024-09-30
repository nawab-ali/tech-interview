#include <iostream>
#include <math.h>

// GPU kernel to add the elements of 2 arrays
__global__ void add(int n, float *x, float *y) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    for (int i = index; i < n; i += stride) {
        y[i] = x[i] + y[i];
    }
}

int main(void) {
    int N = 1 << 20;
    float *x, *y;

    // Allocate unified memory
    cudaMallocManaged(&x, N * sizeof(float));
    cudaMallocManaged(&y, N * sizeof(float));

    // Initialize x, y arrays on the host
    for (int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    int blocksize = 256;
    int numblocks = (N + blocksize - 1) / blocksize;

    // Run kernel on 1M elements on the GPU
    add<<<numblocks, blocksize>>>(N, x, y);

    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();

    // Check for errors (all values should be 3.0f)
    float maxerror = 0.0f;
    for (int i = 0; i < N; i++) {
        maxerror = fmax(maxerror, fabs(y[i] - 3.0f));
    }
    std::cout << "Max error: " << maxerror << std::endl;

    // Free memory
    cudaFree(x);
    cudaFree(y);

    return 0;
}
