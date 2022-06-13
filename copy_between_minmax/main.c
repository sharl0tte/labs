#include <Windows.h>

#include <stdio.h>
#include <time.h>
#include <limits.h>

#define CNT(x) (sizeof(x) / sizeof(x[0]))

#define ARRAY_SIZE 5

int main()
{
	int i;
	int srcarr[ARRAY_SIZE];
	srand((unsigned int)time(0));
	printf("Source array: ");
	for (i = 0; i < CNT(srcarr); i++) {
		srcarr[i] = rand() % 100;
		printf("%d ", srcarr[i]);
	}
	printf("\n");

	// [*][ ]  0 - min         1 - max
	// [ ][*]  0 - значение    1 - индекс
	int minmax[2][2] = {
		{ INT_MAX, 0 },
		{ INT_MIN, 0 }
	};

	for (i = 0; i < CNT(srcarr); i++) {
		if (srcarr[i] < minmax[0][0]) {
			minmax[0][0] = srcarr[i];
			minmax[0][1] = i;
		}

		if (srcarr[i] > minmax[1][0]) {
			minmax[1][0] = srcarr[i];
			minmax[1][1] = i;
		}
	}

	printf("Min %d Index: %d\n", minmax[0][0], minmax[0][1]);
	printf("Max %d Index: %d\n", minmax[1][0], minmax[1][1]);

	int beginidx = min(minmax[0][1], minmax[1][1]);
	int endidx = max(minmax[0][1], minmax[1][1]);
	printf("beg %d   end %d\n", beginidx, endidx);
	int size = (endidx - beginidx) - 1;
	if (size <= 0) {
		printf("No elements between!\n");
		return 0;
	}

	//copy
	int arr2[ARRAY_SIZE];
	int j = beginidx + 1;
	for (i = 0; i < CNT(srcarr) && j < endidx; i++, j++)
		arr2[i] = srcarr[j];

	printf("Elements between %d and %d: ", minmax[0][0], minmax[1][0]);
	for (i = 0; i < size; i++)
		printf("%d ", arr2[i]);

	return 0;
}