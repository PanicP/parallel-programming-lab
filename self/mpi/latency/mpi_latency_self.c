#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data = 8;

    if (rank == 0)
    {
        double start = MPI_Wtime();
        for (int i = 0; i < 1000; i++)
        {
            MPI_Ssend(&data, 1, MPI_DOUBLE, 1, 123, MPI_COMM_WORLD);
            MPI_Recv(&data, 1, MPI_DOUBLE, 1, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        double end = MPI_Wtime();
        printf("ping: %.15f", (end - start) / 2000);
    }
    if (rank == 1)
    {
        for (int i = 0; i < 1000; i++)
        {
            MPI_Recv(&data, 1, MPI_DOUBLE, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Ssend(&data, 1, MPI_DOUBLE, 0, 234, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}