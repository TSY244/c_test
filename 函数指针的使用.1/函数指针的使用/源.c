#include<stdio.h>

int sum(int a,int b)
{
	return a + b;
}

int min(int a,int b)
{
	return a > b ? a : b;
}
int max(int a, int b)
{
	return a < b ? a : b;
}
void print(int (*p)(int, int), int a, int b)
{
	printf("\n%d\n", (*p)(a, b));
	printf("%d\n", p(a, b));
}

void func(int a, int b)
{
	//void (*p_print)(int(*)(int, int), int, int) = print;
	
}


int main()
{
	void (*p_print)(int(*)(int, int), int, int) = print;
	p_print(min, 3, 4);
	return 0;
}