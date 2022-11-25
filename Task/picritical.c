#include <stdio.h>
#include <omp.h>

#define f(A) (4.0 / (1.0 + A * A))

const int n = 1000000000;

int main(int argc, char *argv[])
{

    long long i;
    double w, x, sum, pi, partSum;
    w = 1.0 / n;
    sum = 0.0;

    #pragma omp parallel shared(w, sum)  private(x, i)
    #pragma omp for reduction(+:sum)
    
        for (i = 0; i < n; i++)
            {
                x = w * ((double)i + 0.5);
                // #pragma omp critical
                sum = sum + f(x);

            }
        
    
    printf("pi = %.15f\n", w * sum);
    return 0;
}
