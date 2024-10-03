#define HAVE_STRUCT_TIMESPEC

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int global = 0;
pthread_t* thr;

struct pthr_data
{
    int myid;
    double stuff;

};


void* func(void* arg) {


    pthr_data* struct_thr = (pthr_data*)arg;

    if (struct_thr->myid == 0) {

        cout << "Myid " << struct_thr->myid << " global: " << global << endl;
        global += 1;
    }
    else {
        pthread_join(thr[struct_thr->myid - 1], NULL);

        cout << "Myid " << struct_thr->myid << " global: " << global << endl;
        global += 1;
    }

    pthread_exit(NULL);
    return 0;

}


int main(int argc, char* argv[])
{
    int NUM_THREADS;

    if (argc == 1) {
        NUM_THREADS = 8;
    }
    else if (argc == 2) {
        NUM_THREADS = atoi(argv[1]);
    }
    else {
        cout << "Too many arguments" << endl;
        exit(-1);
    }


    thr = new pthread_t[NUM_THREADS];
    pthr_data* thr_data = new pthr_data[NUM_THREADS];



    for (int i = 0; i < NUM_THREADS; i++) {

        thr_data[i].myid = i;

        if (pthread_create(&thr[i], NULL, func, &thr_data[i])) {
            cout << endl <<  "FALL" << endl;
            exit(-1);
        }

    }



    pthread_join(thr[NUM_THREADS - 1], NULL);

    delete[]thr;
    delete[]thr_data;


}



