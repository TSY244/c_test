#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void menu()//菜单函数
{
	printf("*****************************\n");
	printf("******* 1.play  0.exit ******\n");
	printf("*****************************\n");
}
void game()
{
	//创建数组
	char board[row][col] = { 0 };
	//创建返回值
	char ret ;
	//初始化
	InitBoard(board, row, col);
	//打印
	display(board, row, col);
	//一号玩家走
	while (1)
	{
		fistplayermove(board, row, col);
		display(board, row, col);
		ret=iswin(board, row, col);
		if (ret != 'c')
		{
			break;
		}
		/*secondplayermove(board, row, col);*/
		computermove(board, row, col);
		display(board, row, col);
		ret=iswin(board, row, col);
		if (ret != 'c')
		{
			break;
		}
	}
	if (ret == '*')
	{
		printf("玩家获胜！\n");
	}
	else if (ret == '#')
	{
		printf("电脑获胜！\n");
	}
	else if(ret == 'd')
	{
		printf("平局!\n");
	}
}
void test()//运行函数
{
	srand((unsigned int)time(NULL));
	int input;
	do
	{
		menu();
		printf("请选择：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{
			printf("三子棋游戏！\n");
			game();
			break;
		}
		case 0:
		{
			printf("退出游戏！\n");
			break;
		}
		default:
		{
			printf("输入错误！\n");
			break;
		}
		}
	} while (input);
}
int main()
{
	test();
	return 0;
}