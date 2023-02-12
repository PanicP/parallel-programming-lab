#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int size, rank;
    MPI_Init(0, 0);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char charToWrite = 'a' + rank;

    // Open file
    MPI_File fh;
    int amode = MPI_MODE_CREATE | MPI_MODE_WRONLY;
    MPI_File_open(MPI_COMM_WORLD,
                  "myfile.txt",
                  amode,
                  MPI_INFO_NULL,
                  &fh);
    // Calculate displacement (offset from the beginning)
    int displacement = rank;
    // Calculate offset (jump to next position)
    int offset = size;

    for (int i = 0; i < 5; i++)
    {
        // write to file AT correct position
        MPI_File_write_at(fh, rank + (offset * i), &charToWrite, 1, MPI_CHAR, MPI_STATUS_IGNORE);
    }

    // close file
    MPI_File_close(&fh);

    MPI_Finalize();
    return 0;
}
