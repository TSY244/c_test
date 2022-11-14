#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
//—°‘ÒÀ„∑®Ωµ–Ú

int main()
{
	int arr[10]={2,4,51,1,7,86,3,9,13,45};
	int i=0,j;
	int tem;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(arr[i]>arr[j])
			{
				tem=arr[j];
				arr[j]=arr[i];
				arr[i]=tem;
			}
		}
	}
	for(i=0;i<10;i++)
	{
		printf("%d\t",arr[i]);
	}
	return 0;
}


////√∞≈›À„∑®…˝–Ú
//int main()
//{
//	int arr[10]={2,4,51,1,7,86,3,9,13,45};
//	int i=0,j;
//	int tem;
//	for(i=0;i<10;i++)
//	{
//		for(j=0;j<10-i;j++)
//		{
//			if(arr[j-1]>arr[j])
//			{
//				tem=arr[j];
//				arr[j]=arr[j-1];
//				arr[j-1]=tem;
//			}
//		}
//	}
//	for(i=0;i<10;i++)
//	{
//		printf("%d\t",arr[i]);
//	}
//	return 0;
//}

