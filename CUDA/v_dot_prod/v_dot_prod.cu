// Parallel vector dot product on GPU using CUDA

#include <math.h>
#include <stdio.h>

#define N (2048 * 2048)
#define BLOCKSIZE 512
#define NUMBLOCKS (N / BLOCKSIZE)

// Parallel vector dot product kernel
__global__ void v_dot_prod(float *a, float *b, float *c) {
    __shared__ float t_prod[BLOCKSIZE];
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    // Parallel vector multiplication
    for (int i = index; i < N; i += stride) {
        t_prod[threadIdx.x] = a[i] * b[i];
    }

    // Wait for all threads in the block to complete
    __syncthreads();

    // Serial summation of vector t_prod at block level
    if (threadIdx.x == 0) {
        float t_sum = 0.0;
        for (int i = 0; i < BLOCKSIZE; i++) {
            t_sum += t_prod[i];
        }
        // Add to global sum atomically
        atomicAdd(c, t_sum);
    }

    return;
}

int main(void) {
    float *x;
    float *y;
    float *sum;
    float t_sum = 0.0f;

    // Allocate unified memory for vectors and sum
    cudaMallocManaged(&x, N * sizeof(float));
    cudaMallocManaged(&y, N * sizeof(float));
    cudaMallocManaged(&sum, sizeof(float));

    // Initialize vectors
    *sum = 0.0f;
    for (int i = 0; i < N; i++) {
        x[i] = 2.0f;
        y[i] = 3.0f;
    }

    // Run the vector dot product kernel on the GPU
    v_dot_prod<<<NUMBLOCKS, BLOCKSIZE>>>(x, y, sum);

    // Wait for GPU to complete processing
    cudaDeviceSynchronize();

    // Verify the GPU results
    for (int i = 0; i < N; i++) {
        t_sum += x[i] * y[i];
    }

    printf("Error: %f\n", fabs(t_sum - *sum));

    // Free memory
    cudaFree(x);
    cudaFree(y);
    cudaFree(sum);

    return 0;
}
