#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>


int main()
{
	int c1, r1;
	int c2, r2;
	int arr1[5][5] = { 0 };//第一个矩阵
	int arr2[5][5] = { 0 };//第二个矩阵
	int sum[5][5] = { 0 };//和矩阵，用于接受矩阵的和
	int i;//控制大体的行，列
	int j;//控制二层循环
	int z = 0;//控制内层循环
	printf("请输入第一个矩阵的行和列");
	scanf("%d%d", &c1, &r1);
	printf("请输入第二个矩阵的行和列");
	scanf("%d%d", &c2, &r2);
	if (r1 != c2)
	{
		printf("两个矩阵不可以相乘！");
		return 1;
	}
	//第一个矩阵 的输入
	printf("请输入矩阵");
	for (i = 0; i < c1; i++)
	{
		for (j = 0; j < r1; j++)
		{
			scanf("%d", &arr1[i][j]);
		}
	}
	//第二个矩阵 的输入
	printf("请输入矩阵");
	for (i = 0; i < c2; i++)
	{
		for (j = 0; j < r2; j++)
		{
			scanf("%d", &arr2[i][j]);
		}
	}
	//矩阵乘法计算器
	i = 0;
	for (i = 0; i < c1; i++)
	{
		for (j = 0; j < r2; j++)
		{
			for (z = 0; z < r1; z++)
			{
				sum[i][j] += arr1[i][z] * arr2[z][j];
			}
		}
	}
	//矩阵输出
	for (i = 0; i < c1; i++)
	{
		for (j = 0; j < r2; j++)
		{
			printf("%d ", sum[i][j]);
		}
		printf("\n");
	}
	return 0;
}