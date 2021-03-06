#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include<cmath>

int two_mas[100000];//двоичный массив
int obr_two[100000];//обратный двоичный
int size_two = 1;//размерность двоичного числа
int solve_cout = 0;//количество решений
int num_without_zero=1;//сколько нулей до числа
int num_ten = 0;
int res;

void two(int num,int N)
{
	int i;
	int t;
	int buf[10000] = { 0 };
	for (t = 0; t < N - num_without_zero; t++)
	{
		two_mas[t] = 0;
	}
	for (i = 0; num > 0; i++)
	{
		obr_two[i] = num % 2;
		num = num / 2;
	}
	size_two = i;
	
	for (int j=0; i > 0;j++, i--)
	{
		buf[j] = obr_two[j];
	}
	i = 0;
	t = N - t;
	for (int k = t; k < N; k++,i++)
	{
		two_mas[k-1] = buf[i];
	}
}

int f(int *r, int n, int num)
{
	for (int f = 0; f < n; f++)
	{
		two_mas[f] = 0;
	}
	int all = pow(2, n - 1);
	res = r[0];//для сравнения с ответом
	for (int i = 0; i < all; i++)//поставить индексы тредов
	{
		for (int j = 0; j < n-1; j++)
		{
			if (two_mas[j] == 0)res = res - r[j + 1];
			else res = res + r[j + 1];
		}
		if (res == num)solve_cout++;
		res = r[0];
		num_ten++;
		two(num_ten, n);
	}
	return solve_cout;
}

int f1(int *r, int n, int num)
{
	int all = pow(2, n - 1), tmp;
	for (int i = 0; i < all; i++)
	{
		tmp = r[0];
		for (int j = i, k = 1; k < n; j >>= 1, k++)//Проверяем все возможные варианты для каждого элемента если необходим ''+'' то возвращаем 1 и выходим из функции
			tmp = (j & 1) ? tmp + r[k] : tmp - r[k];
		if (tmp == num)
		{
			return i;
		}
	}
	return -1;//Иначе возвращаем -1 и говорим что нужен ''-''
}

int main()
{
	int *tmp, N, signs, num;
	int all_s = 0;
	scanf("%d", &N);//Вводим число обозначающее количество элементов без S
	all_s = pow(2, N - 1);
	tmp = (int*)malloc(N * sizeof(int));//Вводим динамический массив
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &tmp[i]);//Вводим элементы с клавиатуры
	}
	scanf("%d", &num);//Вводим S

		signs = f(tmp, N, num);//Присваиваем переменной значение функции
		if (signs == 0)
			printf("no solution \n");//Если не найдено ни одной комбинации то выводим ''НЕТ РЕЗУЛЬТАТА''
		//else
		//	printResult(tmp, N, num, signs);
	free(tmp);
	printf("count of solve=%d\n", solve_cout);
}