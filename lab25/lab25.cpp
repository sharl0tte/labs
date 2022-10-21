#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>

class common_fraction
{
	float numerator, denominator; //private поля
public:
	//конструкторы
	common_fraction() : numerator(0.f), denominator(0.f) {} //конструктор по умолчанию
	common_fraction(float a, float b) : numerator(a), denominator(b) {} //конструктор с парааметрами

	//селекторы
	float get_numr() { return numerator; } //числитель

	//знаменатель
	float get_den() {
		if (denominator == 0.f) //предотвратить деление на 0
			denominator = 1.f;

		return denominator;
	} 

	//модификаторы
	void set_numr(float a) { numerator = a; }
	void set_den(float b) { denominator = b; }

	inline float fraction_value() { return get_numr() / get_den(); } // значение дроби

	// перегрузка операторов
	common_fraction operator/(common_fraction a) { return common_fraction(get_numr() / (a.get_numr() != 0.f) ? a.get_numr() : 1.f, get_den() / (a.get_den() != 0.f) ? a.get_den() : 1.f); }
	common_fraction operator*(common_fraction a) { return common_fraction(get_numr() * a.get_numr(), get_den() * a.get_den()); }
	common_fraction operator-(common_fraction a) { return common_fraction(get_numr() - a.get_numr(), get_den() - a.get_den()); }
	common_fraction operator+(common_fraction a) { return common_fraction(get_numr() + a.get_numr(), get_den() + a.get_den()); }
	bool operator<(common_fraction a) { return fraction_value() < a.fraction_value(); }
	bool operator>(common_fraction a) { return fraction_value() > a.fraction_value(); }
	bool operator==(common_fraction a) { return fraction_value() == a.fraction_value(); }

	void print_fraction() { printf("(%f / %f)", numerator, denominator); }
	void print_fractionln() { printf("(%f / %f)\n", numerator, denominator); }
};

float frand(float min, float max)
{
	return min + rand() / (float)RAND_MAX * (max - min);
}

#define MIN_RAND -100.f
#define MAX_RAND 100.f

const char *p_has_noalloc_errmsg = "Memory is not allocated. Allocate fractions by menu item 1!\n";

void display_menu()
{
	printf(
		"\n-------------------------\n"
		" 1. set array size\n"
		" 2. fill array\n"
		" 3. modify value\n"
		" 4. exec methods\n"
		" 5. clear and display this menu\n"
		"-------------------------\n"
	);
}

int i, count;
common_fraction *p_fractions = NULL;

