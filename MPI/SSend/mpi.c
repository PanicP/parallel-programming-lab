#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int size;
    int rank;
    int Left, Right;
    MPI_Init(Null, Null);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Left = (rank + size - 1) % size;
    Right = (rank + 1) % size;
    // Code here
    for (int i = 0; i < size - 2; i++)
    {

        MPI_Ssend(99, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        MPI_Recv(&r, 1, MPI_INT, MPI_ANY_SOURCE, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        print("Rank %d, Value %d\n", rank, val)
    }

    MPI_Finalize();
    return 0;
}