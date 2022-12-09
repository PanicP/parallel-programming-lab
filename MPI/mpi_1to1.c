// #include <stdio.h>
// #include <mpi.h>
// #include <unistd.h>

// int main(int argc, char** argv) {
//     int rank, size;
//     MPI_Status status;

//     MPI_Init(NULL, NULL); // mandatory

//     char host[128];
//     gethostname(host, 128);

//     printf("Hello World %s \n", host);

//     MPI_Comm_size( MPI_COMM_WORLD, &size );
//     MPI_Comm_rank( MPI_COMM_WORLD, &rank );
//     printf("size %d rank %d\n", size, rank);

//     int x = 10, y = 20;

//     if( rank <= 4 ){
//         x = 100;
//         MPI_Send( &x, 1, MPI_INT, 1, 123, MPI_COMM_WORLD );
//         printf("test");
//     }
//     else if( rank >= 5 ){
//         MPI_Recv( &y, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status );
//         printf("test2");
//     }

//     MPI_Finalize();// mandatory
//     return 0;
// }

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Status status;
  int a;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    a = 123;
    MPI_Send(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } else if (rank == 1) {
    a = 456;
    MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  }
  printf("Process %d : a = %d\n", rank, a);
  
  MPI_Finalize();
  return 0;
}