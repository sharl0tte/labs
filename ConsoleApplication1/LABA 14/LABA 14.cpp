// 
// Lab 14
// 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool is_zaglav(const char *p_string)
{
	bool is_first_char = true;
	for (int i = 0; p_string[i]; i++) {
		if (isspace(p_string[i]))
			continue;

		if (is_first_char && isupper(p_string[i]))
			return true;
		else is_first_char = false;
	}
	return false;
}

typedef struct str_s {
	char string[512];
} str_t;

int get_kolvo_slov(const char *p_str)
{
	int cwords = 0;
	for (int i = 0; p_str[i]; i++) {
		if (p_str[i] == ' ') {
			cwords++;
		}
	}
	return cwords + 1;
}

int main()
{
	char str[128];
	printf("Lab 14\nVvedite stroki: ");
	scanf("%[^\r\n]", str);
	int count = get_kolvo_slov(str);
	printf("count: %d\n", count);

	str_t *p_strings = (str_t *)calloc(count, sizeof(str_t));
	if (!p_strings) {
		printf("Ne udalos vydelit pamyat!\n");
		return 1;
	}

	int i = 0;
	char *ptr = strtok(str, " ");
	do {
		strcpy(p_strings[i].string, ptr);
		i++;
	} while ((ptr = strtok(NULL, " ")));

	for (i = 0; i < count; i++) {
		if (is_zaglav(p_strings[i].string)) {
			printf("Zaglavnoe slovo: %s  Col-vo bukv: %d\n", p_strings[i].string, strlen(p_strings[i].string));
		}
	}

	free(p_strings);
	return 0;
}