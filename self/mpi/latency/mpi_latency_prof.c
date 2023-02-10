#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(0, 0);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    float data = 0.0f;
    if (rank == 0)
    {
        double start = MPI_Wtime();
        for (int i = 0; i < 1000; i++)
        {
            // PING
            MPI_Ssend(&data, 1, MPI_FLOAT, 1, 17, MPI_COMM_WORLD);
            // PONG
            MPI_Recv(&data, 1, MPI_FLOAT, 1, 23, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        double end = MPI_Wtime();

        printf("t ping/pong: %0.15lf\n", ((end - start) / 2000.0));
    }
    else if (rank == 1)
    {

        for (int i = 0; i < 1000; i++)
        {
            // PING
            MPI_Recv(&data, 1, MPI_FLOAT, 0, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // PONG
            MPI_Ssend(&data, 1, MPI_FLOAT, 0, 23, MPI_COMM_WORLD);
        }
    }
    else
    {
    }

    MPI_Finalize();
    return 0;
}
