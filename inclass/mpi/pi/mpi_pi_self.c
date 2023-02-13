#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define f(x) 4.0 / (1.0 + (x * x))

const long long n = 10000000000;

double calPi(long long start, long long end)
{
    long long i;
    double w, x, sum, pi;
    w = 1.0 / n;
    sum = 0.0;

    for (i = start; i < end; i++)
    {
        x = w * ((double)i + 0.5);
        sum += f(x);
    }
    // printf("sum: %.20f", w * sum);
    return sum;
}

int main(int argc, char *argv[])
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long portion = n / size;
    long long start = rank * portion;
    long long end = start + portion;

    double val = calPi(start, end);

    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            double temp;
            MPI_Recv(&temp, 1, MPI_DOUBLE, i, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            val += temp;
        }
        printf("data: %f", val / n);
    }
    else
    {
        MPI_Send(&val, 1, MPI_DOUBLE, 0, 123, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}