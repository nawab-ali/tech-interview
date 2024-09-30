#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int rank = 0, numtasks = 0, len = 0;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(hostname, &len);

    printf("Hello from task %d on host %s\n", rank, hostname);

    if (rank == 0) {
        printf("Number of MPI tasks: %d\n", numtasks);
    }

    MPI_Finalize();
    return (0);
}
