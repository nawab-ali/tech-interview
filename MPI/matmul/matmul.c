// Parallel matrix multiplication using MPI

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void allocate_memory(float **a, const int size);
void initialize_matrix(float *a, const int nrows, const int ncols);
void print_matrix(float *a, const int nrows, const int ncols);
void matmul(float *recvbuf_a, float *b, float *sendbuf_c, const int recvcount,
            const int M, const int K, const int N);

int main(int argc, char **argv) {
    float *a, *b, *c;
    int numtasks, rank;
    int sendcount, recvcount;
    int M = 8 * 10000, K = 500, N = 25;
    float *recvbuf_a, *sendbuf_c;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    allocate_memory(&b, K * N);

    if (rank == 0) {
        srand(time(0));
        allocate_memory(&a, M * K);
        allocate_memory(&c, M * N);
        initialize_matrix(a, M, K);
        initialize_matrix(b, K, N);
    }

    allocate_memory(&recvbuf_a, (M * K) / numtasks);
    allocate_memory(&sendbuf_c, (M * N) / numtasks);

    MPI_Bcast(b, K * N, MPI_FLOAT, 0, MPI_COMM_WORLD);

    sendcount = recvcount = (M * K) / numtasks;
    MPI_Scatter(a, sendcount, MPI_FLOAT, recvbuf_a, recvcount, MPI_FLOAT, 0,
                MPI_COMM_WORLD);

    matmul(recvbuf_a, b, sendbuf_c, recvcount, M, K, N);

    sendcount = recvcount = (M * N) / numtasks;
    MPI_Gather(sendbuf_c, sendcount, MPI_FLOAT, c, recvcount, MPI_FLOAT, 0,
               MPI_COMM_WORLD);
    if (rank == 0) {
        print_matrix(c, M, N);
    }

    MPI_Finalize();
    return (0);
}

void allocate_memory(float **a, const int size) {
    *a = (float *)malloc(size * sizeof(float));
    memset(*a, 0, size * sizeof(float));
}

void initialize_matrix(float *a, const int nrows, const int ncols) {
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            a[i * ncols + j] = rand() % 10;
        }
    }
}

void print_matrix(float *a, const int nrows, const int ncols) {
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            printf("%0.2f ", a[i * ncols + j]);
        }
        printf("\n");
    }
}

void matmul(float *recvbuf_a, float *b, float *sendbuf_c, const int recvcount,
            const int M, const int K, const int N) {
    for (int i = 0; i < recvcount / K; i++) {
        for (int j = 0; j < N; j++) {
            for (int p = 0; p < K; p++) {
                sendbuf_c[i * N + j] += recvbuf_a[i * K + p] * b[p * N + j];
            }
        }
    }
}
