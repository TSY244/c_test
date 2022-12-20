
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
void Conv(char* p);
int main()
{
	char str[64];

	gets(str);
	Conv(str);
	printf("After changing:   %s", str);
	return 0;
}


/* 请在这里填写答案 */

void Conv(char* p)
{
	int flag = 1;

	while (*p != '\0')
	{
		if ((*p >= 'a' && *p <= 'z' && flag == 1)) {
			*p = *p - 'a' + 'A';
			flag = 0;
		}
		if (*p == ' ')
			flag = 1;
		p++;
	}
}
