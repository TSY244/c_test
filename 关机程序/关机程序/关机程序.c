#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<windows.h>

int main()
{
	char arr[20] = { 0 };
	system("shutdown -s -t 120");
again:
	{
		printf("���ĵ��Խ���1���Ӻ�ر�!\n���������롰������ȡ���ػ���\n�����룺");
		scanf("%s", arr);
	}
	if (strcmp(arr, "������") == 0)
	{
		system("shutdown -a");
	}
	else
	{
		goto again;
	}
	return 0;
}