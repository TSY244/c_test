#define _CRT_SECURE_NO_WARNINGS 1


#include"game.h"

//打印菜单
void mune()
{
	printf("********************************\n");
	printf("*********     1.play    ********\n");
	printf("*********     0.exit    ********\n");
	printf("********************************\n");
}

//游戏本体框架
void game()
{
	//创建棋盘数组    
	char mine[ROWS][COLS]={0};
	char show[ROWS][COLS]={0};
	//初始化棋盘
	initboard(mine,ROWS,COLS,'0');
	initboard(show,ROWS,COLS,'*');
	//打印两个棋盘
	displayboard(show,ROW,COL);
	displayboard(mine,ROW,COL);
	//放置炸弹
	setmine(mine,ROW,COL);
	displayboard(mine,ROW,COL);
	//排查炸弹
	findmine(mine,show,ROW,COL);
}
void test()
{
	int input=0;
	srand((unsigned int)time(NULL));
	do
	{
		mune();
		printf("请选择：");
		scanf("%d",&input);
		switch(input)
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
				printf("输入错误！");
				break;
			}
		}
	}while(input);
}
int main()
{
	test();
	return 0;
}