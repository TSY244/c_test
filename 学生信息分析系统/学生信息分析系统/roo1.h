#pragma once

#pragma once
#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>

typedef struct stu_information
{
	char name[10];
	int grade[5];
}stu;


//函数声明
void get_stu(stu* stu1);//得到学生信息
void menu();//菜单函数
void func();//主体函数
double average_value(stu* stu1);//计算平均值
double MeanScore(stu* stu1);//计算均差