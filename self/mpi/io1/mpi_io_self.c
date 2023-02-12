#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char charToWrite = 'a' + rank;
    int amode = MPI_MODE_CREATE | MPI_MODE_WRONLY;
    MPI_File file;
    MPI_File_open(MPI_COMM_WORLD, "myfile.txt", amode, MPI_INFO_NULL, &file);

    int displacement = rank;
    int offset = size;

    for (int i = 0; i < 10; i++)
    {
        MPI_File_write_at(file, (offset * i) + displacement, &charToWrite, 1, MPI_CHAR, MPI_STATUS_IGNORE);
    }

    MPI_File_close(&file);

    MPI_Finalize();
    return 0;
}