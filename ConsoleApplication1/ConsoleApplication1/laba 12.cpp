#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

typedef struct circle_s {
	float x, y, r;
} circle_t;

//площать круга 
float ploshad(const circle_t *a)
{
	return 3.14 * (a->r * a->r);
}

//длина окружности
float circle_length(const circle_t *a)
{
	return (a->r * 2) * 3.14;
}

//длина стороны квадрата вписанного в окружность
float rect_in_circle_compute(const circle_t *a)
{
	return a->r * sqrtf(2.f);
}

void enter_circle_data(circle_t *a)
{
	printf("Enter circle data: x y radius: ");
	scanf("%f %f %f", &a->x, &a->y, &a->r);
}

void print_circle_data(const circle_t *a)
{
	printf("Circle: x = %f y = %f r = %f\n", a->x, a->y, a->r);
	
}

int main()
{
	int i;
	circle_t circle;
	while (true)
	{
		scanf("%d", &i);
		switch (i) {
		case 1:
		enter_circle_data(&circle);
		print_circle_data(&circle);
		printf("Ploshad: %f\n", ploshad(&circle));
		printf("Dlinna: %f\n", circle_length(&circle));
		printf("Rect in circle side length: %f\n", rect_in_circle_compute(&circle));
		break;

		case 2:
			goto __exit;
		}
	}
__exit:
	return 0;
}