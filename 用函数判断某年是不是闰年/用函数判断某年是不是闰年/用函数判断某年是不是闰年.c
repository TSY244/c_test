#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int is_leap_year(int A)
{
	if ((A % 4 == 0 && A % 100 != 0) || A % 400 == 0)
	{
		return 1;
	}
	else
		return 0;
}
int main()
{
	int year = 0, ret = 0;
	scanf("%d", &year);
	ret = is_leap_year(year);
	if (1 == ret)
	{
		printf("%d该年是闰年！", year);
	}
	else
	{
		printf("%d不是闰年！",year);
	}
	return 0;
}