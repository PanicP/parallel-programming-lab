#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define KIB 1024
#define MIB (KIB * 1024)
#define GIB (MIB * 1024)

int main(int argc, char **argv)
{
    MPI_Init(0, 0);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        char *buffer = 0;
        for (int s = 128; s < 100 * MIB; s *= 2)
        {
            buffer = malloc(s);
            double start = MPI_Wtime();
            for (int i = 0; i < 25; i++)
            {
                // PING
                MPI_Ssend(buffer, s, MPI_CHAR, 1, 17, MPI_COMM_WORLD);
            }
            double end = MPI_Wtime();

            double duration = (end - start) / 25;
            double MiBpS = (((double)s) / ((double)1024 * 1024)) / duration;
            double sizeInMB = ((double)s) / (1024.0 * 1024.0);

            // printf("%d ; %0.15lf ; \n", s, ((end-start)/25.0));
            printf("Bandwidth with packet size %lf: %lf MiB/sec.\n", sizeInMB, MiBpS);
            free(buffer);
        }
    }
    else if (rank == 1)
    {
        char *buffer = 0;
        for (int s = 128; s < 100 * MIB; s *= 2)
        {
            buffer = malloc(s);
            for (int i = 0; i < 25; i++)
            {
                // PING
                MPI_Recv(buffer, s, MPI_CHAR, 0, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            free(buffer);
        }
    }
    else
    {
    }

    MPI_Finalize();
    return 0;
}
