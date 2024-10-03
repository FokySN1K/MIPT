#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>


int** create_massiv_distance(int** massiv, int* n); // создание двумерного массива
void print_massiv_distance(int** massiv, int n); // печать двумерного квадратного массива
void delete_massiv(int** massiv, int n); // освобождение памяти
int* solution(int** massiv, int n); // 0 вершина(можно заменить в коде)
void route(int** massiv, int* problem, int n);// для 0 вершины
void route_1(int** massiv, int* problem, int n, int vertex); // для n-ой вершины (вершины вводятся не с 0, а с 1)

int main() {
	freopen("c:/Yaroslav/Projects/Algorithm/1_task/5/EXAMPLE.txt", "r", stdin);
	int** massiv_distance = NULL;
	int n;

	int* problem = NULL;// массив, по которому мы сможем установить в какие ребра следует идти
	massiv_distance = create_massiv_distance(massiv_distance, &n);

	problem = solution(massiv_distance, n);

	/*for (int i = 0; i < n; i++) {
		printf("%i ", problem[i] + 1);
	}*/
	route(massiv_distance, problem, n);
	//route_1(massiv_distance, problem, n, 1);

	delete_massiv(massiv_distance, n);
	free(problem);
}


int** create_massiv_distance(int** massiv, int* n) {
	scanf("%i", n);
	massiv = (int**)calloc(*n, sizeof(int*));
	for (int i = 0; i < *n; i++) {
		massiv[i] = (int*)calloc(*n, sizeof(int));
	}
	for (int i = 0; i < *n; i++) {
		for (int j = 0; j < *n; j++) {
			scanf("%i", &massiv[i][j]);
		}
	}
	return massiv;
}
void print_massiv_distance(int** massiv, int n) {
	printf("..........\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%i ", massiv[i][j]);
		}
		printf("\n");
	}
}
void delete_massiv(int** massiv, int n) {
	for (int i = 0; i < n; i++) {
		free(massiv[i]);
	}
	free(massiv);
}
int* solution(int** massiv, int n) {
	int* vertics = (int*)calloc(n, sizeof(int));// 0 - невыбранные вершины, 1 - выбранные
	int* problem = (int*)calloc(n, sizeof(int));// вершины, из которых быстрее всего добираться
	int size = 1;
	int* arr = (int*)calloc(n, sizeof(int)); // массив с ребрами, из которых будем выбирать
	int vertic = 0;//!!!!!!!! вершина, от которой мы всё ищем
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Надо потребовать scanf от пользователя в  main, а потом передать в route_1
	vertics[vertic] = 1;
	for (int i = 0; i < n; i++) {
		arr[i] = massiv[vertic][i];
		problem[i] = vertic;
	}
	while (size != n) {
		int min = 9999999;// будем считать, что это бесконечность
		int k;
		for (int i = 0; i < n; i++) {
			if (vertics[i] == 1) {
				continue;
			}
			if (min > arr[i]) {
				min = arr[i];
				k = i; // выбрали вершину
			}
		}
		vertics[k] = 1; // эта вершина выбрана
		//смотрим, изменится ли наш массив рёбер, если будем "шагать" из выбранной вершины
		for (int i = 0; i < n; i++) {
			if (vertics[i] == 1) { // сама себя вершина не смотрит
				continue;
			}
			if (arr[i] > min + massiv[k][i]) {
				arr[i] = min + massiv[k][i];
				problem[i] = k;
			}
		}
		size++;
	}
	free(vertics);
	free(arr);
	return problem;
}
void route(int** massiv, int* problem, int n) { // печатает с 1, принимая, что 1 - начало
	for (int i = 1; i < n; i++) {
		int w = i;
		int sum = 0;// суммарная длина
		if (problem[i] == 0) {
			sum = massiv[0][i];
			printf("%i: %i-1\n", i + 1, i + 1);			
		}
		else {
			printf("%i: %i-", i + 1, i + 1);
			while (problem[w] != 0) {
				sum += massiv[problem[w]][w];
				printf("%i-", problem[w] + 1);
				w = problem[w];
			}
			sum += massiv[0][w];
			printf("1\n");
		}
		printf("Total distance: %i\n", sum);
		printf("...............\n");
	}
}
void route_1(int** massiv, int* problem, int n, int vertex) { // печатает с 1, принимая, что 1 - начало
	vertex -= 1;
	for (int i = 0; i < n; i++) {
		if (i == vertex) {
			continue;
		}
		int w = i;
		int sum = 0;// суммарная длина
		if (problem[i] == vertex) {
			sum = massiv[vertex][i];
			printf("%i: %i-%i\n", i + 1, i + 1, vertex + 1);
		}
		else {
			printf("%i: %i-", i + 1, i + 1);
			while (problem[w] != vertex) {
				sum += massiv[problem[w]][w];
				printf("%i-", problem[w] + 1);
				w = problem[w];
			}
			sum += massiv[vertex][w];
			printf("%i\n", vertex + 1);
		}
		printf("Total distance: %i\n", sum);
		printf("...............\n");
	}
}