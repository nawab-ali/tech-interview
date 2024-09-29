//Matrix transpose on GPU using CUDA

#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define M (4096)
#define N (8192)

//CUDA kernel for matrix transpose operation
__global__
void m_transpose(float *a, float *a_t) {
	int row = blockIdx.y * blockDim.y  + threadIdx.y;
	int col = blockIdx.x * blockDim.x  + threadIdx.x;

	int index1 = (row * N) + col;
	int index2 = (col * M) + row;

	if (row < M && col < N) {
		a_t[index2] = a[index1];
	}

	return;
}

int main(int argc, char **argv) {
	float *A, *A_T;
	float max_err = 0.0f;
	int size = M * N * sizeof(float);
	dim3 threads_per_blk(16, 16, 1);
	dim3 blocks_per_grid((N+threads_per_blk.x-1)/threads_per_blk.x,
											 (M+threads_per_blk.y-1)/threads_per_blk.y,
												1);

	//Seed the random number generator
	srand(time(NULL));

	//Allocate unified memory for matrices A and A_T
	cudaMallocManaged(&A, size);
	cudaMallocManaged(&A_T, size);

	//Initialize matrix A (MxN)
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			int index = i * N + j;
			A[index] = float(rand() % 100000 + 1.0f);
		}
	}

	//Launch transpose kernel on GPU
	m_transpose<<<blocks_per_grid, threads_per_blk>>>(A, A_T);

	//Wait for GPU to finish
	cudaDeviceSynchronize();

	//Verify GPU transpose operation
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			int index1 = i * N + j;
			int index2 = j * M + i;
			max_err = fabs(fmax(max_err, (A[index1] - A_T[index2])));
		}
	}

	printf("Max error: %f\n", max_err);

	//Free unified memory
	cudaFree(A);
	cudaFree(A_T);

	return 0;
}
