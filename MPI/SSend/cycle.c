#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int size;
    int rank;
    int Left, Right, buffer, sum;
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Left = (rank + size - 1) % size;
    Right = (rank + 1) % size;
    // Code here
    // if (rank < size - 2)
    // {
    //     MPI_Ssend(&r, 1, MPI_INT, rank + 1, 123, MPI_COMM_WORLD);
    // }
    // if (rank >= 0)
    // {
    //     MPI_Recv(&r, 1, MPI_INT, MPI_ANY_SOURCE, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // }
    // for (int i = 0; i < size - 2; i++)
    // {

    //     MPI_Ssend(99, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
    // }

    // for (int i = size - 1; i >= 0; i--)
    // {
    //     MPI_Recv(&r, 1, MPI_INT, MPI_ANY_SOURCE, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     print("Rank %d, Value %d\n", rank, val)
    // }
    if (rank == 0)
    {
        MPI_Ssend(&rank, 1, MPI_INT, Right, 123, MPI_COMM_WORLD);
        MPI_Recv(&buffer, 1, MPI_INT, Left, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        sum += buffer;
        // Send
        MPI_Ssend(&sum, 1, MPI_INT, Right, 234, MPI_COMM_WORLD);
        MPI_Recv(&buffer, 1, MPI_INT, Left, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else
    {
        sum = rank;
        MPI_Recv(&buffer, 1, MPI_INT, Left, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sum += buffer;
        MPI_Ssend(&sum, 1, MPI_INT, Right, 123, MPI_COMM_WORLD);

        // Recv
        MPI_Recv(&sum, 1, MPI_INT, Left, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(&sum, 1, MPI_INT, Right, 234, MPI_COMM_WORLD);
    }

    double end = MPI_Wtime();
    if (rank == 0)
        printf("Required time: %lf\n", (end - start));

    MPI_Finalize();
    return 0;
}