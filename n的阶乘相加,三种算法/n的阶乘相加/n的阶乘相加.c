#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>

////º¯ÊýµÄµÝ¹é
//int func(int n)
//{
//	int sum=1,i;
//	if(n>0)
//	{
//		for(i=n;i>0;i--)
//		{
//			sum*=i;
//		}
//		return sum+func(n-1);
//	}
//	else 
//	{
//		return 0;
//	}
//}

int func(int n)
{
	int i,j,sum=0,tem=1;
	for(i=1;i<=n;i++)
	{
		tem=1;
		for(j=1;j<i+1;j++)
		{
			tem*=j;  
		}
		sum+=tem;
	}
	return sum;
}

int main()
{
	int x=0;
	scanf("%d",&x);
	printf("%d\n",func(x));
}
