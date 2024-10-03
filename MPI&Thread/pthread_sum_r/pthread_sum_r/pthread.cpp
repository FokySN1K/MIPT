#define HAVE_STRUCT_TIMESPEC
#define NUM_THREADS  8

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;



long long num_step = 20000;


struct my_pthread_data {
    int id;
    double sum = 0;
};

void* calculate(void* arg) {
    my_pthread_data *var =  (my_pthread_data*) arg;
    //cout << var->id ;

    for (int i = var->id + 1; i <= num_step; i += NUM_THREADS) {
        var->sum += 1.0 / i;
        /*if (var->id == 0) {
            cout << var->sum << " " << i << endl;
        }*/
    }


    pthread_exit(NULL);
    return 0;

}

int main(int argc, char** argv) { // основная ф-й принимает аргумент

    pthread_t thr[NUM_THREADS]; // готовим буфер для создания N потоков
    my_pthread_data thr_arr[NUM_THREADS];

    double total_sum = 0;

    if (argc == 1) {
        
    }
    else if (argc == 2) {
        num_step = stoi(argv[1]);
    }
    else {
        exit(-1);
    }

    for (int i = 0; i < NUM_THREADS; i++) 
    {
        thr_arr[i].id = i;
        
        pthread_create(&thr[i], NULL, calculate, &thr_arr[i]);
    
    }
    



    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(thr[i], NULL);
        total_sum += thr_arr[i].sum;
    }
    cout << total_sum;

}
