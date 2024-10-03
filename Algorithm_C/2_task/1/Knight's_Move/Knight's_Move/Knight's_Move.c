#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <dos.h> // для sleep()
#include <assert.h>


// ЭЛЕМЕНТЫ ЗАДАЧИ
int** create_massiv_N_N(int N);
void delete_massiv_N_N(int** massiv, int N);
void massiv_N_N_to_null(int** massiv, int N);

// РЕШЕНИЕ
int sum_of_moves(int** massiv, int N, int x1, int y1); // количество ходов из этой клетки
void solution(int** massiv, int N, int x1, int y1, int* horse); // x1 - строка, y1 - столбец

// ВЫВОД РЕШЕНИЯ
void print_massiv_N_N(int** massiv, int N);
void beatiful_print_moving_from_horse(int** massiv, int N); // просто красивый вывод

// ПРОВЕРКА РЕШЕНИЯ
int checking(int** massiv, int N); // простая проверка суммой
int big_checking(int** massiv, int N, int x, int y); // 0 - решения нет, 1 - решение изначально было получено верно, 2 - решение было исправлено
int testing(int** massiv, int N); // смотрит на все доски, которые нельзя заполнить без big_checking
int last_chance(int ** massiv, int N) {
	int x = 0, y = 0;
	int x1 = 0, y1 = 0;
	for (int x2 = 0; x2 < N; x2++ ) {
		for (int y2 = 0; y2 < N; y2++) {
			if (massiv[x2][y2] == 1) {
				x = x2;
				y = y2;
			}
			else if (massiv[x2][y2] == N*N) {
				x1 = x2;
				y1 = y2;
			}
		}
	}
	if (( abs(x1 - x) == 1 && abs(y1 - y) == 2)  || (abs(x1 - x) == 2 && abs(y1 - y) == 1)) {
		printf("%i %i", x1, y1);
		return 1;
	}
	else {
		return 0;
	}
}







int main() {
	setlocale(LC_ALL, "Rus");

	int size_massiv = 6;
	int** massiv = NULL; // таблица, по которой ходит конь
	int horse = 1;
	int x1 = 4, y1 = 1;

	massiv = create_massiv_N_N(size_massiv);
	
	
	massiv[x1][y1] = 1; // ставим коня
	solution(massiv, size_massiv, x1, y1, &horse);

	//testing(massiv, size_massiv); // простая подстановка чисел
	int number_solution = big_checking(massiv, size_massiv, x1, y1);

	if (number_solution == 1) {
		printf("Еееееее, всё прошло гладко!\n");
		print_massiv_N_N(massiv, size_massiv);
		//beatiful_print_moving_from_horse(massiv, size_massiv);
	}
	else if (number_solution == 2) {
		printf("Было нелегко, но мы нашли ошибку и исправили её!\n");
		print_massiv_N_N(massiv, size_massiv);
		//beatiful_print_moving_from_horse(massiv, size_massiv);
	}
	else {
		printf("Решения нет!\n");
	}

	delete_massiv_N_N(massiv, size_massiv);

}

// ЭЛЕМЕНТЫ ЗАДАЧИ
int** create_massiv_N_N(int N) {
	/*
		Я знаю, что в прошлых задачах ступил, можете не напоминать))
		Лучше писать так!
	*/
	int** massiv = (int**)calloc(N, sizeof(int*));
	for (int i = 0; i < N; i++) {
		massiv[i] = (int*)calloc(N, sizeof(int));
	}
	return massiv;
}
void delete_massiv_N_N(int** massiv, int N) {
	for (int i = 0; i < N; i++) {
		free(massiv[i]);
	}
	free(massiv);
}

