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
        int sum;
        for (int i = 1; i < size; i++)
        {
            int r = rand();
            MPI_Send(&r, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
        }
        for (int i = 1; i < size; i++)
        {
            int partSum;
            MPI_Recv(&partSum, 1, MPI_INT, i, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += partSum;
            printf("rank: %d partSum %d\n", rank, partSum);
        }
        printf("sum = %d\n", sum);
    }
    else
    {
        int rand;
        MPI_Recv(&rand, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int partSum = rand * rank;
        printf("rank: %d partSum %d\n", rank, partSum);
        MPI_Send(&partSum, 1, MPI_INT, 0, 234, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}