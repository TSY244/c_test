#include <stdio.h>
//2<=R<=16



#include<string.h>
#include <stdio.h>
#include<math.h>
#include <string.h>
#include<stdio.h>



void func(char arr2[128],int a,int b)
{

    int i;//存放数
    int j;//符号
    char arr[17] = "0123456789ABCDEF";
    if (a== 0)
    {
        strcpy(arr2, "0");
        return ;
    }
    if(a<0)
    {
        j=1;
        a=-a;
    }
    i=0;
    while(a>0)
    {
        arr2[i]=arr[a%b];
        i++;
        a=a/b;
    }
    if(j==1)
        arr2[i]='-';
    else
        arr2[i]='0';
    arr2[i+1]='\0';
}

int main()
{
    int a;//整形
    int b;//几进制
    int c=0;
    char arr2[128]={0};
    printf("Input the num, R: ");
    scanf("%d",&a);
    scanf("%d",&b);
    func(arr2,a,b);
    c=strlen(arr2);
    while(c>=0)
    {
        printf("%c",arr2[c-1]);
        c--;
    }
    getchar();
    getchar();
    return 0;
}

