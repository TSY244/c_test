#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2

//����ը���ĸ���
#define easy_count 80


//������������
void initboard(char board[ROWS][COLS],int rows,int cols,char set);//��ʼ��
void displayboard(char board[ROWS][COLS],int row,int col);//��ӡ������Ϣ
void setmine(char mine[ROWS][COLS],int row,int col);//����ը��
void findmine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col);//�Ų�����
