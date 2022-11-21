#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
//要求：不改变单词的顺序的情况下，将每一个单词翻转（单词倒序写）。输入中只有英文单词和空格（不含其它字符）。
//
//如图：其中I am happy today是键盘输入的。
void exchange(char* arr,int n)
{
	int a=0;//用于统计单词中字母个数
	int i;
	char arr2[20]={0};
	for(i=0;i<=n;i++)
	{
		if(arr[i]!=' '&&arr[i]!='\0')
		{
			arr2[a]=arr[i];
			a++;
		}
		else//执行打印
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
	char arr[100];//存放句子
	int n;//计算大小
	printf("Input:\n");
	gets(arr);
	n=strlen(arr);
	arr[n]='\0';
	printf("Output:\n");
	exchange(arr,n);
	return 0;
}