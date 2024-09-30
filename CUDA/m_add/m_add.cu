// Parallel Matrix-Matrix addition on GPU using CUDA
// Matrix dimensions are MxN
// C = A + B

#include <math.h>
#include <stdio.h>

#define M (8192)
#define N (4096)

// Parallel Matrix-Matrix addition kernel
__global__ void m_add(float *a, float *b, float *c) {
    int index = 0;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < M && col < N) {
        index = row * N + col;
        c[index] = a[index] + b[index];
    }
    return;
}

int main(int argc, char **argv) {
    int index = 0;
    float *A, *B, *C;
    float max_err = 0.0f;
    int size = M * N * sizeof(float);

    // Define the Grid and Block dimensions
    dim3 threads_per_blk(16, 16);
    dim3 blocks_per_grid((N + threads_per_blk.x - 1) / threads_per_blk.x,
                         (M + threads_per_blk.y - 1) / threads_per_blk.y);

    // Allocate unified memory for linear 2D array
    cudaMallocManaged(&A, size);
    cudaMallocManaged(&B, size);
    cudaMallocManaged(&C, size);

    // Initialize the MxN matrices
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            index = i * N + j;
            A[index] = 2.0f;
            B[index] = 3.0f;
            C[index] = 0.0f;
        }
    }

    // Launch the kernel on the GPU
    m_add<<<blocks_per_grid, threads_per_blk>>>(A, B, C);

    // Wait for GPU to finish
    cudaDeviceSynchronize();

    // Verify GPU math
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            index = i * N + j;
            max_err = fmax(max_err, fabs(C[index] - (A[index] + B[index])));
        }
    }

    printf("Max error: %f\n", max_err);

    // Free memory
    cudaFree(A);
    cudaFree(B);
    cudaFree(C);

    return 0;
}