// РЕШЕНИЕ
int sum_of_moves(int** massiv, int N, int x1, int y1) {

	int sum = 0;
	int moving[8][2] = { // ходы коня
		{-2, -1}, {-2, 1},
		{2, -1}, {2, 1},
		{-1, -2}, {1, -2},
		{-1, 2}, {1, 2}
	};
	int x3 = 0, y3 = 0;

	for (int i = 0; i < 8; i++) { // движемся по возможным ходам
		x3 = x1 + moving[i][0];
		y3 = y1 + moving[i][1];

		if ((x3 >= 0 && y3 >= 0) && (x3 < N && y3 < N)) { // проверяем возможность хода
			if (massiv[x3][y3] == 0) { // если клетка свободна
				sum += 1;
			}
		}
	}
	return sum;
}
void solution(int** massiv, int N, int x1, int y1, int* horse) {
	int moving[8][2] = {
		{-2, -1}, {-2, 1},// 2 вниз влево-вправо
		{2, -1}, {2, 1},// 2 вверх влево-вправо
		{-1, -2}, {1, -2},// 2 влево вверх-вниз
		{-1, 2}, {1, 2}// 2 вправо вверх-вниз
	};
	int min = 100000;
	int x2 = 0, y2 = 0;
	int x3 = 0, y3 = 0; // выбранные клетки

	int sum = 0;
	int flag = 0; 
	// flag == 0 -> все соседние клетки заняты(ставим коня и забиваем)
	// flag == 1 -> продолжаем ходить 
	
	for (int i = 0; i < 8; i++) { // движемся по возможным ходам
		x2 = x1 + moving[i][0];
		y2 = y1 + moving[i][1];
		if ((x2 >= 0 && y2 >= 0) && (x2 < N && y2 < N)) { // проверяем возможность хода
			if (massiv[x2][y2] == 0) { // если клетка свободна
				sum = sum_of_moves(massiv, N, x2, y2);
				if (sum < min) {
					flag = 1;
					min = sum;
					x3 = x2;
					y3 = y2;
				}
			}
		}
	}



	if (flag) {
		*horse += 1;
		massiv[x3][y3] = *horse;
		solution(massiv, N, x3, y3, horse);
	}

}
void massiv_N_N_to_null(int** massiv, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			massiv[i][j] = 0;
		}
	}
}

// ВЫВОД РЕШЕНИЯ
void print_massiv_N_N(int** massiv, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%3i ", massiv[i][j]);
		}
		printf("\n");
	}
	printf("......................\n");
}
void beatiful_print_moving_from_horse(int** massiv, int N) {
	for (int index = 1; index <= N * N; index++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%c ", (massiv[i][j] == index) ? ('K') : ('-'));
			}
			printf("\n");
		}
		Sleep(200);
		printf("\033[0d\033[2J"); // сдвиг курсора(имитация "стирания" консоли)
	}
}

// ПРОВЕРКА РЕШЕНИЯ
int checking(int** massiv, int N) {
	long long unsigned sum = 0;
	long long unsigned total_sum = 0;
	if (N % 2 == 1) {
		sum = (1 + N * N) / 2 * ( N * N);
	}
	else {
		sum = (N * N) / 2 * (N * N + 1);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			total_sum += massiv[i][j];
		}
	}
	if (sum == total_sum) {
		return 1;
	}
	return 0;
}
int  big_checking(int** massiv, int N, int x, int y) {
	if (checking(massiv, N)) {
		return 1;
	}
	else { // если оказалось, что решение неправильно
		// мы пользуемся правилом Варнсдорфа, поэтому шанс хоть и маленький, но может присутствовать
		int horse = 1;

		// начинаем перебирать все решения
		for (int x1 = 0; x1 < N; x1++) {
			for (int y1 = 0; y1 < N; y1++) {
				horse = 1;
				massiv_N_N_to_null(massiv, N);
				massiv[x1][y1] = 1;
				solution(massiv, N, x1, y1, &horse);
				if (checking(massiv, N) && last_chance(massiv, N)) {

					//print_massiv_N_N(massiv, N);
					int difference = massiv[x][y] - 1;
					//printf("%i\n", difference);
					// изменяем ходы, как будто мы ходили с заданного поля
					for (int x2 = 0; x2 < N; x2++) {
						for (int y2 = 0; y2 < N; y2++) {
							if (massiv[x2][y2] > difference) {
								massiv[x2][y2] -= difference;
							}
							else {
								massiv[x2][y2] = N * N + massiv[x2][y2] - difference;
							}
						}
					}
					// всё изменили - теперь можно жить
					return 2;

				}
			}
		}
		return 0;
	}


}
int testing(int** massiv, int N) {
	int horse = 1;
	for (int x1 = 0; x1 < N; x1++) {
		for (int y1 = 0; y1 < N; y1++) {
			horse = 1;
			massiv_N_N_to_null(massiv, N);
			massiv[x1][y1] = 1;
			solution(massiv, N, x1, y1, &horse);
			if (checking(massiv, N) == 0) {
				printf("%i-%i\n", x1, y1);
			}
		}
	}
	massiv_N_N_to_null(massiv, N);
	return 1;
}
