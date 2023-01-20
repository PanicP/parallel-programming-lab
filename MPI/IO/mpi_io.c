#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int size, rank;
    MPI_Init(0, 0);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char charToWrite = '0' + rank;

    // Open File
    MPI_File fh;
    MPI_File_open(MPI_COMM_WORLD, "myfile.txt", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

    // Calculate displacement (offset from the begining)
    int displacement = rank;

    // Calculate offset (jump to next position)
    int offset = size-1;

    for (int i = 0; i < 5; i++)
    {
        MPI_File_write_at(fh, (offset*i)+rank, &charToWrite, 1, MPI_CHAR, MPI_STATUS_IGNORE);
        // write to file AT correct position
    }

    // close file
    MPI_File_close(&fh);

    MPI_Finalize();
    return 0;
}

// mpicc mpi_io.c -o mpi_io
// mpirun -np 8 ./mpi_io