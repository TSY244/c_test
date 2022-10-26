#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

void minmax(int arr[],int* min,int* max,int sz)
{
	int i=0;
	*max=*min=arr[0];
	for(i=0;i<sz;i++)
	{
		if(*min>=arr[i])
		{
			*min=arr[i];
		}
		if(*max<=arr[i])
		{
			*max=arr[i];
		}
	}
}

int main()
{
	int arr[]={12,3,643,2,45,83,45,18,8,264,68,5,81,22};
	int min=0,max=0;
	minmax(arr,&min,&max,sizeof(arr)/sizeof(0));
	printf("min=%d,max=%d",min,max);
	return 0;
}
