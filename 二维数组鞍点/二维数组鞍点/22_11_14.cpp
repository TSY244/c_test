#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{
	int i,j;//���ÿһ��Ԫ��
	int a,b;//�Զ�ά�������
	int arr[2][3]={{2,3,1},{8,5,6}};
	int ri,rj;//��¼����
	int count=0;//����ֵ
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			count=0;
			for(a=0;a<3;a++)
			{
				if(arr[i][j]<arr[i][a])
				{
					count=1;
					break;
				}
			}

			for(a=0;a<2;a++)
			{
				if(count==1)
					break;
				if(arr[i][j]>arr[a][j])
				{
					count=1;
					break;
				}
			}
			if(count!=1)
				printf("��%d�У���%d��,%d�ǰ���\n",i+1,j+1,arr[i][j]);
		}
	}
	return 0;
}