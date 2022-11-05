#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
int  binary_search(int arr[], int x, int y)
{
	int left = 0;
	int right = y;
	int mid = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if(arr[mid] > x)
		{
				right = mid - 1;
		}
		else if (arr[mid] < x)
		{
		left = mid + 1;
		}
		else if (arr[mid] == x)
		{
		return mid;
		}
	}
	return 0;
}
int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18,19,20 };
	int a = 0, b = 0;
	int sz = sizeof(arr) / sizeof(arr[0]) - 1;
	scanf("%d", &a);
	b = binary_search(arr,a,sz);
	
	if(0==b)
	{
		printf("没找到！");
	}
	else
	{
		printf("找到了！下标为%d", b);
	}
	return 0;
}