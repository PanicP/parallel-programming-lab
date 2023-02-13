#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KB 1024
#define MB (KB*1024)
#define GB (MB*1024)

int main(int argc, char** argv) {
	MPI_Init(0,0);

	int rank;
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    // char *data;
    // int bytes = (1024*1024*1024);
    // data = (char *) malloc(bytes);
    // for(int i=0;i<bytes;i++){
    //     data[i] = (char) rand();
    //     // printf("%c",data[i]);
    // }


	// float data = 0.0f ;
	if(rank == 0) {

        char* buffer = 0;
        for (int s = 128; s < (100*MB); s*=2) {
            buffer = malloc(s);
        

		    double start = MPI_Wtime();
		    for (int i = 0; i < 1000; i++) {
			    // PING
		    	MPI_Ssend(buffer, 1, MPI_CHAR, 1, 17, MPI_COMM_WORLD);	
		    	//PONG
		    	// MPI_Recv(buffer,  1, MPI_CHAR, 1, 23, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		    }
		double end= MPI_Wtime();

		printf("%d : %0.15lf : \n", s, ((end-start)/25.0));
        free(buffer);
        }
	} else if(rank == 1) {
	    char* buffer = 0;
        for (int s = 128; s < 100*MB; s*=2) {
            buffer = malloc(s);
		for (int i = 0; i < 1000; i++) {
			// PING
			MPI_Recv(buffer,  1, MPI_CHAR, 0, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			// PONG
			// MPI_Ssend(buffer, 1, MPI_CHAR, 0, 23, MPI_COMM_WORLD);	
		}
        free(buffer);
        }
	} else {

	}

	MPI_Finalize();
	return 0;
}
