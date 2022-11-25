#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL); // mandatory

    char host[128];
    gethostname(host, 128);

    printf("Hello World %s\n", host);
    MPI_Finalize();// mandatory
    return 0;
}

// mpicc mpi.c -o mpi