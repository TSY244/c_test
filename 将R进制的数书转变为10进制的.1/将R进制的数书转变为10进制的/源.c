#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>


int main()
{
	char arr[100] = { 0 };
	int ten_R = 0;
	int R = 0;//进制
	int size = 0;
	int tem = 0;
	int i = 0;
	printf("Input:");
	scanf("%d", &R);
	getchar();
	gets(arr);
	//转化为10进制
	size = strlen(arr);
	while (size--)
	{
		i = strlen(arr) - 1;
		if (arr[size] > 47 && arr[size] < 58)
		{
			tem = arr[size] - 48;
			i -= size;
			while (i--)
			{
				tem *= R;
			}
			ten_R += tem;
		}
		else
		{
			tem = arr[size] - 55;
			i -= size;
			while (i--)
			{
				tem *= R;
			}
			ten_R += tem;
		}
	}
	printf("Output:%d", ten_R);
	return 0;
}

