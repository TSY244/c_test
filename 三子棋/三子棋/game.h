#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#define row 3
#define col 3

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void InitBoard(char arr[row][col], int ROW, int COL);//��ʼ������
void display();//��ӡ����
void fistplayermove(char arr[row][col], int ROW, int COL);//һ��������壻
void secondplayermove(char board[row][col], int ROW, int COL);//����������壻
void computermove(char board[row][col], int ROW, int COL);//��������
char iswin(char board[row][col], int ROW, int COL);//�ж���Ӯ
int isfull(char board[row][col], int ROW, int COL);//�ж�ƽ��

