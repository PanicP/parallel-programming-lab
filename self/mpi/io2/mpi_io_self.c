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

    // int displacement = rank;
    // int offset = size;
    int ndims = 1;
    int array_of_sizes[1] = {size};
    int array_of_subsizes[1] = {1};
    int array_of_starts[1] = {rank};
    MPI_Datatype elementType = MPI_CHAR;
    MPI_Datatype filetype;

    MPI_Type_create_subarray(ndims, array_of_sizes, array_of_subsizes, array_of_starts, MPI_ORDER_C, elementType, &filetype);
    MPI_Type_commit(&filetype);
    MPI_File_set_view(file, 0, elementType, filetype, "native", MPI_INFO_NULL);

    for (int i = 0; i < 10; i++)
    {
        MPI_File_write(file, &charToWrite, 1, MPI_CHAR, MPI_STATUS_IGNORE);
        // MPI_File_write_at(file, (offset * i) + displacement, &charToWrite, 1, MPI_CHAR, MPI_STATUS_IGNORE);
    }

    MPI_File_close(&file);

    MPI_Finalize();
    return 0;
}