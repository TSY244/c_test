#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<windows.h>

int main()
{
	char arr1[] = "##################################";
	char arr2[] = "####  chg   chg   chg   chg   ####";
	int right = 0;
	int left = 0;
	right = sizeof(arr1) / sizeof(arr1[0]) - 1;
	while (left <=right)
	{
		printf("%s", arr1);
		arr1[right] = arr2[right];
		arr1[left] = arr2[left];
		right--;
		left++;
		Sleep(500);
		system("cls");
	}
	return 0;
}