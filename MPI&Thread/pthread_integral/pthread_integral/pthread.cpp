#define _CRT_SECURE_NO_WARNINGS 1
#define HAVE_STRUCT_TIMESPEC
#define BOOST_ALL_NO_LIB
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <boost/thread.hpp>
#include <ctime>

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
	int nthreads = std::thread::hardware_concurrency();
#else
	int nthreads = 10; // whatever fallback value
#endif
	
// задаем параметры для задачи
#define LEFT 0.005
#define RIGHT 5.0
std::vector <double> vec;


using namespace std;



struct pthr_data
{
    int myid;
    double sum = 0.0;
	int NUM_THREADS;
	double eps;
};



double func_1(double x) { return cos(1.0/x); }

double integral_trapezoid_method(double h, double left, double right, double (*func)(double)) {

	//cout << right - left << " " << h << endl;
	long long N = floor((right - left) / h);
	//cout << N << endl;
	double integral_sum = 0;
	double x1, x2;



	for (long long step = 0; step < N; step++) {
		x1 = left + step * h;
		x2 = left + (step + 1) * h;

		integral_sum += 0.5 * (x2 - x1) * (func(x2) + func(x1));

	}
	if (x2 - right != 0) {
		integral_sum += 0.5 * (right - x2) * (func(right) + func(x2));
	}

	return integral_sum;

}

/*Выбор шага интегрирования для обеспечения заданной точности
вычисления интеграла с помощью метода двойного пересчета*/
double precise_integration(double left, double right, double (*func)(double), double eps) {

	double h = 0.000001;

	double integral1 = integral_trapezoid_method(h, left, right, func);

	h /= 2;
	double integral2 = integral_trapezoid_method(h, left, right, func);

	while (abs(integral1 - integral2) >= eps) {

		integral1 = integral2;
		h /= 2;
		integral2 = integral_trapezoid_method(h, left, right, func);

		//cout << left << " " << right << " " << h << endl;
	}

	return integral2;
}

//ЗОЛОТОЕ СЕЧЕНИЕ

void* func(void* arg) {

	
	pthr_data* var = (pthr_data*)arg;
	for (int i = var->myid; i < vec.size() - 1; i+=var->NUM_THREADS) 
	{
		var->sum += precise_integration(vec[i], vec[i+1], func_1, var->eps);
	}

	pthread_exit(NULL);
	return 0;
}

// функция для нахождения нулей данной функции
void find_null(double (*func)(double), double h = 0.000001) {

	vec.push_back(LEFT);


	// некоторые допущения, что RIGHT - LEFT >> h
	for (double step = LEFT; step < RIGHT; step += h) 
	{
		//cout << step;
		if (abs(func(step)) < 0.00001) {
			if (abs(vec.back() - step) > min(0.001, h*100)) {
				vec.push_back(step);
			}
		}
	}
	vec.push_back(RIGHT);

}

int main(int argc, char* argv[])
{
	auto start = clock();

	double total_sum = 0.0;
	int NUM_THREADS;
	double EPS;
	int length_eps;
	char s[20];


	//ввод двух параметров
	if (argc == 1) {
		NUM_THREADS = nthreads;
		EPS = 0.000000000001;
		length_eps = 12;
	}
	else if(argc == 3) {
		NUM_THREADS = atoi(argv[1]);
		EPS = strtod(argv[2], NULL);
		length_eps = strlen(argv[2]);
	}
	else {
		cout << "You should enter 2 parametres: NUM_THREAD and EPS";
		exit(-1);
	}
	


	//cout << NUM_THREADS << " " << EPS;

    pthread_t* thr = new pthread_t[NUM_THREADS];
    pthr_data* thr_data = new pthr_data[NUM_THREADS];



	// ищем нули на нашем изначальном потоке
	find_null(func_1);



    for (int i = 0; i < NUM_THREADS; i++) {

        thr_data[i].myid = i;
		thr_data[i].NUM_THREADS = NUM_THREADS;
		thr_data[i].eps = EPS/NUM_THREADS;
        if (pthread_create(&thr[i], NULL, func, &thr_data[i])) {
            cout << endl <<  "FALL" << endl;
            exit(-1);
        }

    }


    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(thr[i], NULL);
		total_sum += thr_data[i].sum;
    }

	cout << fixed;
	cout.precision(length_eps + 10);
	auto finish = clock();
	cout << "Total time: " << (finish - start)/1000.0  << "s" << endl;
	cout << "NUM_THREADs: " << NUM_THREADS<< endl;
	cout << "Decimal places: " << length_eps << endl;
	cout << EPS << endl;
	cout << total_sum << endl;
	cout << "3.529070700017938" << " - online answer" << endl;

	delete[]thr;
	delete[]thr_data;
}


