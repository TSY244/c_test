#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int number(char ch)
{
	if(ch>='0'&&ch<='9')
	{
		return 1;
	}
	return 0;
}

int main()
{
	char ch;
	int count=0;
	printf("������һ���ַ���");
	while('\n'!=(ch=(getchar())))
	{
		count+=number(ch);
	}
	printf("һ����%d������",count);
	return 0;
}