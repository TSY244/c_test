#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{

	int x=0;
	scanf("%d",&x);
	if(x<0)
	{
		printf("-%o,-%x",-x,-x);
	}
	else 
	{
		printf("%o,%x",x,x);
	}

	return 0;
}