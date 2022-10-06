#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <locale>

bool bolshe3(const char *gav) { 
	return strlen(gav) > 3; 
}

void read_string(char *dst)
{
	scanf("%[^\n]", dst);
}

int main() {
	setlocale(0, "Russian");
	printf("Нмт-1, Шабалин Родион\n");
	printf("Лабораторная работа №14,вариант №10\n\n");
	char arr[1024];
	read_string(arr);
	char *ptr = strtok(arr, " ");
	do {
		
		if (bolshe3(ptr)) {

			printf("слово где букв больше 3: %s количесво символов:%d\n", ptr,strlen(ptr));//ptr - слово из строки
		}
	} while ((ptr = strtok(NULL, " ")));
}
