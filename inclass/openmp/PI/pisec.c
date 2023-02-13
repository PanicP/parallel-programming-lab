// gcc -O0 pi-sec.c -o pi-sec // use this for debugging
// gcc -O2 pi-sec.c -o pi-sec // use this for float
// gcc -O3 pi-sec.c -o pi-sec
// time ./pi-sec

#include <stdio.h>

#define f(A) (4.0 / (1.0 + A * A))

const int n = 1000000000;

int main(int argc, char *argv[])
{
    int i;
    double w, x, sum, pi;
    w = 1.0 / n;
    sum = 0.0;

    for (i = 0; i < n; i++)
    {
        x = w * ((double)i + 0.5);
        {
            sum = sum + f(x);
        }
    }

    printf("pi = %.15f\n", w * sum);

    return 0;
}
