#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number;
    if (world_rank == 0)
    {
        number = -1;
        MPI_Sendrecv(&number, 1, MPI_INT, 1, 123, &number, 1, MPI_INT, 1, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received number %d from process 1\n", number);
    }
    else if (world_rank == 1)
    {
        MPI_Recv(&number, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        number = number * 2;
        MPI_Send(&number, 1, MPI_INT, 0, 234, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
