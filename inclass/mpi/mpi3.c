#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[] )
{
    int rank;
    MPI_Status status;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    int x = 10, y = 20;

    if( rank == 0 ){
        x = 100;
        MPI_Send( &x, 1, MPI_INT, 1, 123, MPI_COMM_WORLD );
        printf("test");
    }
    else if( rank == 1 ){
        MPI_Recv( &y, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status );
        printf("test2");
    }

    MPI_Finalize();
    return 0;
}