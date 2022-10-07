#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void game()
{
	int b = 0, c = 0, d = 0, e = 100, i = 1;
	printf("欢迎进入猜数字游戏！\n请输入数字：");
	c = rand(srand) % 100 + 1;
	while (c<101)
	{
		scanf("%d", &b);
		if (b == c)
		{
			printf("恭喜你找对了！\n一共用了%d次！\n",i);
			if (i == 1)
			{
				printf("天选之子！");
			}
			else if (i < 3 && i != 1)
			{
				printf("很厉害了！！");
			}
			else if (i >= 3 && i < 7)
			{
				printf("哈哈，不太行！");
			}
			else if (i >= 7)
			{
				printf("你真的不行啊！！！！！！！！");
			}
			break;
		}
		else if (b > c)
		{
			printf("猜大了！\n");
			e = b;
			printf("范围为%d--%d\n小垃圾还没猜对呢！\n", d, e);
			i++;
		}
		else if (b < c)
		{
			printf("猜小了！\n");
			d = b;
			printf("范围为%d--%d\n多踩点屎加点运气!\n", d, e);
			i++;
		}
		printf("重新输入吧，哈哈：");
	}
}
void menu()
{
	printf("\n********************************\n");
	printf("******  1.play   0.exit  *******\n");
	printf("********************************\n");
}
int main()
{
	int a = 0;
	srand((unsigned int)time(NULL));
	
	do
	{ 
		menu();
		printf("请选择：");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
		{
			game();
			break;
		}
		case 0:
		{
			printf("退出游戏！");
			break;
		}
		default:
		{
			printf("输入错误!");
			break;
		}
		}
	} while (a);
	return 0;
}