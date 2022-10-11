#define _CRT_SECURE_NO_WARNINGS //отключим проверку unsafe функций (в нашем случае scanf)
#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc
#include <string.h> //memset     
#include <stdbool.h> //bool
#include <intrin.h> //__rdtsc

typedef unsigned short ushort;

#define MAX_VAL 20 //самое большое значение рандомного числа

#define CNT(x) (sizeof(x) / sizeof(x[0])) //макрос получения количества элементов массива (делим размер массива на размер одного элемента)

// 
// count_bits
// 
// посчитать количество бит, равных значению val ( 0 / 1 )
// 
int count_bits(ushort value, bool val)
{
	int n_bits = 0;
	for (int i = 0; i < sizeof(ushort) * 8; i++) // 2 байта * 8 бит == 16 бит (размер числа short в битах)
		if (((1 << i) & value) == val) //если проверяемый бит 1 И бит числа == val
			n_bits++; //увеличиваем счетчик

	return n_bits;
}

// 
// binary_print
// 
// вывести число в двоичной системе счисления в виде строки
// 
const char *binary_print(ushort value)
{
	static char string[sizeof(ushort) * 8 + 1]; //размер массива равен числу бит числа + 1 байт под терминальный нуль для завершения строки
	string[sizeof(ushort) * 8] = '\0'; //записываем в конец терминальный нуль чтобы завершить строку
	for (int i = 0; i < sizeof(ushort) * 8; i++) // 2 байта * 8 бит == 16 бит (размер числа short в битах)
		string[i] = ((1 << i) & value) ? '1' : '0'; //если текущий бит равен 1, записываю в строку символ '1', иначе '0'

	return (const char *)string;
}

// 
// print_array
// 
// вывод массива
// 
void print_array(const ushort *p_numbers, const int number_of_elements)
{
	for (int i = 0; i < number_of_elements; i++)
		printf("%hu ", p_numbers[i]);

	printf("\n");
}

// 
// fill_array
// 
// заполнение массива рандомными числами
// 
void fill_array(ushort *p_dst, const int number_of_elements)
{
	// использую счетчик таков процессора с начала работы компьютера (__rdtsc) как высокоточный источник чисел
	// каждый такт его значение изменяется, что гарантирует менее повторяющиеся значения
	for (int i = 0; i < number_of_elements; i++) {
		srand((unsigned int)__rdtsc() + i);
		p_dst[i] = (ushort)(rand() % MAX_VAL); 
	}
}

// 
// minimum
// 
// возвращает минимальное из a и b
// 
ushort minimum(ushort a, ushort b)
{
	if (a < b)
		return a;

	return b;
}

#define USHORT_MAX ((ushort)-1) //узнаем максимальный диапазон типа ushort, переполним беззнаковый диапазон

