#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int color = world_rank / 2;
    MPI_Comm sub_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &sub_comm);

    int sub_rank;
    MPI_Comm_rank(sub_comm, &sub_rank);
    int sub_size;
    MPI_Comm_size(sub_comm, &sub_size);

    printf("WORLD RANK/SIZE: %d/%d --- SUB COMM RANK/SIZE: %d/%d\n",
           world_rank, world_size, sub_rank, sub_size);

    MPI_Comm_free(&sub_comm);
    MPI_Finalize();
    return 0;
}