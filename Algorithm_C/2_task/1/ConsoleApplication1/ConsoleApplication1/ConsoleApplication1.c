// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>

int main()
{
    int* arr = (int*)calloc(50, sizeof(int));
    printf("%i", sizeof(*arr));
}
