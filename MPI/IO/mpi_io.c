#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int size, rank;
    MPI_Init(0, 0);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char charToWritten = '0' + rank;

    // Open File
    MPI_File_open(MPI_COMM_WORLD, "test.out",
                  MPI_MODE_CREATE | MPI_MODE_WRONLY,
                  MPI_INFO_NULL, &fh);
    // Calculate displacement (offset from the begining)
    int displacement = ;

    // Calculate offset (jump to next position)
    int offset = ;

    for (int i = 0; i < 5; i++)
    {
        // write to file AT correct position
    }

    // close file

    MPI_Finalize();
    return 0;
}