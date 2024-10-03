#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int** create_massiv_distance(int** massiv, int* n); // создание двумерного массива
void print_massiv_distance(int** massiv, int n); // печать двумерного квадратного массива
void delete_massiv(int** massiv, int n); // освобождение памяти
void print_edge(int** massiv, int n); // печать списка ребер
void solution(int** massiv_distance, int** massiv, int n);


int main() {
	freopen("C:/Yaroslav/Projects/Algorithm/1_task/3/example.txt", "r", stdin);
	int** massiv_distance = NULL;
	int n;
	int** massiv = NULL;// массив, который нам покажет нужные соединения

	/// инициализируем массивы
	massiv_distance = create_massiv_distance(massiv_distance, &n); // Почему надо передавать так?
	massiv = (int**)calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++) {
		massiv[i] = (int*)calloc(n, sizeof(int));
	}
	/////////
	solution(massiv_distance, massiv, n);
	print_edge(massiv, n);
	delete_massiv(massiv_distance, n);
	delete_massiv(massiv, n);
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
void print_edge(int** massiv, int n) {
	printf("..............\n");
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (massiv[i][j] != 0) {
				printf("%i - %i: %i\n", i, j, massiv[i][j]);
			}
		}
	}
}
void delete_massiv(int** massiv, int n) {
	for (int i = 0; i < n; i++) {
		free(massiv[i]);
	}
	free(massiv);
}
void solution(int** massiv_distance, int** massiv, int n) {
	int* set = (int*)calloc(n, sizeof(int));// множество всех вершин 1 - выбранные, 0 - невыбранные
	set[0] = 1; // выбрали случайную вершину
	int set_size = 1;// кол-во выбранных вершин
	while (set_size != n) {
		int min = 9999999;// бесконечность
		int k_i;// номер вершины
		int k_j;
		for (int i = 0; i < n; i++) { // уже выбранные вершины
			if (set[i] == 0) {
				continue;
			}
			for (int j = 0; j < n; j++) {// ещё невыбранные вершины
				if (set[j] == 1) {
					continue;
				}
				if (min > massiv_distance[i][j] && massiv_distance[i][j] != 0) {
					min = massiv_distance[i][j];
					k_i = i;
					k_j = j;
				}
			}
		}
		set[k_j] = 1;
		massiv[k_i][k_j] = massiv_distance[k_i][k_j]; // может быть так, что k_i > k_j
		massiv[k_j][k_i] = massiv_distance[k_i][k_j]; // а печать ребер настроена для неориентированного графа
		set_size++;
	}
	free(set);
}