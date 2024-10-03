#include <iostream>
#include <fstream>
#include "mpi.h"
#define M_PI           3.14159265358979323846  /* pi */
using namespace std;



double func_border_x(double x) { return cos(M_PI * x); }

double func_border_t(double t) { return exp(-t); }


double func(double t, double x) { return t + x; }


void print(double** arr, int size) {

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void print_arr_to_file(double** arr, int size) {
	std::ofstream out("F:/exp.txt"); //откроем файл для вывод
	std::streambuf* coutbuf = std::cout.rdbuf(); //запомним старый буфер
	std::cout.rdbuf(out.rdbuf()); //и теперь все будет в файл out.txt!

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	std::cout.rdbuf(coutbuf);
}

void print_values_to_file(double t_L, double t_R, double x_L, double x_R ) {
	std::ofstream out("F:/exp_values.txt"); //откроем файл для вывод
	std::streambuf* coutbuf = std::cout.rdbuf(); //запомним старый буфер
	std::cout.rdbuf(out.rdbuf()); //и теперь все будет в файл out.txt!
	cout << t_L << " " << t_R << endl;
	cout << x_L << " " << x_R << endl;
	std::cout.rdbuf(coutbuf);



}
void clear(double** arr, int size) {

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {
			arr[i][j] = 0.0;
		}
	}
}

int main(int argc, char** argv)
{

	cout << fixed;
	cout.precision(6);

	MPI_Init(&argc, &argv);

	int numtasks, myrank;





	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);




	int number_of_partitions = 100000;

	double t_L = 0.0, t_R = 5.0 ;
	double x_L = 0.0, x_R = 5.0;
	
	print_values_to_file(t_L, t_R, x_L, x_R);


	double step_t = (t_R - t_L) / number_of_partitions;
	double step_x = (x_R - x_L) / number_of_partitions;


	number_of_partitions++;
	double** arr = new double* [number_of_partitions];

	for (int i = 0; i < number_of_partitions; i++) {
		arr[i] = new double[number_of_partitions];

	}

	clear(arr, number_of_partitions);

	// заполняю массив изначальными данными
	for (int x = 0; x < number_of_partitions; x++) {
		arr[0][x] = func_border_x(x_L + step_x * x);
	}

	for (int t = 0; t < number_of_partitions; t++) {
		arr[t][0] = func_border_t(t_L + step_t * t);
	}

	// здесь MPI

	//print(arr, number_of_partitions);


	double* reduce_arr = new double[number_of_partitions];
	for (int i = 0; i < number_of_partitions; i++) {
		reduce_arr[i] = 0.0;
	}

	double start = MPI_Wtime(), finish;

	if (numtasks == 1) {

		for (int t = 0; t < number_of_partitions - 1; t++) {

			for (int x = 0; x < number_of_partitions - 1; x++) {
				arr[t + 1][x + 1] = step_t * func(step_t * t, step_x * (x + 1)) - step_t / step_x * (arr[t][x + 1] - arr[t][x]) + arr[t][x + 1];
			}
		}
	
	}
	else {
		for (int t = 0; t < number_of_partitions - 1; t++) {




			MPI_Bcast(arr[t], number_of_partitions, MPI_DOUBLE, 0, MPI_COMM_WORLD);



			// считаем следующий слой
			for (int x = myrank; x < number_of_partitions - 1; x+=numtasks) {
				reduce_arr[x + 1] = step_t * func(step_t * t, step_t * (x + 1)) - step_t / step_x * (arr[t][x + 1] - arr[t][x]) + arr[t][x + 1];
			}
			if (myrank == 0) {
				reduce_arr[0] = arr[t + 1][0];
			}
			

			MPI_Reduce(reduce_arr, arr[t + 1], number_of_partitions, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


		}
	}
	


	if (myrank == 0) {
		finish = MPI_Wtime();
		cout << "Operating time:  " << finish - start << endl;
		//print_arr_to_file(arr, number_of_partitions);
		//print(arr, number_of_partitions);
	}

	for (int i = 0; i < number_of_partitions; i++) {
		delete []arr[i];
	}

	delete[]reduce_arr;

	MPI_Finalize();



}
