#include <iostream>
#include "mpi.h"
#include <cmath>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;





double second_derivative_func(double var, double (*func)(double), double h = 0.0001) {
	return (func(var + h) - 2*func(var) + func(var - h))/h/h;
	//return ( - (2 * sin(1 / var) + cos(1 / var) / var) / (var * var * var) );

}

double max_section_for_sec_der_func(double left, double right, double (*func)(double),  double h = 0.00001) {
	int width = (right - left) / h;
	double maximum = -INFINITY;

	//cout << "width " << width << endl;
	double y;
	for (int step = 0; step < width; step++) {

		y = abs(second_derivative_func(left + step*h, func));
		if (maximum < y) {
			maximum = y;
		}

	}
	return maximum;
}


double func_1(double var) {return cos(1.0 / var);}


/* интегрирование методом прямоугольников от left до right функции func с шагом h*/
double integral_rectangle_method(double h, double left, double right, double (*func)(double)) {
	
	double integral_sum = 0;

	for (double var = left; var <= right; var += h) {
		integral_sum += func(var)*h;
	}
	return integral_sum;

}
/* интегрирование методом трапеций от left до right функции func с шагом h*/
double integral_trapezoid_method(double h, double left, double right, double (*func)(double)) {

	//cout << right - left << " " << h << endl;
	int N = (right - left) / h;
	//cout << N << endl;
	double integral_sum = 0;
	double x1, x2;

	for (int step = 0; step < N; step++) {
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
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);


	//cout << h << endl;
	// 
	double h = sqrt(12 * eps / (right - left) / max_section_for_sec_der_func(left, right, func_1));
	
	//cout << h << endl;

	double integral1 = integral_trapezoid_method(h, left, right, func);
	
	h /= 2;
	double integral2 = integral_trapezoid_method(h, left, right, func);

	while (abs(integral1 - integral2) >= eps) {

		integral1 = integral2;
		h /= 2;
		integral2 = integral_trapezoid_method(h, left, right, func);

		cout << left << " " << right << " " << "Myrank " << myrank << " || " <<  integral2 << endl;
	}
	
	return integral2;
}

int main(int argc, char** argv)
{

	MPI_Init(&argc, &argv);


	double eps;
	int numtasks, myrank;
	double integral_sum = 0;;
	double total_integral_sum = 0;

	double start, finish;

	start = MPI_Wtime();

	// задаем пределы интегрирования
	double left = 0.005, right = 5;



	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	



	/*задаем погрешность и точность вывода*/
	if (argc == 1) {

		eps = 0.00000001;

		cout << fixed;
		cout.precision(13);

	}
	else if (argc == 2) {

		eps = strtod(argv[1], NULL);

		cout << fixed;
		cout.precision(strlen(argv[1]) + 5);

	}
	else {
		cout << "Too many arguments" << endl;
		exit(-1);
	}



	vector <double> vec;
	vec.push_back(left);

	double tr;
	do {
		tr = right;
		while (sqrt(12 * eps / (tr - vec.back()) / max_section_for_sec_der_func(vec.back(), tr, func_1, min(0.00001, eps*10000))) < 0.000001) {
			tr = (vec.back() + tr) / 2;
			//cout << tr << endl;

		}
		vec.push_back(tr);
		if (myrank == 0) {
			cout << tr << endl;
		}

	} while (right != tr);


	//for (int i = 0; i < vec.size() - 1; i++) {
	//	cout << vec[i] << " " << vec[i + 1] << " ";
	//	cout << sqrt(12 * eps / (vec[i + 1] - vec[i]) / max_section_for_sec_der_func(vec[i], vec[i + 1], func_1)) << endl;
	//}




	for (int i = myrank; i < vec.size() - 1; i += numtasks)
	{
		integral_sum += precise_integration(vec[i], vec[i + 1], func_1, eps / numtasks);
	}

	//cout << vec.size();

	MPI_Reduce(&integral_sum, &total_integral_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


	if (myrank == 0) {
		cout << endl;
		cout << eps << endl;
		cout << total_integral_sum << endl;
		finish = MPI_Wtime();

		cout << "Total working time: " << finish - start << " sec" << endl;
		cout << endl;
	}
	

	MPI_Finalize();

}
