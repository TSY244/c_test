#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{
	int a = 0, b = 1, c = 1;
	printf("欢迎使用阶层计算！\n请输入数字:");
	scanf("%d", &a);
	for (c = 1; b < a+1; b++)
	{
		c = c * b;
	}
	/*while (b<a+1)
	{

		c = b * c;
		b++;
		
	}*/
	printf("%d的阶层是%d", a, c);
	return 0;
}