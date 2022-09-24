#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long file_size(FILE *fp)
{
	long offset;
	fseek(fp, 0, SEEK_END);//переместится в конец  файла
	offset = ftell(fp);//узнать позицию в файле в байтах
	fseek(fp, 0, SEEK_SET);//вернутся в начало файла
	return offset;
}

bool is_zaglav(const char *p_string)
{
	bool is_first_char = true;
	for (int i = 0; p_string[i]; i++) {
		if (!ispunct((unsigned char)p_string[i]) && isspace((unsigned char)p_string[i]))
			continue;

		if (is_first_char && isupper((unsigned char)p_string[i]))
			return true;
		else is_first_char = false;
	}
	return false;
}


int main()
{
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
	if (!filesize) {//проеврка равен ли размер файла нулю
		printf("Empty file!\n");
		fclose(infile);//закрываем файл
		fclose(outfile);
		return 3;
	}

	//выделаем динамическую мапять под данные файла infile
	char *text = (char *)calloc(filesize, sizeof(char));
	if (!text) {//если память выделить не удалось заеверш прогу
		printf("Failed to allocate memory!\n");
		return 4;
	}

	//читаем данные из файла в выделлный блок памяти
	size_t size = fread(text, sizeof(char), filesize, infile);
	
	if (size != filesize) {//проверяем рано ли количество прочитанных данных тому которое треб прочитать
		printf("error reading from file!\n");
		return 5;
	}

	printf(" ----- \n%s\n ----- \n", text);//выведем данные файла

	//разобьеми данные файла по словам через пробелы
	int i = 0;
	char *tok = strtok(text, " ");
	do {
		if (is_zaglav(tok)) {//если слво заглав,выволи его в консоль и  записываем его в outfile
			printf("%d Stroka s zaglavnoi bukvy: %s\n", i, tok);
			fprintf(outfile, "%d: %s\n", i, tok);
			i++;
		}
	} while ((tok = strtok(NULL, " ")));

	free(text);//освобождаем выделенную память, в которой хранились данные файла
	fclose(infile);
	fclose(outfile);
	return 0;
}