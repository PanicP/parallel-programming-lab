#include <stdio.h>
#include <omp.h>

#define f(A) (4.0 / (1.0 + A * A))

const int n = 1000000000;

int main(int argc, char *argv[])
{

    int i;
    double w, x, sum, pi, partSum;
#pragma omp parallel shared(w, sum)  private(x, i, partSum)
    {
        w = 1.0 / n;
        sum = 0.0;
        // partSum = 0.0;

        

// #pragma omp parallel
// #pragma share(w, sum)
// #pragma for private(x, i)
// #pragma omp parallel shared(w, sum)

// shared(w, sum)
// private(x, i, partSum)
// {
// #pragma omp for private(x, i, partSum)
        #pragma omp for 
        for (i = 0; i < n; i++)
            {
                x = w * ((double)i + 0.5);

                // sum = sum + f(x);
                partSum = partSum + f(x);
                // printf("%d", i);
            }

            sum += partSum;
        
        printf("pi = %.15f\n", partSum);
        // }
        
    }
    // printf("pi = %.15f\n", w * sum);
    return 0;
}
