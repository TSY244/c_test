#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>

void my_strcpy(char* dest,const char *scr)
{
	assert(*dest!=NULL);
	assert(*scr!=NULL);
	while(*dest++=*scr++){}
}

int main()
{
	char arr1[20]="chgchgchgchg";
	char arr2[]="tsytsytsy";
	printf("%s\n",arr1);
	my_strcpy(arr1,arr2);
	printf("%s\n",arr1);
	return 0;
}