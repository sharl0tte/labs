// laba 16
//
#include<stdio.h>
#include<conio.h>
#include<locale.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define _CRT_SECURE_NO_WARNINGS //Разрешение использовать небезопасные функции

struct Phono
{
	char manufacturer[10];
	char model[10];
	int data;
	int odata;
	float dia;
};

void SetInfo(Phono* phon)
{
	printf("Производитель:\n");
	//while (getchar()!= '\n');
	scanf("%s", phon->manufacturer);
	printf("Модель:\n");
	while (getchar() != '\n');
	scanf("%s", phon->model);
	printf("Память:\n");
	while (getchar() != '\n');
	scanf("%d", &phon->data);
	printf("Оперативная память:\n");
	while (getchar() != '\n');
	scanf("%d", &phon->odata);
	printf("Диагональ:\n");
	while (getchar() != '\n');
	scanf("%f", &phon->dia);
}

void ViewInfo(Phono* phon, int SIZE)
{
	printf("===================================================================\n");
	printf("| № | Производитель | Модель | Память | Опер. память | Диагональ |\n");
	printf("===================================================================\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("| %2d | %-13s | %6s | %6d | %12d | %-9.2f |\n", i + 1, phon[i].manufacturer, phon[i].model, phon[i].data, phon[i].odata, phon[i].dia);
	}
	printf("===================================================================\n");
}

int BuffFile(char* FName)
{
	FILE* pf;
	Phono buff1;
	char key;
	int count = 0;

	pf = fopen(FName, "ab");
	do {
		printf("Введите характеристики телефона:\n");
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
	return SIZE / sizeof(Phono);
	fclose(pf);
}

void allFileRead(Phono* str, char* FName)
{
	FILE* pf = fopen(FName, "rb");
	int check = fread(str, sizeof(Phono), CountStructs(FName), pf);
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
	printf("Нмт-2, Ильичев\n");
	printf("Лабораторная работа №16,вариант №4.1\n\n");

	Phono a;
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
			Phono* Data = new Phono[CountStructs(FName)];
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
			Phono* Data = new Phono[CountStructs(FName)];
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

