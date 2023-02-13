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

    // Open file
    MPI_File fh;
    int amode = MPI_MODE_CREATE | MPI_MODE_WRONLY;
    MPI_File_open(MPI_COMM_WORLD,
                  "myfile2.txt",
                  amode,
                  MPI_INFO_NULL,
                  &fh);

    int ndims = 1;
    int array_of_sizes[1] = {size};
    int array_of_subsizes[1] = {1};
    int array_of_starts[1] = {rank};
    MPI_Datatype elementType = MPI_CHAR;
    MPI_Datatype filetype;

    MPI_Type_create_subarray(ndims, array_of_sizes, array_of_subsizes, array_of_starts, MPI_ORDER_C, elementType, &filetype);
    MPI_Type_commit(&filetype);
    MPI_File_set_view(fh, 0, elementType, filetype, "native", MPI_INFO_NULL);

    for (int i = 0; i < 5; i++)
    {
        // write to file correct position
        MPI_File_write(fh, &charToWrite, 1, MPI_CHAR, MPI_STATUS_IGNORE);
    }

    // close file
    MPI_File_close(&fh);

    MPI_Finalize();
    return 0;
}
