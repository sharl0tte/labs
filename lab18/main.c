#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

//вывод массива в консоль
void print_mass(const int *p_array, int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", p_array[i]);
	printf("\n");
}

//опции поиска минимального и максимального числа (у меня это реализовано в одной функции)
enum FIND_OPT
{
	FO_MIN = 0, //опция поиска минимального числа
	FO_MAX //опция поиска максимального числа
};

// ----------------
// find
// 
// найти минимальное или максимальное значение в целочисленном массиве
// функция была сделана для того, чтобы не проводить поиск минимального и максимального числа в двух разных функциях
// ----------------
int find(enum FIND_OPT option, const int *p_array, int size)
{
	int value;
	switch (option) {
	case FO_MIN: //если ищем минимальное число
		value = INT_MAX; //изначально, минимальное число является максимально возможным
		for (int i = 0; i < size; i++)
			if (p_array[i] < value)
				value = p_array[i];
		break;

	case FO_MAX: //если ищем максимальное число
		value = INT_MIN; //изначально, максимальное число является минимально возможным
		for (int i = 0; i < size; i++)
			if (p_array[i] > value)
				value = p_array[i];

		break;
	}
	return value; //возвратим из функции найденное значение
}

//удалим элемент из массива с указанного индекса
void remove_from_array(int *p_array, int *p_size, int index)
{
	for (int i = index; i < (*p_size) - 1; i++)
		p_array[i] = p_array[i + 1];

	(*p_size)--;
}

//вставим элемент в массив с указанного индекса
void insert_from(int *p_array, int *p_size, int max_size, int index, int value)
{
	(*p_size)++;
	if (*p_size >= max_size)
		*p_size = max_size;

	for (int i = (*p_size); i >= index; i--)
		p_array[i + 1] = p_array[i];

	p_array[index] = value;
}

int main()
{
	srand((unsigned int)time(0)); //установим seed рандома текущим временем, чтобы рандом не повторялся при запуске программы

	int i;
	int mass[20];

	//сгененрируем рандомные числа в массиве
	int size = sizeof(mass) / sizeof(mass[0]);
	for (i = 0; i < size; i++)
		mass[i] = (rand() % size) + i;

	//выведем массив
	printf("Source array: ");
	print_mass(mass, size);
	printf("\n\n");

	int maximum = find(FO_MAX, mass, size); //найдем максимальное число в массиве
	int half_max = maximum / 2; //найдем половину от максимального числа
	printf("Max: %d  Half: %d\n", maximum, half_max);

	// удалить все числа из массива, превышающие половину от максимального числа
	for (i = 0; i < size; i++) {
		if (mass[i] > half_max) {
			remove_from_array(mass, &size, i);
			print_mass(mass, size); //выведем все числа из массива, которые у нас остались после удаления
			i = 0; //сбрасываем позицию чтобы всегда начинать поиск сначала
		}
	}
	printf("Result: ");
	print_mass(mass, size); //выведем итоговый массив

	printf("\n\n");
	int minimum = find(FO_MIN, mass, size); //теперь найдем минимальное число
	printf("Min: %d\n", minimum);

	//вставим максимальное число после минимального
	for (i = 0; i < size; i++) {
		if (mass[i] == minimum) {
			insert_from(mass, &size, sizeof(mass) / sizeof(mass[0]), i + 1, maximum);
		}
	}
	print_mass(mass, size); //распечатаем массив

	int j = 0;
	int temp;
	printf("\n\n");

	//переставим в начало массива все числа кратные 5
	for (i = 0; i < size; i++) {
		if (!(mass[i] % 5)) {
			temp = mass[j];
			mass[j] = mass[i];
			mass[i] = temp;
			j++;
		}
	}
	print_mass(mass, size); //выведем полученный массив
	return 0;
}