
#include<stdio.h>
#include<stdlib.h>

int main()
{
	char ch = 0;
	int count = 0;
	int i = 0;
	int* p = NULL;
	p = (int*)realloc(p, sizeof(int));
	p[0] = 0;
	while ('.' != (ch = getchar()))
	{
		if (' ' != ch)
		{
			p[count]++;
		}
		else if (' ' == ch && 0 != p[count])
		{
			p = (int*)realloc(p, (count++ + 2) * sizeof(int));
			p[count] = 0;
		}
	}
	//¥Ú”°
	while (i <= count)
	{
		if ((p[0] == 0 && count == 0) || (p[i] == 0 && i == count))
		{
			return 0;
		}

		printf("%d", p[i++]);
		if (p[i] == 0 && i == count)
		{
			break;
		}
		if ((i - 1 != count))
		{
			printf(" ");
		}

	}
	free(p);
	return 0;
}