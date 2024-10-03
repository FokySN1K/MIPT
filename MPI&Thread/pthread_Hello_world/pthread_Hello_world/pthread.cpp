#define HAVE_STRUCT_TIMESPEC
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS  8

using namespace std;

typedef struct _thread_data_t
{
    int tid;
    double stuff;

}thread_data_t;


void* Hello(void* arg) {
    
        thread_data_t* data = (thread_data_t*)arg;
        printf("hello from %d\n", data->tid);
        pthread_exit(NULL);
        return 0;
    }

int main(int argc, char* argv[])
{
    pthread_t thr[NUM_THREADS];
    thread_data_t thr_data[NUM_THREADS];


    int i, rc;

    for (i = 0; i < NUM_THREADS; ++i) {
        thr_data[i].tid = i;

        if ((rc = pthread_create(&thr[i], NULL, Hello, &thr_data[i]))) {
            fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            return EXIT_FAILURE;
        }
    }


    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
    }

    return EXIT_SUCCESS;
}


