#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    MPI_Init(NULL, NULL);
    char host[128];
    gethostname(host, 128);
    printf("%s\n", host);
    MPI_Finalize();
}