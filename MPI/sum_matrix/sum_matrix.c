// Sum a 2D matrix in parallel using MPI

#include <assert.h>
#include <mpi.h>
#include <stdio.h>

#define SIZE 8
int sum_buffer(const int *buffer);
void print_buffer(const int *buffer, const int rank);

int main(int argc, char **argv) {
    int sum, partial_sum;
    int numtasks, rank, src = 0;
    int sendbuf[SIZE][SIZE], recvbuf[SIZE];
    int sendcount = SIZE, recvcount = SIZE;

    // Initialize sendbuf
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sendbuf[i][j] = j;
        }
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    assert(numtasks == SIZE);

    MPI_Scatter(sendbuf, sendcount, MPI_INT, recvbuf, recvcount, MPI_INT, src,
                MPI_COMM_WORLD);

    print_buffer(recvbuf, rank);
    partial_sum = sum_buffer(recvbuf);

    MPI_Reduce(&partial_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Task: %d sum: %d\n", rank, sum);
    }

    MPI_Finalize();
    return (0);
}

void print_buffer(const int *buffer, const int rank) {
    printf("Task: %d -- recvbuf: ", rank);
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int sum_buffer(const int *buffer) {
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += buffer[i];
    }
    return (sum);
}
