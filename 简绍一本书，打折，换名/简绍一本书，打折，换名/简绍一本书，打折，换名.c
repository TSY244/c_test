#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>

struct book
{
	char name[20];
	int price;
};
int main()
{
	struct book b1 = { "chg",520 };
	printf("%s\n", b1.name);
	printf("%d\n", b1.price);
	b1.price = 1314;
	strcpy(b1.name, "hhh");
	printf("%d\n", b1.price);
	printf("%s\n", b1.name);
	return 0;
}