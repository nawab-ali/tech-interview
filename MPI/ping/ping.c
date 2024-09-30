#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int src, dest;
    int numtasks, rank;
    int count, tag = 1;
    char inmsg, outmsg = 'x';
    MPI_Status stat;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        src = 1, dest = 1;
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, 1, MPI_CHAR, src, tag, MPI_COMM_WORLD, &stat);
    } else if (rank == 1) {
        src = 0, dest = 0;
        MPI_Recv(&inmsg, 1, MPI_CHAR, src, tag, MPI_COMM_WORLD, &stat);
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    }

    if (rank == 0 || rank == 1) {
        MPI_Get_count(&stat, MPI_CHAR, &count);
        printf("Task %d received %d char(s) from task %d with tag %d\n", rank,
               count, stat.MPI_SOURCE, stat.MPI_TAG);
    }

    MPI_Finalize();
    return (0);
}
