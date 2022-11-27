#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<windows.h>

int main()
{
	char arr[20] = { 0 };
	system("shutdown -s -t 120");
again:
	{
		printf("您的电脑将在1分钟后关闭!\n您可以输入“我是猪”取消关机！\n请输入：");
		scanf("%s", arr);
	}
	if (strcmp(arr, "我是猪") == 0)
	{
		system("shutdown -a");
	}
	else
	{
		goto again;
	}
	return 0;
}