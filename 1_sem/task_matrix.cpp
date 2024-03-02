#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#define strk 100
#define stlb 100
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Rus");
	int n, m, cnt=0;
	double sum=0, srznach;
	int mat[strk][stlb];


	printf("Введите кол-во строк матрицы <=100:");
	scanf_s("%d", &n);
	while (true)
	{
		if (n > 0 && n < 100)
		{
			break;

		}
		printf("ОШИБКА\n");
		printf("Введите кол-во строк матрицы <=100:");
		scanf_s("%d", &n);

	}

	printf("Введите кол-во  столбцов матрицы <=100:");
	scanf_s("%d", &m);
	while (true)
	{
		if (m > 0 && m < 100)
		{
			break;
		}
		printf("ОШИБКА\n");
		printf("Введите кол-во  столбцов матрицы <=100:");
		scanf_s("%d", &m);
	}


	printf("Введите элементы матрицы: ");
	printf("\n");
	for (int i = 0; i < n; i++)//ввод матрицы с клавиатуры
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &mat[i][j]);
		}
	}
	printf("\n");

	printf("Ваша матрица: ");
	printf("\n");
	for (int i = 0; i < n; i++)//вывод матрицы для наглядности
	{
		for (int j = 0; j < m; j++)
		{
			printf(" %d ", mat[i][j]);
		}
		printf("\n");
	}

	for (int j = 0; j < m; j++)
	{
		sum = mat[0][j];
		for (int i = 0; i < n; i++)//поиск минимума строки
		{
			cnt++;
			sum += mat[i][j];
		}
		srznach = sum / cnt;
		printf("\n%f\n", srznach);
		printf("%d\n", cnt);
		printf("%f\n", sum);
	}
	printf("Ваша новая матрица: ");
	printf("\n");
	for (int i = 0; i < n; i++)//вывод матрицы для наглядности
	{
		for (int j = 0; j < m; j++)
		{
			printf(" %d ", mat[i][j]);
		}
		printf("\n");
	}

}
