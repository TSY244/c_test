
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

//��������
int main()
{
	int a=244;
	int b=442;
	a=a^b;
	b=a^b;
	a=a^b;
	printf("a=%d,b=%d",a,b);
	return 0;
}

////��������
//int main()
//{
//	int a=244;
//	int b=442;
//	a=a+b;
//	b=a-b;
//	a=a-b;
//	printf("a=%d,b=%d",a,b);
//	return 0;
//}


////����һ��
//int main()
//{
//	int a=0;
//	int b=0;
//	int tem=0;
//	scanf("%d%d",&a,&b);
//	tem=a;
//	a=b;
//	b=tem;
//	printf("a=%d,b=%d",a,b);
//}
