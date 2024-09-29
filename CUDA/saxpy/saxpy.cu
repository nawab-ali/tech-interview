//Parallel SAXPY on GPU using CUDA
//z = ax + y

#include<math.h>
#include<stdio.h>

//CUDA SAXPY kernel
__global__
void saxpy(int n, float a, float *x, float *y) {
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;

	for (int i = index; i < n; i += stride) {
		y[i] = a * x[i] + y[i];
	}
	return;
}

int main() {
	float *x;
	float *y;
	int N = 1<<25;
	float a = 2.0f;
	float max_err = 0.0;
	int blocksize = 256;
	int nblocks = (N + blocksize - 1) / blocksize;

	//Allocate unified memory for vectors x, y
	cudaMallocManaged(&x, N*sizeof(float));
	cudaMallocManaged(&y, N*sizeof(float));

	//Initialize x, y
	for (int i = 0; i < N; i++) {
		x[i] = 2.0f;
		y[i] = 3.0f;
	}

	//Run SAXPY kernel on the GPU
	saxpy<<<nblocks, blocksize>>>(N, a, x, y);

	//Wait for GPU to finish
	cudaDeviceSynchronize();

	//Verify results
	for (int i = 0; i < N; i++) {
		max_err = fmax(max_err, fabs(y[i] - 7.0f));
	}

	printf("Max error: %f\n", max_err);

	//Free memory
	cudaFree(x);
	cudaFree(y);

	return 0;
}
