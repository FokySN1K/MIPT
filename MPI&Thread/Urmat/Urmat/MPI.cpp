#include <iostream>
#include "mpi.h"
using namespace std;


int main(int* argc, char** argv)
{

	int numtasks, myrank;


	MPI_Init(argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	cout << "Hello MPI from process = " << myrank << ", total number of processes: " << numtasks << endl;

	MPI_Finalize();



}
