#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{
	int num=0,i=0,count=0;
	scanf("%d",&num);
	for(i=0;i<32;i++)//32����Ϊ��int ����4���ֽڣ�ÿ���ֽ�8���ַ�,���Դ洢a��32λ2����
	{
		if(1==((num=num>>i)&1))
		{
			count++;
		}
	}
	printf("%d��������%d��1\n",num,count);
	return 0;
}
