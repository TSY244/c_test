#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
int main()
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18,19,20};
	int a = 0;
	int left = 0;
	int right = 0;
	int mid = 0;
	right = sizeof(arr) / sizeof(arr[0]) - 1;
	printf("请输入该数字：");
	scanf("%d", &a);
	while (left <= right)
	{
		mid = (right + left) / 2;
		if (arr[mid] == a)
		{
			printf("找到了！\n下标为%d", mid);
			break;
		}
		else if (arr[mid] > a)
		{
			right = mid-1;
		}
		else if (arr[mid] < a)
		{
			left = mid+1;
		}
	}
	if (left > right)
	{
		printf("无该数！");
	}

	return 0;
}