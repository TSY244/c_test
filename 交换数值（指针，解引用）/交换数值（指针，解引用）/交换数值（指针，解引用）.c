#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>

void F(int* A, int* B)
{
	int C = 0;
	C = *B;
	*B = *A;
	*A = C;
}
int main()
{
	int a = 0, b = 0;
	scanf("%d%d", &a, &b);
	printf("a=%d   b=%d\n", a, b);
	F(&a, &b);
	printf("a=%d   b=%d\n", a, b);
	return 0;
}