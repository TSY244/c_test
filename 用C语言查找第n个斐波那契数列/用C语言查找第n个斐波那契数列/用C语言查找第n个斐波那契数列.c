#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
int F1(int N)
{
	int left = 1, right = 1, A = 2, B = 0;
	while (A < N)
	{
		B = left + right;
		left = right;
		right = B;
		A++;
	}
	return B;
}
int main()
{
	int n = 0, ret = 0;
	scanf("%d", &n);
	if (n > 2)
	{
		ret = F1(n);
		printf("��%d��쳲���������%d", n, ret);
	}
	else
	{
		printf("��%d��쳲���������1", n);
	}
	return 0;
}