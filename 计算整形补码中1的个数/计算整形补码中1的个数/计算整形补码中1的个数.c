#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{
	int num=0,i=0,count=0;
	scanf("%d",&num);
	for(i=0;i<32;i++)//32是因为，int 类型4个字节，每个字节8个字符,所以存储a有32位2进制
	{
		if(1==((num=num>>i)&1))
		{
			count++;
		}
	}
	printf("%d补码中有%d个1\n",num,count);
	return 0;
}
