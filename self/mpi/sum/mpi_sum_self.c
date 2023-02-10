#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        int sum = 0;
        for (int i = 1; i < size; i++)
        {
            int r = rand();
            MPI_Send(&r, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
        }
        for (int i = 1; i < size; i++)
        {
            int calc;
            MPI_Recv(&calc, 1, MPI_INT, i, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += calc;
        }
        printf("sum: %d", sum);
    }
    else
    {
        int r;
        MPI_Recv(&r, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int calc = r * rank;
        MPI_Send(&calc, 1, MPI_INT, 0, 234, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}