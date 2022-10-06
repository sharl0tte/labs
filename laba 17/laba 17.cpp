#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <locale>
#include <conio.h>
#include <stdlib.h>     
#include <time.h>
#define USHORT unsigned short

size_t size_bit(unsigned short value) {

	size_t num_zeroes = 0;

	for (int d = 15; d >= 0; d--)
	{
		if (((1 << d) & value) == 0)
			++num_zeroes;
	}

	return num_zeroes;
}

char * get_str(unsigned short value) {
	char str[1024];
	char str2[1024];

	memset(str2, 0, 1024);
	memset(str, 0, 1024);
	for (int d = 15; d >= 0; d--)
		strcat(str2, ((1 << d) & value) ? "1" : "0");

	sprintf(str, "10=%d 16=%x 2=%s\n", value, value, str2);

	return str;
}
void main()
{
	USHORT mass[1024];
	srand(time(NULL));
	USHORT min = 65535;
	for (int i = 0; i < 1024; i++) {
		mass[i] = 1 + rand() % 65534;
		if (size_bit(mass[i]) % 3 && min >= mass[i]) {
			min = mass[i];
		}
	}
	printf(get_str(min));
}
