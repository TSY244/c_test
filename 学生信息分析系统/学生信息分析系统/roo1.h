#pragma once

#pragma once
#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>

typedef struct stu_information
{
	char name[10];
	int grade[5];
}stu;


//��������
void get_stu(stu* stu1);//�õ�ѧ����Ϣ
void menu();//�˵�����
void func();//���庯��
double average_value(stu* stu1);//����ƽ��ֵ
double MeanScore(stu* stu1);//�������