void handle_menu(int opt)
{
	float stride = 0.f;

	//разберем выбранный пункт меню
	switch (opt) {
	case 1: //задать кол-во дробей
		printf("--- create fractions array ---\n");
		do {
			printf("Enter fractions count: ");
			scanf("%d", &count);
		} while (count <= 0); //повторим ввод если размер задан неверно

		if (p_fractions) {
			printf("Already allocated memory has free\n");
			delete[] p_fractions;
		}

		p_fractions = new common_fraction[count];
		printf("Array of fractions size: %d\n", count);
		break;

	case 2: //заполнить по возрастанию с шагом
		printf("--- fill allocated fractions ---\n");
		if (!p_fractions) {
			printf(p_has_noalloc_errmsg);
			break;
		}

		printf("Enter values stride: ");
		scanf("%f", &stride);
		for (i = 0; i < count; i++)
			p_fractions[i] = common_fraction((float)i - stride, (float)i + stride);

		for (i = 0; i < count; i++)
			printf("[%d] numr = %f  den = %f\n", i, p_fractions[i].get_numr(), p_fractions[i].get_den());

		break;

	case 3: //задать значение
		printf("--- set fractions values ---\n");
		if (!p_fractions) {
			printf(p_has_noalloc_errmsg);
			return;
		}

		printf("Set values from index: ");
		scanf("%d", &opt);
		printf("Number of values: ");
		scanf("%d", &i);

		if (opt < 0) {
			printf("Selected index out of bounds (min)\n");
			break;
		}

		if (i <= 0) {
			printf("Number of elements equals 0 or negative value!\n");
			break;
		}

		if ((opt + i) > count) {
			printf("SelectedIndex + NumOfSetElements > NumberOfElements\n");
			break;
		}

		int idx;
		common_fraction *p_fr;
		float newnumr, newden;
		for (int j = 0; j < i; j++) {
			idx = opt + j; //посчитаем индекс
			p_fr = &p_fractions[idx];
			printf("Enter new fraction NUMERATOR and DENOMINATOR: \n");
			scanf("%f %f", &newnumr, &newden);
			p_fr->set_numr(newnumr);
			p_fr->set_den(newden);
			printf("New fraction value on index %d (numr = %f,  den = %f)\n", idx, newnumr, newden);
		}
		break;

	case 4: { //задать значение
		printf("--- execute fractions methods ---\n");
		if (!p_fractions) {
			printf(p_has_noalloc_errmsg);
			return;
		}

		printf("Get values from index: ");
		scanf("%d", &opt);
		printf("Number of values: ");
		scanf("%d", &i);

		if (opt < 0) {
			printf("Selected index out of bounds (min)\n");
			break;
		}

		if (i <= 0) {
			printf("Number of elements equals 0 or negative value!\n");
			break;
		}

		if ((opt + i) > count /*-1*/) {
			printf("SelectedIndex + NumOfSetElements > NumberOfElements\n");
			break;
		}

		common_fraction p_fr_result;
		for (int j = 0, k = opt; j < i && k < (count - 1); j++, k++) {
			common_fraction &p_fr_a = p_fractions[k];
			common_fraction &p_fr_b = p_fractions[k + 1];

			printf("Fraction on index %d:\n", k);

			printf("\t(%f / %f) / (%f / %f) = ", p_fr_a.get_numr(), p_fr_a.get_den(), p_fr_b.get_numr(), p_fr_b.get_den());
			common_fraction(p_fr_a / p_fr_b).print_fractionln();

			printf("\t(%f / %f) * (%f / %f) = ", p_fr_a.get_numr(), p_fr_a.get_den(), p_fr_b.get_numr(), p_fr_b.get_den());
			common_fraction(p_fr_a * p_fr_b).print_fractionln();

			printf("\t(%f / %f) - (%f / %f) = ", p_fr_a.get_numr(), p_fr_a.get_den(), p_fr_b.get_numr(), p_fr_b.get_den());
			common_fraction(p_fr_a - p_fr_b).print_fractionln();

			printf("\t(%f / %f) + (%f / %f) = ", p_fr_a.get_numr(), p_fr_a.get_den(), p_fr_b.get_numr(), p_fr_b.get_den());
			common_fraction(p_fr_a + p_fr_b).print_fractionln();

			printf("\tFraction (%f / %f) < (%f / %f) == %s\n",
				p_fr_a.get_numr(), p_fr_a.get_den(),
				p_fr_b.get_numr(), p_fr_b.get_den(),
				(p_fr_a < p_fr_b) ? "TRUE" : "FALSE"
			);

			printf("\tFraction (%f / %f) > (%f / %f) == %s\n",
				p_fr_a.get_numr(), p_fr_a.get_den(),
				p_fr_b.get_numr(), p_fr_b.get_den(),
				(p_fr_a > p_fr_b) ? "TRUE" : "FALSE"
			);

			printf("\tFraction (%f / %f) == (%f / %f) == %s\n",
				p_fr_a.get_numr(), p_fr_a.get_den(),
				p_fr_b.get_numr(), p_fr_b.get_den(),
				(p_fr_a == p_fr_b) ? "TRUE" : "FALSE"
			);
		}
		break;
	}

	case 5: //задать значение
		system("cls");
		display_menu();
		if (p_fractions) {
			delete[] p_fractions;
			p_fractions = NULL;
		}

		break;

	default: // введен пункт меню который не существует
		printf("Unknown menu item!\n");
		display_menu();
	}
}

int main()
{
	int opt;
	display_menu();
	// читаем с консоли целые числа и проверяем на правильность
	printf("> ");
	while (scanf("%d", &opt) == 1) {
		srand((unsigned int)time(NULL));
		handle_menu(opt);
		printf("> ");
	}
	return 0;
}