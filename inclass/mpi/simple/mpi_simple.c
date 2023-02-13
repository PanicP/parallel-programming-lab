#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    // next line is mandatory
    MPI_Init(NULL, NULL);

    char host[128];
    gethostname(host, 128);

    printf("Hello World from %s!!!\n", host);
    // next line is mandatory
    MPI_Finalize();

    return 0;
}
