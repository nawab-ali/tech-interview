// Parallel SAXPY using MPI
// y[] = ax[] + y[]

#include<mpi.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void allocate_vector_memory(float** x, float** y, const int bufsize);
void allocate_buffer_memory(float** recvbuf_x, float** recvbuf_y, const int numtasks, const int bufsize);
void initialize_vectors(float* a, float* x, float* y, const int bufsize);
void saxpy(float a, float* x, float* y, const int bufsize);

int main(int argc, char** argv) {
	float a;
	int numtasks, rank;
	int sendcount, recvcount;
	const int bufsize = 8*100;
 	float *x, *y, *recvbuf_x, *recvbuf_y;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		allocate_vector_memory(&x, &y, bufsize);
		initialize_vectors(&a, x, y, bufsize);
	}

	MPI_Bcast(&a, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

	allocate_buffer_memory(&recvbuf_x, &recvbuf_y, numtasks, bufsize);

	sendcount = recvcount = bufsize/numtasks;
	MPI_Scatter(x, sendcount, MPI_FLOAT, recvbuf_x, recvcount, MPI_FLOAT, 0, MPI_COMM_WORLD);
	MPI_Scatter(y, sendcount, MPI_FLOAT, recvbuf_y, recvcount, MPI_FLOAT, 0, MPI_COMM_WORLD);

	saxpy(a, recvbuf_x, recvbuf_y, recvcount);

	MPI_Gather(recvbuf_y, sendcount, MPI_FLOAT, y, recvcount, MPI_FLOAT, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		printf("\n");
		for (int i = 0; i < bufsize; i++) {
			printf("%0.2f ", y[i]);
		}
		printf("\n\n");
	}

	MPI_Finalize();
	return(0);
}

void allocate_vector_memory(float** x, float** y, const int bufsize) {
	*x = (float*)malloc(sizeof(float)*bufsize);
	*y = (float*)malloc(sizeof(float)*bufsize);
}

void allocate_buffer_memory(float** recvbuf_x, float** recvbuf_y, const int numtasks, const int bufsize) {
	*recvbuf_x = (float*)malloc(sizeof(float)*(bufsize/numtasks));
	*recvbuf_y = (float*)malloc(sizeof(float)*(bufsize/numtasks));
}

void initialize_vectors(float* a, float* x, float* y, const int bufsize) {
	srand(time(0));
	*a = rand() % 100;
	for (int i = 0; i < bufsize; i++) {
		x[i] = rand() % 100;
		y[i] = rand() % 100;
	}
}

void saxpy(float a, float* x, float* y, const int bufsize) {
	for (int i = 0; i < bufsize; i++) {
		y[i] += a*x[i];
	}
}
