#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{
	int x=0,y=0,z=0;
	int i;
	for(i=100;i<1000;i++)
	{
		x=i/100;
		z=i%10;
		y=((i-z)%100)/10;
		if(x*x*x+y*y*y+z*z*z==i)
		{
			printf("%d\n",i);
		}
	}
	return 0;
}