#include"game.h"

//初始化棋盘
void InitBoard(char arr[row][col], int ROW,int COL)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			arr[i][j] = ' ';
		}
	}
}
//打印棋盘
void display(char board[row][col], int ROW, int COL)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		printf("\n");
		for (j = 0; j < col; j++)
		{
			printf(" %c ",board[i][j]);
			if (j < col - 1)
			{
				printf("|");
			}
			else if (j = col - 1)
			{
				printf("\n");
			}
		}
		if (i < row - 1)
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
				{
					printf("|");
				}
			}
		}
	}
	printf("\n");
}
//一号玩家
void fistplayermove(char board[row][col], int ROW, int COL)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("规模为%d*%d\n", row, col);
		printf("一号玩家走,请输入：\n");
		scanf("%d%d", &x, &y);
		if (x > 0 && x <= row && y > 0 && y <= col)
		{
			if (board[x-1][y-1] == ' ')
			{
				board[x-1][y-1] = '*';
				break;
			}
			else
			{
				printf("该子已占！\n");
			}
		}
		else
		{
			printf("输入坐标错误！\n");
		}
	}
	

}
////二号玩家
//void secondplayermove(char board[row][col], int ROW, int COL)
//{
//	int x = 0;
//	int y = 0;
//	while (1)
//	{
//		printf("二号玩家走,请输入：\n");
//		printf("规模为%d*%d\n", row,col);
//		scanf("%d%d", &x, &y);
//		if (x > 0 && x <= row && y > 0 && y <= col)
//		{
//			if (board[x - 1][y - 1] == ' ')
//			{
//				board[x - 1][y - 1] = '#';
//				break;
//			}
//			else
//			{
//				printf("该子已占！\n");
//			}
//		}
//		else
//		{
//			printf("输入坐标错误！\n");
//		}
//	}
//
//
//}

void computermove(char board[row][col], int ROW, int COL)
{
	int x = 0;
	int y = 0;
	printf("电脑走：");
	while (1)
	{
		x = rand(srand) % ROW;
		y = rand(srand) % COL;
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
		
	}
}
//判断输赢
//return *,player win
//return #,computer win
//return 'd',draw
//return 'c',continue
int isfull(char board[row][col], int ROW, int COL)
{
	int i = 0, j = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}
char iswin(char board[row][col],int ROW,int COL)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ROW; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] &&board[i][1]!=' ')
		{
			return board[i][0];
		}
	}
	for (j=0;j<COL;j++)
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ')
		{
			return board[0][j];
		}
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
	{
		return board[1][1];
	}
	else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
	{
		return board[1][1];
	}
	if (1 == isfull(board, row, col))
	{
		return 'd';
	}
	return 'c';
}