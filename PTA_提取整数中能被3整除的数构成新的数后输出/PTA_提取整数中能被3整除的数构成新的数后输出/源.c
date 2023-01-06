#define _CRT_SECURE_NO_WARNINGS 1


#include <stdio.h> 
void fun(int x, int* px);
int main()
{
	int num, t;
	scanf("%d", &num);
	fun(num, &t);
	printf("The result is: %d\n", t);
	return 0;
}

/* 请在这里填写答案 */

void fun(int x, int* px)
{
	int tem[20] = { 0 }, i = 0, j = x;
	while (x)
	{
		if ((x % 10) % 3 == 0)
			tem[i++] = x % 10;
		x /= 10;
	}
	if (i != 0)
	{
		*px = 0;
		while (i--)
		{
			*px = *px * 10 + tem[i];
		}
	}
	else
	{
		*px = j;
	}
}