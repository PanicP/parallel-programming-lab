#include <stdio.h>
#include <omp.h>

#define f(x) 4.0 / (1.0 + (x * x))

const long long n = 10000000000;

int main(int argc, char *argv[])
{
    long long i;
    double w, x, sum, pi;
    w = 1.0 / n;
    sum = 0.0;

#pragma omp parallel shared(sum, w) private(x, i)
#pragma omp for reduction(+ \
                          : sum)
    for (i = 0; i < n; i++)
    {
        x = w * ((double)i + 0.5);
        sum += f(x);
    }
    printf("sum: %.20f", w * sum);
    return 0;
}