int main()
{
	int i, size, index, step; //переменные под счетчик, размер динмаического массива и индекс минимального числа с количеством нулевых бит кратным 3
	ushort *p_array, min_val; //указатель для хранения адреса блока динмической памяти и временная переменная для минимального значения

__repeat_full: //метка полного повтора с отображением информации
	printf(
		"\n\nMenu:\n"
		"1. Continue\n" //1 и любое другое число - продолжить работу программы
		"0. Exit\n\n" //0 - выход
	);
	scanf("%d", &i); //ждем пока пользователь введет номер пункта меню
	if (!i) //если номер пункта меню равен 0 (выход)
		return 0; //возвращаем из main 0 (завершаем программу)


__repeat_size: //метка повтора ввода размера массива, если не удалось выделить память
	printf("Enter array size: ");
	scanf("%d", &size); //ждем пока пользователь введет количество элементов
	printf("Array size is: %d\n", size);

	//выделяем память под указанное количество элементов
	if (!(p_array = (ushort *)malloc(size * sizeof(ushort)))) { //если не удалось выделить память (malloc вернул NULL)
		printf("ERROR: Failed to allocate %d bytes!\n", size); //говорим сколько байт хотели выделить
		goto __repeat_size; //переходим на метку выше, чтобы повторить выделение памяти
	}


	//меню методов заполнения массива
__repeat_fill_method: //метка повтора ввода метода заполнения массива
	printf(
		"\nFill method:\n"
		"1. Random\n" //рандомный метод заполнения
		"2. From x1 and step k\n\n" //заполняем с элемента x до конца массива с шагом k
	);
	scanf("%d", &i); //ждем пока пользователь введет номер пункта меню метода заполнения массива
	switch (i) { //сравним выбранный пункт меню со всеми номерами меню
	case 1: //рандом
		printf("Selected method Random\n");
		fill_array(p_array, size); //заполнить рандомными числами
		break;

	case 2: //от X с шагом K
		printf("Selected method from X with step K\nEnter X and K: ");
		scanf("%d %d", &i, &step); //прочитаем X и K

		//проверим не выходит ли индекс начала за пределы массива
		if (i < 0 || i > size) {
			printf("Index out of bounds. Auto set to 0\n"); //оповестим пользователя
			i = 0; //если индекс выходит за пределы, поставим его на 0
		}

		if (step < 0) {
			step *= -1; //сделаем step положительным. умонжим step на -1 и сохраним туда же получившееся значение
			printf("Step must be only postive number! Set step to %d\n", step); //оповестим пользователя
		}

		//заполним по очереди от указанного индекса с указанным шагом до конца массива
		//сначала заполним весь массив нулями. memset заполняет побайтно, по этому умонжим количество элементов на размер одного элемента
		memset(p_array, 0, size * sizeof(ushort));
		for (int k = i; k < size; k += step) {
			srand((unsigned int)__rdtsc() + i); //поставим новый seed для rand
			p_array[k] = (ushort)(rand() % MAX_VAL); //получим рандомное число до MAX_VAL
		}
		break;

	default:
		printf("Unknown menu parameter %d !\n", i); //введен неверный пункт меню!
		goto __repeat_fill_method; //повторим ввод
	}
	
	printf("Source array: ");
	print_array(p_array, size); //выводим исходный массив

	//выведем количество нулевых битов чисел и сами числа
	printf("Number of zero bits in numbers:\n");
	for (i = 0; i < size; i++)
		printf("%hu\t%s\n", p_array[i], binary_print(p_array[i])); //спецификатор формата %hu (sHort Unsigned) выводит беззнаковое целое 16-ти битное число

	//выведем минимальное число из всех чисел, у которых количество нулевых бит кратно трем
	printf("\nBits multiple 3 min number:\n");
	index = -1; //изначально индекс будет -1 (нет такого числа)
	min_val = USHORT_MAX;
	for (i = 0; i < size; i++) {
		if (!(count_bits(p_array[i], false) % 3)) { //!(n % 3) - проверка четности n на 3.  В нашем случае count_bits вернет количество бит, и если оно кратно трем, то сравним это число с минимальным
			
			//сравним прошлое минимальное с новым
			//если новое минимальное меньше прошлого, оно запишется в min_val
			min_val = minimum(min_val, p_array[i]);
			index = i; //так же сохраним индекс в массиве этого минимального числа
		}
	}

	//выведем минимальное число в разных системах счисления
	//индекс в массиве мы сохраняли как раз для этого
	if (index != -1) {//если было число с количеством нулевых бит кратным 3
		printf("*10 = %d  *16 = %X  *2 = %s", p_array[index], p_array[index], binary_print(p_array[index]));
	}
	else {
		printf("No numbers with bits multiple 3!\n"); //не было чисел с количеством нулевых бит кратных 3
	}
	free(p_array); //освободим динмическую память занятую массивом

	goto __repeat_full; //повторяем отображение меню, перейдя на метку __repeat_full
	return 0;
}
