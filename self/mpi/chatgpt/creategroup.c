#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    MPI_Comm subgroup;
    MPI_Group world_group, subgroup_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);

    // Create a subgroup of the even-numbered processes
    int subgroup_ranks[world_size / 2];
    int subgroup_size = 0;
    for (int i = 0; i < world_size; i++)
    {
        if (i % 2 == 0)
        {
            subgroup_ranks[subgroup_size++] = i;
        }
    }
    MPI_Group_incl(world_group, subgroup_size, subgroup_ranks, &subgroup_group);
  MPI_Comm_create_group(MPI_COMM_WORLD, subgroup_group, 0, &
}