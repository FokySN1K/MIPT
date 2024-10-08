﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//создаем структуру ребер
//так как у нас задача о времени заявок, то отрицательных чисел быть не должно
//будем ориентироваться на это в функции solution
typedef struct edge {
	int begin;
	int end;
}Edge;

void bubble_sort(struct edge* vector, unsigned int NUM);
void print_vector_size(unsigned int NUM);
void print_vector(struct edge* vector, unsigned int NUM);
struct edge* solution(struct edge* vector, unsigned int* NUM);

int main() {

	unsigned int NUM;// число ребер
	scanf("%i", &NUM);

	Edge* vector = (Edge*)calloc(NUM, sizeof(Edge));

	//добавляем ребра
	for (unsigned int i = 0; i < NUM; i++) {
		scanf("%i %i", &vector[i].begin, &vector[i].end);
	}

	bubble_sort(vector, NUM); // сортируем вектор по последнему значению
	vector = solution(vector, &NUM);
	
	print_vector_size(NUM);
	print_vector(vector, NUM);

	free(vector);
}

void bubble_sort(struct edge* vector, unsigned int NUM) {
	for (unsigned int i = 0; i < NUM - 1; i++) {
		for (unsigned int j = (NUM - 1); j > i; j--) {
			if (vector[j - 1].end > vector[j].end) {
				Edge temp = vector[j - 1];
				vector[j - 1] = vector[j];
				vector[j] = temp;
			}
		}
	}
}

//вывод "пригодных" заявок
void print_vector(struct edge* vector, unsigned int NUM) {
	for (unsigned int i = 0; i < NUM; i++) {
		printf("%i %i\n", vector[i].begin, vector[i].end);
	}
}
void print_vector_size(unsigned int NUM) {
	printf("................\n");
	printf("%u\n", NUM);
}

/*учитываем, что время не может быть отрицательным, тем самым
избавляясь от надобности создавать три указателя или же
прибегать к сложной сортировке
*/
struct edge* solution(struct edge* vector, unsigned int* NUM) {
	unsigned int NUM_1 = *NUM;
	int end = vector[0].end;
	for (unsigned int i = 1; i < NUM_1; i++) {
		if (end > vector[i].begin) {
			vector[i].begin = vector[i].end = -1; // выбрасываем ненужные заявки
			(*NUM)--; //кол-во "правильных" заявок
		}
		else {
			end = vector[i].end;
		}
	}
	Edge* vector_1 = (Edge*)calloc(*NUM, sizeof(Edge));
	unsigned NUM_2 = 0;
	for (unsigned int i = 0; i < NUM_1 && NUM_2 != *NUM; i++) { // Два случая: нужные заявки в конце, нужные заявки в начале
		if (vector[i].begin != -1) { // !!! Здесь int-ое значение, так что всё в норме
			vector_1[NUM_2] = vector[i];
			NUM_2++;
		}
	}	
	
	free(vector); // ОБЯЗАТЕЛЬНО ОЧИСТИТЬ, ИНАЧЕ УТЕЧКА ПАМЯТИ
	return vector_1;
}



