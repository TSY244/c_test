
#include<stdio.h>


union text
{
	int a;
	char b;
};

int main()
{
	union text c;
	c.a = 1;
	if (c.b == 1)
		printf("С����");
	else
		printf("�����");
	return 0;
}

//ָ�뷨
//int main()
//{
//	int a=1;
//	char* p = (char*) & a;
//	if (*p == 1)
//		printf("С����");
//	else
//		printf("�����");
//
//	return 0;
//}