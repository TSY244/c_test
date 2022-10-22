#define _CRT_SECURE_NO_WARNINGS 1


#include"game.h"

//��ʼ������
void initboard(char board[ROWS][COLS],int rows,int cols,char set)
{
	int i=0,j=0;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			   board[i][j]=set;
		}
	}
}

//��ӡ����
void displayboard(char board[ROWS][COLS],int row,int col)
{
	int i=0,j=0;
	printf(" ");
	for(i=1;i<=row;i++)
	{
		printf(" %d ",i);
	}
	printf("\n");
	for(i=1;i<=row;i++)
	{
		printf("%d",i);
		for(j=1;j<=col;j++)
		{
			printf(" %c ",board[i][j]);
		}
		printf("\n");
	}
}
//����ը��
void setmine(char mine[ROWS][COLS],int row,int col)
{
	int count=easy_count;
	while(count)
	{
		int x=rand()%row+1;
		int y=rand()%col+1;
		if(mine[x][y]=='0')
		{
			mine[x][y]='1';
			count--;
		}
	}
}

//�ų�ը��
int get_mine_count(char mine[ROWS][COLS],int x,int y)
{
	return
		mine[x-1][y]+
		mine[x-1][y-1]+
		mine[x][y-1]+
		mine[x+1][y-1]+
		mine[x+1][y]+
		mine[x+1][y+1]+
		mine[x][y+1]+
		mine[x-1][y+1]-8*'0';
}

void findmine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col)
{
	int x=0,y=0;
	int win=0;
	while(win<row*col-easy_count)
	{
		printf("�������Ų�����꣺");
		scanf("%d%d",&x,&y);
		if(x>=1&&x<=row&&y>=1&&y<=col)
		{
			if(mine[x][y]=='1')
			{
				printf("��ϲ�㱻ը����;\n");
				displayboard(mine,row,col);
				break;
			}
			else
			{
				int count=0;
				count=get_mine_count(mine,x,y);
				show[x][y]=count+'0';
				displayboard(show,ROW,COL);
				win++;
			}
		}
		else
		{
			printf("�������!\n");
		}

	}
	if(win==row*col-easy_count)
	{
		printf("ɨ�׽�����\n��ϲ�㣡\n");
	}
}