#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

void print_mass(const int *p_array, int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", p_array[i]);
	printf("\n");
}

enum FIND_OPT
{
	FO_MIN = 0,
	FO_MAX
};

// ----------------
// find
// 
// найти минимальное или максимальное значение в целочисленном массиве
// ----------------
int find(enum FIND_OPT option, const int *p_array, int size)
{
	int value;
	switch (option) {
	case FO_MIN:
		value = INT_MAX;
		for (int i = 0; i < size; i++)
			if (p_array[i] < value)
				value = p_array[i];
		break;

	case FO_MAX:
		value = INT_MIN;
		for (int i = 0; i < size; i++)
			if (p_array[i] > value)
				value = p_array[i];

		break;
	}
	return value;
}

void remove_from_array(int *p_array, int *p_size, int index)
{
	for (int i = index; i < (*p_size) - 1; i++)
		p_array[i] = p_array[i + 1];

	(*p_size)--;
}

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
	srand((unsigned int)time(0));

	int i;
	int mass[20];
	int size = sizeof(mass) / sizeof(mass[0]);
	for (i = 0; i < size; i++)
		mass[i] = (rand() % size) + i;

	printf("Source array: ");
	print_mass(mass, size);
	printf("\n\n");
	
	int maximum = find(FO_MAX, mass, size);
	int half_max = maximum / 2;
	printf("Max: %d  Half: %d\n", maximum, half_max);
	for (i = 0; i < size; i++) {
		if (mass[i] > half_max) {
			remove_from_array(mass, &size, i);
			print_mass(mass, size);
			i = 0;
		}
	}
	printf("Result: ");
	print_mass(mass, size);

	printf("\n\n");
	int minimum = find(FO_MIN, mass, size);
	printf("Min: %d\n", minimum);
	for (i = 0; i < size; i++) {
		if (mass[i] == minimum) {
			insert_from(mass, &size, sizeof(mass) / sizeof(mass[0]), i + 1, maximum);
		}
	}
	print_mass(mass, size);

	int j = 0;
	int temp;
	printf("\n\n");
	for (i = 0; i < size; i++) {
		if (!(mass[i] % 5)) {
			temp = mass[j];
			mass[j] = mass[i];
			mass[i] = temp;
			j++;
		}
	}
	print_mass(mass, size);
	return 0;
}