// #include "mpi.h"
// #include <stdio.h>

// int main(int argc,char *argv[] )
// {
//     int rank;
//     int size;
//     MPI_Init( &argc, &argv );
//     MPI_Comm_rank( MPI_COMM_WORLD, &rank );
//     MPI_Comm_size( MPI_COMM_WORLD, &size );
//     printf( "rank = %d and size = %d \n", rank, size);
//     MPI_Finalize();
//     return 0;
// }

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int size, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  printf("Hello World from Rank %d/%d\n", rank, size);
  
  MPI_Finalize();
  return 0;
}