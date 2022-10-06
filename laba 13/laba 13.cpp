#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <locale>
#include <conio.h>
#include <time.h>

void fill_array(int *p_dest, int destlen, int start, int step)
{
	for (int i = 0; i < destlen; i++) {
		p_dest[i] = start;
		start += step;
	}
}

int FindMin(int *Arr, int Size)
{
	int  min = Arr[0]; 
	for (int i = 1; i < Size; i++) 
		if (Arr[i] < min) 
			min = Arr[i]; 
	return min; 
}

int FindMax(int *Arr, int Size)
{
	int  max = Arr[0]; 
	for (int i = 1; i < Size; i++) 
		if (Arr[i] > max) 
			max = Arr[i]; 
	return max; 
}

void View_Array(int*Array1, int count) {   //print mass
	for (int i = 0; i < count; i++)
		printf("%d ", Array1[i]);
}

void Fill_Array_Rand(int*Array1,int size) {
	for (int i = 0; i < size; i++)
	{
		 Array1[i] = rand() % 10;
	}
}

float name(int neme)
{
	int count = 0;
	int nam = 0;
	while (neme) {
		nam += neme % 10;
		neme /= 10;
		count++;
	}
	return (float)nam / (float)count;
}

void mass_copy(const int*src, int*dst, int saze) {
	for (int i = 0; i < saze; i++)
	{
		dst[i] = name(src[i]);
	}
}


void FillArrayStep(int *p_dest, int destlen, int start, int step)//пункт 3
{
	for (int i = 0; i < destlen; i++) {
		p_dest[i] = start;
		start += step;
	}
}

int main()
{
	printf("Нмт-1, Шабалин Родион\n");
	printf("Лабораторная работа №13,вариант №10\n\n");
	int* Array1 = 0; // Указатель на первый массив
	int* Array2 = 0; // Указатель на второй массив
	int x1, k, m, w;
	int Size1 = 10, Size2 = 10; // размеры массивов
	char key;
	srand(clock()); // Для генератора случайных чисел
	setlocale(0, "Russian");
	Array1 = new int[Size1]; // Выделяем память под массив
	Array2 = new int[Size2]; // Выделяем память под массив
	for (;;) // Бесконечный цикл
	{
		printf("\n Выберите пункт меню:\n");
		printf(" 0 – Выйти из программы!\n");
		printf(" 1 – Изменить размеры массивов!\n");//готово
		printf(" 2 – Задать массив 1 случайными числами!\n");//готово
		printf(" 3 – Задать массив 1 числамиот х1 с шагом к!\n");//готово
		printf(" 4 – Вывести массив 1\n");//готово
		printf(" 5 – Вывести массив 2\n");//готово
		printf(" 6 – Найти мин и макс значения массивов\n");//готово
		printf(" 7 – Копир-ть из 1-го масс. во 2-ой числа по функции из 10 лаб\n");//готово
		printf(" Спасибо, что воспользовались ilya_ilichev_program!!!\n");
		key = _getch();
		switch (key)
		{
		case '0':
			delete[] Array1;
			delete[] Array2;
			return 0; // Завершение программы
		case '1':
			delete[] Array1;
			delete[] Array2;
			printf("Размер массивов = ");
			scanf("%d", &Size1);
			Size2 = Size1;
			Array1 = new int[Size1]; // Выделяем память под массив
			Array2 = new int[Size2]; // Выделяем память под массив
			printf("Массивы созданы!\n");
			break;
		case '2':
			Fill_Array_Rand(Array1, Size1);// Заполнение случ.числами
			printf("Массив заполнен:\n");
			View_Array(Array1, Size1);
			break;
		case '3':
			printf("Заполнить от: ");
			scanf("%d", &x1);
			printf("с шагом: ");
			scanf("%d", &k);
			FillArrayStep(Array1, Size1, x1, k);
			printf("Массивы заполнены\n");
			break;
		case '4':
			printf("Массив 1:\n");
			View_Array(Array1, Size1);
			break;
		case '5':
			printf("Массив 2:\n");
			View_Array(Array2, Size2);
			break;
		case '6':
			m = FindMin(Array1, Size1);
			printf("Мин. число массива 1: %d\n", m);
			w = FindMax(Array1, Size1);
			printf("max. число массива 1: %d\n", w);
			m = FindMin(Array2, Size2);
			printf("Мин. число массива 2: %d\n", m);
			w = FindMax(Array1, Size1);
			printf("Мax. число массива 2: %d\n", w);
			break;
		case '7':
			mass_copy(Array1, Array2, Size1); // копируем четные
			printf("Массив 1:\n");
			View_Array(Array1, Size1);
			printf("Массив 2:\n");
			View_Array(Array2, Size2);
		    break;

		}
    } // Конец цикла for
}