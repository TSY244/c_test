#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2

//设置炸弹的个数
#define easy_count 80


//函数的声明：
void initboard(char board[ROWS][COLS],int rows,int cols,char set);//初始化
void displayboard(char board[ROWS][COLS],int row,int col);//打印棋盘信息
void setmine(char mine[ROWS][COLS],int row,int col);//安置炸弹
void findmine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col);//排查棋盘
