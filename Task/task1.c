#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{

#pragma omp parallel num_threads(4)
    {
    #pragma omp single
        {
            printf("E = ");
            #pragma omp task
            printf(" m ");
            #pragma omp task
            printf(" c^2 ");
            #pragma omp taskwait
            printf(" Wow");
        }
    } // end of parallel
    return 0;
}