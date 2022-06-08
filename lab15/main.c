#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long file_size(FILE *fp)
{
	long offset;
	fseek(fp, 0, SEEK_END);
	offset = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return offset;
}

bool is_zaglav(const char *p_string)
{
	bool is_first_char = true;
	for (int i = 0; p_string[i]; i++) {
		if (!ispunct(p_string[i]) && isspace(p_string[i]))
			continue;

		if (is_first_char && isupper(p_string[i]))
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

	if (fread(text, sizeof(char), filesize, infile) != filesize) {
		printf("error reading from file!\n");
		return 5;
	}

	printf(" ----- \n%s\n ----- \n", text);

	int i = 0;
	char *tok = strtok(text, " ");
	do {
		if (is_zaglav(tok)) {
			printf("%d Stroka s zaglavnoi bukvy: %s\n", i, tok);
			fprintf(outfile, "%d: %s\n", i, tok);
			i++;
		}
	} while ((tok = strtok(NULL, " ")));

	free(text);
	fclose(infile);
	fclose(outfile);
	return 0;
}