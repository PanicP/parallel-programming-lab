#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define f(A) (4.0 / (1.0 + A * A))

const long long n = 10000000000;

double piCalcFunc(long long start, long long end)
{
    printf("%lld %lld\n", start, end);
    long long i;
    double w, x, sum, pi;
    w = 1.0 / n;
    sum = 0.0;

    for (i = start; i < end; i++)
    {
        x = w * ((double)i + 0.5);
        {
            sum = sum + f(x);
        }
    }
    return sum;
}

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long portion = n / size;
    long long start = portion * rank;
    long long end = start + portion;

    double part = piCalcFunc(start, end);
    // printf("part: %lf\n", (part / n));

    if (rank == 0)
    {
        double buf = 0.0;
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&buf, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            part += buf;
        }
        printf("total sum: %lf\n", (part / n));
    }
    else
    {
        MPI_Send(&part, 1, MPI_DOUBLE, 0, 234, MPI_COMM_WORLD);
    }
    MPI_Finalize();

    return 0;
}

// #include <stdio.h>

// #define f(A) (4.0 / (1.0 + A * A))

// const long long n = 10000000000;

// int main(int argc, char *argv[])
// {
//     long long i;
//     double w, x, sum, pi;
//     w = 1.0 / n;
//     sum = 0.0;

//     for (i = 0; i < n; i++)
//     {
//         x = w * ((double)i + 0.5);
//         {
//             sum = sum + f(x);
//         }
//     }

//     printf("pi = %.15f\n", w * sum);

//     return 0;
// }
