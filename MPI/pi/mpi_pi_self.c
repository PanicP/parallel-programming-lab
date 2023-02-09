#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define f(x) 4.0 / (1.0 + (x * x))

const long long n = 10000000000;

double calPi(long long start, long long end)
{
    printf("%lld %lld\n", start, end);
    long long i;
    double w, x, sum, pi;
    w = 1.0 / n;
    sum = 0.0;

    for (i = start; i < end; i++)
    {
        x = w * ((double)i + 0.5);
        sum += f(x);
    }

    return sum;
}

int main(int argc, char *argv[])
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long portion = n / size;
    long long start = portion * rank;
    long long end = portion + start;

    double calPart = calPi(start, end);
    printf("part: %lf\n", (calPart / n));
    if (rank == 0)
    {
        double recv;
        for (int j = 1; j < size; j++)
        {
            MPI_Recv(&recv, 1, MPI_DOUBLE, j, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            calPart += recv;
        }
        printf("%.15f", calPart / n);
    }
    else
    {
        MPI_Send(&calPart, 1, MPI_DOUBLE, 0, 123, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}