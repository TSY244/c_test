#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#define row 3
#define col 3

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void InitBoard(char arr[row][col], int ROW, int COL);//初始化棋盘
void display();//打印棋盘
void fistplayermove(char arr[row][col], int ROW, int COL);//一号玩家下棋；
void secondplayermove(char board[row][col], int ROW, int COL);//二号玩家下棋；
void computermove(char board[row][col], int ROW, int COL);//电脑下棋
char iswin(char board[row][col], int ROW, int COL);//判断输赢
int isfull(char board[row][col], int ROW, int COL);//判断平局

