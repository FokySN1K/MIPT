#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
int** create_massiv_distance(int** massiv, int* n); // создание двумерного массива
void print_massiv_distance(int** massiv, int n); // печать двумерного квадратного массива
void delete_massiv(int** massiv, int n); // освобождение памяти
int* solution(int** massiv, int n);
void dfs(int** massiv, int size, int* paint, int vertex, int* problem, int* len);//раскраска

int main(){
	setlocale(LC_ALL, "Rus");
	freopen("c:/Yaroslav//Projects/Algorithm/1_task/6/EXAMPLE.txt", "r", stdin);

	int** massiv_distance = NULL;
	int n;
	int* problem = NULL;

	massiv_distance = create_massiv_distance(massiv_distance, &n);
	problem = solution(massiv_distance, n);

	for (int i = 0; i < n; i++) {
		printf("%i ", problem[i] + 1);
	}

	/*print_massiv_distance(massiv_distance, n);*/
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
	int* problem = (int*)calloc(n, sizeof(int));
	int* paint = (int*)calloc(n, sizeof(int));// 0 - белый, 1 - серый, 2 - черный
	int len = n - 1;
	for (int i = 0; i < n; i++) {
		if (paint[i] == 0) {
			dfs(massiv, n, paint, i, problem, &len);
		}
		else if (paint[i] == 1) {
			printf("Обнаружена ошибка:\n");
			assert(0);
		}
	}
	free(paint);
	return problem;
}
void dfs(int** massiv, int size, int* paint, int vertex, int* problem, int* len) {
	if (paint[vertex] == 0) {
		paint[vertex] = 1;
		for (int i = 0; i < size; i++) {
			if (massiv[vertex][i] == 1) {
				dfs(massiv, size, paint, i, problem, len);
			}
		}
		problem[(*len)--] = vertex;
		paint[vertex] = 2;

	}
	else if (paint[vertex] == 1) {
		printf("Обнаружена ошибка:\n");
		printf("Граф цикличен:\n");
		assert(0);
	}
}