#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define KiB 1024
#define MiB KiB * 1024
#define GiB MiB * 1024
#define amount 25
int main(int argc, char **argv)
{
    MPI_Init(0, 0);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        char *buffer = 0;
        for (int s = 128; s < 100 * MiB; s *= 2)
        {
            buffer = malloc(s);
            double start = MPI_Wtime();
            for (int i = 0; i < amount; i++)
            {
                MPI_Ssend(buffer, s, MPI_CHAR, 1, 123, MPI_COMM_WORLD);
            }
            double end = MPI_Wtime();

            double duration = (end - start) / amount;
            double size = ((double)s) / ((double)MiB);
            double MiBpS = size / ((double)duration);

            printf("bandwidth for data size: %.5f => %.5f\n", size, MiBpS);

            free(buffer);
        }
    }

    if (rank == 1)
    {
        char *buffer = 0;
        for (int s = 128; s < 100 * MiB; s *= 2)
        {
            buffer = malloc(s);
            for (int i = 0; i < amount; i++)
            {
                MPI_Recv(buffer, s, MPI_CHAR, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            free(buffer);
        }
    }
    MPI_Finalize();
    return 0;
}