#define HAVE_STRUCT_TIMESPEC
#define NUM_THREADS  8

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



struct pthr_data
{
    int myid;
    double stuff;

};


void* func(void* arg) {}


int main(int argc, char* argv[])
{
    pthread_t thr[NUM_THREADS];
    pthr_data thr_data[NUM_THREADS];



    for (int i = 0; i < NUM_THREADS; i++) {

    }


    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(thr[i], NULL);
    }

}


