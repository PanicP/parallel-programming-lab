// gcc FirstProg.c -o FirstProg
// ./FirstProg

#include <stdio.h>
#include <pthread.h>
#define SIZE 4096
#define THREADS 16

typedef struct {
    int* arr;
    int start;
    int end;
} Data;

void* threadFnc(void* _d) {
    Data* d = (Data*)_d;
    for (int i = d->start; i < d->end; i++) {
        d->arr[i] = d->arr[i]+1;
    }
    return NULL;
}

int main(int argc, char** argv) {
    int arr[SIZE];

    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }
    // Parallelization starting
    pthread_t thread[THREADS];
    Data ds[THREADS];
    int load = SIZE / THREADS;
    for(int i = 0; i < THREADS; i++) {
        ds[i].arr = arr;
        ds[i].start = i * load;
        ds[i].end = (i+1) * load;

        if(i == THREADS - 1) {
            ds[i].end = SIZE;
        }
        pthread_create(&thread[i], NULL, threadFnc, &ds[i]);
    }

    for(int i = 0; i < THREADS; i++) {
        pthread_join(thread[i], NULL);
    }
    // threadFnc(arr);
    // Parallelization ending

    printf("%d %d %d ... %d\n", arr[0], arr[1], arr[2], arr[SIZE - 1]);

    return 0;
}


