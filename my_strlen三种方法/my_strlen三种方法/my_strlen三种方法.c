#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
//��������
//int my_strlen(char * arr)
//{
//	int count;
//	for(count=0;arr[count]!='\0';count++)
//	{
//		;
//	}
//	return count;
//}

//�����ݹ鷨
//int my_strlen(char* arr)
//{
//	char* len=arr;
//	if(*len!='\0')
//	{
//		return 1+my_strlen(len+1);
//	}
//	else 
//	{
//		return 0;
//	}
//}


//ָ�뷨
int my_strlen(char *str)
{
	char* str2=str;
	for(;*str!='\0';str++)
	{
		;
	}
	return str-str2;

}



int main()
{
	char arr[]="chgchgchgtsy";
	int count=my_strlen(arr);
	printf("%d\n",count);
	return 0;
}