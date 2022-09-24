// laba 16 rod.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<conio.h>
#include<locale.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

struct MetalVas
{
	char AName[20];
	int ANum;
	int Temp;
	float vas;
};

void SetInfo(MetalVas* Meta)
{
	printf("Вещество :\n");
	scanf("%s", Meta->AName);
	printf("Атомный номер:\n");
	while (getchar() != '\n');
	scanf("%d", &Meta->ANum);
	printf("Температура (град.С):\n");
	while (getchar() != '\n');
	scanf("%d", &Meta->Temp);
	printf("Вязкость (кг/м*сек) :\n");
	while (getchar() != '\n');
	scanf("%f", &Meta->vas);
}

void ViewInfo(MetalVas* Meta, int SIZE)
{
	printf("==============================================================================\n");
	printf("| № | Вещество | Атомный номер | Температура (град.С) | Вязкость (кг/м*сек) |\n");
	printf("==============================================================================\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("| %2d | %-8s | %13d | %18d | %19f |\n", i + 1, Meta[i].AName, Meta[i].ANum, Meta[i].Temp, Meta[i].vas);
	}
	printf("==============================================================================\n");
}

int BuffFile(char* FName)
{
	FILE* pf;
	MetalVas buff1;
	char key;
	int count = 0;

	pf = fopen(FName, "ab");
	do {
		printf("Введите название металла и его параметры:\n");
		SetInfo(&buff1);
		printf("Добавить в список?(y/n)\n");
		key = _getch();
		if (key == 'y' || key == 'Y')
		{
			fwrite(&buff1, sizeof(buff1), 1, pf);
			printf("Данные добавлены\n");
			count++;
		}
		printf("Добавить ещё?(y/n)\n");
		key = _getch();
		printf("\n");
	} while (key != 'n' && key != 'N');
	fclose(pf);
	return count;
}

int CountStructs(char* FName)
{
	FILE* pf;
	pf = fopen(FName, "rb");
	int SIZE;
	fseek(pf, 0L, SEEK_END);
	SIZE = ftell(pf);
	fseek(pf, 0L, SEEK_SET);
	return SIZE / sizeof(MetalVas);
	fclose(pf);
}

void allFileRead(MetalVas* str, char* FName)
{
	FILE* pf = fopen(FName, "rb");
	int check = fread(str, sizeof(MetalVas), CountStructs(FName), pf);
	if (check == 0)
	{
		printf("Ошибка при чтении файла");
	}
	else
	{
		ViewInfo(str, CountStructs(FName));
	}
	fclose(pf);
}

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("Нмт-1, Шабалин Родион\n");
	printf("Лабораторная работа №16,вариант №10.1\n\n");

	MetalVas a;
	int bil;
	int csm;
	do {
		printf("1. Читать из файла\n");
		printf("2. Создать новый список\n");
		printf("3. Дописать в файл\n");
		scanf("%d", &csm);
		while (getchar() != '\n');
		if (csm == 1) {
			char FName[200];
			printf("Введите название файла\n");
			scanf("%s", FName);
			while (getchar() != '\n');
			MetalVas* Data = new MetalVas[CountStructs(FName)];
			allFileRead(Data, FName);
			delete[] Data;
			bil = 1;
		}
		else if (csm == 2) {
			char FName[200];
			printf("Введите название файла\n");
			scanf("%s", FName);
			while (getchar() != '\n');
			BuffFile(FName);
			MetalVas* Data = new MetalVas[CountStructs(FName)];
			allFileRead(Data, FName);
			delete[] Data;
			bil = 1;
		}
		else if (csm == 3) {
			char FName[200];
			printf("Введите название файла\n");
			scanf("%s", FName);
			while (getchar() != '\n');
			BuffFile(FName);
			bil = 1;
		}
		else {
			bil = 0;
		}


	} while (bil != 0);
	return 0;
}
