#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>


int main()
{
	char ch;
	int letters=0,numbers=0,space=0,others=0;
	printf("ÇëÊäÈë×Ö·û´®£º");
	while('\n'!=(ch=getchar()))
	{
		if(ch>='0'&&ch<='9')
			numbers++;
		else if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
			letters++;
		else if(' '==ch)
			space++;
		else
			others++;

	}
	printf("letters=%d\nnumbers=%d\nspace=%d\nothers=%d",letters,numbers,space,others);
	return 0;
}
