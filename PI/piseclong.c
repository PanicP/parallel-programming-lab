

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#define f(A) (4.0 / (1.0 + A * A))
#define THREADS 8

const long long n = 1000000000;
int portion = n / THREADS;
long long startingPointArray[THREADS];
long long i;
double w, sum, pi;
double allPartResults[THREADS];

void *partPiCalc(void *_index)
{
    long long start = startingPointArray[*((int *)_index)];
    long long end = start + portion;
    double x;
    double partialSum = 0.0;
    for (long longi = start; i < end; i++)
    {
        x = w * ((double)i + 0.5);

        partialSum = partialSum + f(x);
    }
    allPartResults[*((int *)_index)] = partialSum;
    return NULL;
    // sum = sum + partialSum;
    // return 0;
}

int main(int argc, char *argv[])
{

    w = 1.0 / n;
    sum = 0.0;

    for (int i = 0; i < THREADS; i++)
    {
        startingPointArray[i] = i * portion;
    }

    // main func
    // for (i = 0; i < n; i++)
    // {
    //     x = w * ((double)i + 0.5);

    //     sum = sum + f(x);
    // }
    pthread_t threadHandles[THREADS];
    int indices[THREADS]; // to prevent wrong index usage at its loop.
    for (int i = 0; i < THREADS; i++)
    {
        indices[i] = i;
        pthread_create(&threadHandles[i], NULL, partPiCalc, &indices[i]);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(threadHandles[i], NULL);
        sum += allPartResults[i];
    }

    printf("pi = %.15f\n", w * sum);
}
