#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>


int main()
{
	int c1, r1;
	int c2, r2;
	int arr1[5][5] = { 0 };//��һ������
	int arr2[5][5] = { 0 };//�ڶ�������
	int sum[5][5] = { 0 };//�;������ڽ��ܾ���ĺ�
	int i;//���ƴ�����У���
	int j;//���ƶ���ѭ��
	int z = 0;//�����ڲ�ѭ��
	printf("�������һ��������к���");
	scanf("%d%d", &c1, &r1);
	printf("������ڶ���������к���");
	scanf("%d%d", &c2, &r2);
	if (r1 != c2)
	{
		printf("�������󲻿�����ˣ�");
		return 1;
	}
	//��һ������ ������
	printf("���������");
	for (i = 0; i < c1; i++)
	{
		for (j = 0; j < r1; j++)
		{
			scanf("%d", &arr1[i][j]);
		}
	}
	//�ڶ������� ������
	printf("���������");
	for (i = 0; i < c2; i++)
	{
		for (j = 0; j < r2; j++)
		{
			scanf("%d", &arr2[i][j]);
		}
	}
	//����˷�������
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
	//�������
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