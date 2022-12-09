#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define f(A) (4.0/(1.0+A*A))

const long long n = 1000000000;

double calPi(long long start, long long end) {
	long long i;
	double w, x, sum, pi;
	w = 1.0/n;
	sum = 0.0;

	for (i=0; i<n; i++) {
		x = w * ((double)i + 0.5);
		{
			sum = sum + f(x);
		}
	}

	return sum;
}


int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // define portion
    long long portion = n / size;
    long long start = portion * rank;
    long long end = start + portion;

    double part = calPi(start, end);
    // printf("rank = %d\n", rank);
    if(rank == 0) {
        double buf = 0.0;
        // printf("part0 = %lf\n", part);
        for(int i = 1; i < size; i++) {
            // printf("%d %d\n", i, size);
            MPI_Recv(&buf, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            part += buf;
            // printf("buff = %lf\n", buf);
        }
        // printf("pi = %lf %lldf\n", part, n);
        printf("pi = %lf\n", (part/(n*size)));
    } else {
        // printf("part = %lf\n", part);
        MPI_Send(&part, 1, MPI_DOUBLE, 0, 234, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}

// define mpi init
// define mpi com size, com rank
// int portion = n/size
// int start = rank*portion
// int end = start+portion
// double PI cal func (start, end)
// if(rank == 0) collect
// else send