#define HAVE_STRUCT_TIMESPEC
#define NUM_THREADS  8
#define EPS 0.0000001

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "windows.h"

using namespace std;


struct stack_MLS 
{

    double A;
    double B;

    double f_A;
    double f_B;

    double s;
};

struct pthr_data
{
    int myid;
    double sum = 0;

};


vector <struct stack_MLS*> vec;
pthread_mutex_t lock_x;

// function for work with vector struct_stack
bool PUT_INTO_STACK(double A, double B, double f_A, double f_B, double s) {
    try {
        vec.push_back(new stack_MLS{ A, B, f_A, f_B, s });
        return 1;
    }
    catch (const char* error_message) {
        cout << error_message << endl;
        return 0;
    }
}
bool DELETE_INTO_STACK() {
    try {
        delete vec[vec.size() - 1];
        vec.pop_back();
        return 1;
    }
    catch (const char* error_message) {
        cout << error_message << endl;
        return 0;
    }
}

stack_MLS* GET_INTO_STACK() {

    try {
        return vec.back();
    }
    catch (const char* error_message) {
        cout << error_message << endl;
        return nullptr;
    }

}


double func_1(double var) {

    return cos(1.0 / var);

}

double integrate(double A, double B, double (*func) (double)) {

    double J = 0;

    double f_A = func(A);
    double f_B = func(B);

    double sAB = (f_A + f_B) * (B - A) / 2;

    double C = 0.0;
    double f_C = 0.0;

    double sAC = 0.0;
    double sCB = 0.0;

    double sACB = 0.0;


    while (1) 
    {
        C = (A + B) / 2;

        f_C = func(C);

        sAC = (f_A + f_C) * (C - A) / 2;
        sCB = (f_C + f_B) * (B - C) / 2;

        sACB = sAC + sCB;

        //cout << A - C << endl;
        //cout << abs(sAB - sACB) - EPS * abs(sACB) << endl;

        if (abs(sAB - sACB) >= EPS)
        {
            PUT_INTO_STACK(A, C, f_A, f_B, sAC);
            A = C;
            f_A = f_C;
            sAB = sCB;
            //cout << vec.size() << endl;
        }
        else 
        {

            J += sACB;

            if (vec.empty()) 
            {
                break;
            }

            stack_MLS* var = GET_INTO_STACK();

            A = var->A;
            B = var->B;
            f_A = var->f_A;
            f_B = var->f_B;
            sAB = var->s;
            //cout << A << endl;

            DELETE_INTO_STACK();
           
        }
        
    }

    return J;
}




void* create(void* arg) {

    pthread_exit(NULL);
    return 0;

}



int main(int argc, char* argv[])
{
    pthread_t* thr = new pthread_t[NUM_THREADS];
    pthr_data* thr_data = new pthr_data[NUM_THREADS];
    pthread_mutex_init(&lock_x, NULL);

    cout << integrate(0.005, 5, func_1);


    for (int i = 0; i < NUM_THREADS; i++) {

        thr_data[i].myid = i;

        if (pthread_create(&thr[i], NULL, create, NULL)) {
            cout << endl <<  "FALL" << endl;
            exit(-1);
        }

    }


    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(thr[i], NULL);
    }




    delete[]thr;
    delete[]thr_data;
}


