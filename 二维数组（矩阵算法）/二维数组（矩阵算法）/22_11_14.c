#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int main()
{
	double M[5][2]={{1,1},{1,1},{1,1},{1,1,},{1,1}};
	double MT[2][5];
	double SUM[5][5]={0};
	int i,j;//用于建立转置，和和矩阵
	int r,c;//用于计算，和矩阵
	for(i=0;i<5;i++)
	{
		for(j=0;j<2;j++)
		{
			MT[j][i]=M[i][j];
		}
	}
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			for(c=0;c<2;c++)
			{
				SUM[i][j]+=M[i][c]*MT[c][j];
			}
		}
	}
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%.2lf  ",SUM[i][j]);
		}
		printf("\n");
	}
	return 0;
}