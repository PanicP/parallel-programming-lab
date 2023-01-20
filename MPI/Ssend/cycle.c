#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int size;
    int rank;
    int Left, Right, buffer, buffer2, sum;
    double start = 0;
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Left = (rank + size - 1) % size;
    Right = (rank + 1) % size;
    // Code here

    // if (rank == 0)
    // {
    //     MPI_Ssend(&rank, 1, MPI_INT, Right, 123, MPI_COMM_WORLD);
    //     MPI_Recv(&buffer, 1, MPI_INT, Left, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    //     sum += buffer;
    //     // Send
    //     MPI_Ssend(&sum, 1, MPI_INT, Right, 234, MPI_COMM_WORLD);
    //     MPI_Recv(&buffer, 1, MPI_INT, Left, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // }
    // else
    // {
    //     sum = rank;
    //     MPI_Recv(&buffer, 1, MPI_INT, Left, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     sum += buffer;
    //     MPI_Ssend(&sum, 1, MPI_INT, Right, 123, MPI_COMM_WORLD);

    //     // Recv
    //     MPI_Recv(&sum, 1, MPI_INT, Left, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     MPI_Ssend(&sum, 1, MPI_INT, Right, 234, MPI_COMM_WORLD);
    // }

    // alternative

    buffer = rank;
    sum += buffer;
    MPI_Request req;

    for (int i = 0; i < size; i++)
    {
        MPI_Issend(&buffer, 1, MPI_INT, Right, 123, MPI_COMM_WORLD, &req);
        MPI_Recv(&buffer2, 1, MPI_INT, Left, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sum += buffer2;
        MPI_Wait(&req, MPI_STATUS_IGNORE);
        buffer = buffer2;
    }

    double end = MPI_Wtime();
    if (rank == 0)
        printf("Required time: %lf\n", (end - start));

    printf("rank: %d, sum: %d\n", rank, sum);

    MPI_Finalize();
    return 0;
}