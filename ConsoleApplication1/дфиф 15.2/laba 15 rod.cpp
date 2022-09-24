#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale>

long file_size(FILE *fp)
{
	long offset;
	fseek(fp, 0, SEEK_END);
	offset = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return offset;
}



bool bolshe3(const char *gav) {
	return strlen(gav) > 3;
}

int main()
{
	setlocale(0, "Russian");
	printf("Нмт-1, Шабалин Родион\n");
	printf("Лабораторная работа №15,вариант №10\n\n");

	FILE *infile = fopen("infile.txt", "rt");
	if (!infile) {
		printf("Error open file 'infile.txt'\n");
		return 1;
	}

	FILE *outfile = fopen("outfile.txt", "wt");
	if (!outfile) {
		printf("Error open file 'outfile.txt'\n");
		return 2;
	}

	long filesize = file_size(infile);
	if (!filesize) {
		printf("Empty file!\n");
		fclose(infile);
		fclose(outfile);
		return 3;
	}

	char *text = (char *)calloc(filesize, sizeof(char));
	if (!text) {
		printf("Failed to allocate memory!\n");
		return 4;
	}
	size_t size = fread(text, sizeof(char), filesize, infile);

	if (size != filesize) {
		printf("error reading from file!\n");
		return 5;
	}

	printf(" ----- \n%s\n ----- \n", text);

	int i = 0;
	char *tok = strtok(text, " ");
	do {
		if (bolshe3(tok)) {
			printf("%d Stroka gde bolse 3: %s\n", i, tok);
			fprintf(outfile, "%d: %s\n", i, tok);
			i++;
		}
	} while ((tok = strtok(NULL, " ")));

	free(text);
	fclose(infile);
	fclose(outfile);
	return 0;
}