#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
//Ҫ�󣺲��ı䵥�ʵ�˳�������£���ÿһ�����ʷ�ת�����ʵ���д����������ֻ��Ӣ�ĵ��ʺͿո񣨲��������ַ�����
//
//��ͼ������I am happy today�Ǽ�������ġ�
void exchange(char* arr,int n)
{
	int a=0;//����ͳ�Ƶ�������ĸ����
	int i;
	char arr2[20]={0};
	for(i=0;i<=n;i++)
	{
		if(arr[i]!=' '&&arr[i]!='\0')
		{
			arr2[a]=arr[i];
			a++;
		}
		else//ִ�д�ӡ
		{
			for(;a>0;a--)
			{
				printf("%c",arr2[a-1]);
			}
			if(i<n)
			{
				printf(" ");
			}
			else
			{
				printf("\n");
			}
			a=0;
		}
	}
}


int main()
{
	char arr[100];//��ž���
	int n;//�����С
	printf("Input:\n");
	gets(arr);
	n=strlen(arr);
	arr[n]='\0';
	printf("Output:\n");
	exchange(arr,n);
	return 0;
}