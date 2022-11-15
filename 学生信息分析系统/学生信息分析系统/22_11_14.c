
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<math.h>

typedef struct stu_information
{
	double grade[5];
}stu;


//函数声明
void get_stu(stu* stu1);//得到学生信息
void menu();//菜单函数
void func();//主体函数
double average_value(stu* stu1);//计算平均值
double Variance(stu* stu1);//计算均差
double Deviaion(stu* stu1);//计算离差
double Best_subject(stu* stu1);//找出最好的科目
double WorstSubjects(stu* stu1);//寻找最差的科目



int main()
{
	stu stu1={0};
	get_stu(&stu1);//得到学生信息
	func(&stu1);
	return 0;
}

//主体函数
void func(stu* stu1)
{
	int a = 0;//用于选择判断
	double b = 0;//接收平均值
	double c;//接收方差
	double d;//离差
	double e;//最好的科目成绩或者最坏de
	do
	{
		menu();
		scanf("%d", &a);
		switch (a)
		{
		case 0:
		{
			printf("退出成功！\n");
			break;
		}
		case 1:
		{
			b=average_value(stu1);
			printf("平均值为：%.4lf\n", b);
			break;
		}
		case 2:
		{
			c = Variance(stu1);
			printf("均方差为：%.4lf\n", c);
			break;
		}
		case 3:
		{
			d=Deviaion(stu1);
			printf("离差为：%.4lf\n", d);
			break;
		}
		case 4:
		{
			e=Best_subject(stu1);
			if (e == stu1->grade[0])
			{
				printf("最好的科目是数学！\n");
			}
			else if (e == stu1->grade[1])
			{
				printf("最好的科目是英语！\n");
			}
			else if (e == stu1->grade[2])
			{
				printf("最好的科目是物理！\n");
			}
			else if (e == stu1->grade[3])
			{
				printf("最好的科目是化学！\n");
			}
			else if (e == stu1->grade[4])
			{
				printf("最好的科目是语文！\n");
			}
			break;
		}
		case 5:
		{
			e=WorstSubjects(stu1);
			if (e == stu1->grade[0])
			{
				printf("最差的科目是数学！\n");
			}
			else if (e == stu1->grade[1])
			{
				printf("最差的科目是英语！\n");
			}
			else if (e == stu1->grade[2])
			{
				printf("最差的科目是物理！\n");
			}
			else if (e == stu1->grade[3])
			{
				printf("最差的科目是化学！\n");
			}
			else if (e == stu1->grade[4])
			{
				printf("最差的科目是语文！\n");
			}
			break;
		}
		default:
		{
			printf("输入错误!\n");
			break;
		}
		}
	} while (a);
}

//最差的科目
double WorstSubjects(stu*stu1)
{
	double min;//存放最小值
	int i;//循环变量
	min = stu1->grade[0];

	for (i = 0; i < 5; i++)
	{
		if (min> stu1->grade[i])
		{
			min = stu1->grade[i];
		}
	}
	return min;
}

//找出最好的科目
double Best_subject(stu* stu1)
{
	double Max;//存放最大值
	int i;//循环变量
	Max = stu1->grade[0];

	for (i = 0; i < 5; i++)
	{
		if (Max <stu1-> grade[i])
		{
			Max = stu1->grade[i];
		}
	}
	return Max;
}

//计算离差
double Deviaion(stu* stu1)
{
	int b = average_value(stu1);//平均值
	int d = 0;//返回离差
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		d = d + sqrt((stu1->grade[i] - b) * (stu1->grade[i] - b));
	}
	return d;
}




//计算均差
double Variance(stu* stu1)//b为平均值
{
	double a = 0;//接受均方差
	double b = 0;//接受平均值
	b = average_value(stu1);
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		a = a + ((stu1->grade[i] - b) * (stu1->grade[i] - b));
	}
	return a;
}

//计算平均值
double average_value(stu* stu1)
{
	double a;//计算平均值
	double sum = 0;//成绩之和
	sum = stu1->grade[0] + stu1->grade[1] + stu1->grade[2] + stu1->grade[3] + stu1->grade[4];
	return sum / 5;
}

//得到学生信息
void get_stu(stu* stu1)
{
	printf("输入数学成绩：");
	scanf("%lf", &stu1->grade[0]);
	printf("输入英语成绩：");
	scanf("%lf", &stu1->grade[1]);
	printf("输入物理成绩：");
	scanf("%lf", &stu1->grade[2]);
	printf("输入化学成绩：");
	scanf("%lf", &stu1->grade[3]);
	printf("输入语文成绩：");
	scanf("%lf", &stu1->grade[4]);
	printf("信息获取完毕\n");
}


//菜单函数
void menu()
{
	printf("-----------0.exit-----------\n");
	printf("-----------1.计算平均数-----------\n");
	printf("-----------2.均方差-----------\n");
	printf("-----------3.离差-----------\n");
	printf("-----------4.最优科目-----------\n");
	printf("-----------5.最差科目-----------\n");
	printf("请选择：");

}
