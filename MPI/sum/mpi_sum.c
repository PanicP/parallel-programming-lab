#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int r, sum = 0;

    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            r = rand();
            MPI_Send(&r, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
        }
        for (int i = 2; i < size; i++)
        {
            MPI_Recv(&r, 1, MPI_INT, MPI_ANY_SOURCE, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += r;
        }
        printf("total sum: %d\n", sum);
    }
    else
    {
        r = 0;
        MPI_Recv(&r, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int part = r * rank;
        MPI_Send(&part, 1, MPI_INT, 0, 234, MPI_COMM_WORLD);
    }
    MPI_Finalize();

    return 0;
}
