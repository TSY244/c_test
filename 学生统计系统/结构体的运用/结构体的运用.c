#define _CRT_SECURE_NO_WARNINGS 1


#define count1 2//定义班级的人数
#define count2 4//定义学科个数
#define score 60//定义及格线

#include<stdio.h>
void display(struct STUDENT* stu);

enum gender
{
	man = 0,
	woman = 1
};

//出生日期
struct date_of_birth
{
	int day;
	int month;
	int year;

};



//学生信息
struct STUDENT
{
	int number[100];
	char name[5];
	char gender[3];
	int grade[count2];
	struct date_of_birth;
};

//录入数据：
void input(struct STUDENT *stu,struct date_of_birth *DOB)
{
	int j = 0;
	printf("请依次输入学生资料：\n");
	printf("number:");
	scanf("%s", &(stu->number));
	printf("name:");
	scanf("%s", &stu->name);
	printf("gender:");
	while (1)
	{
		scanf("%s", &stu->gender);
		if (strcmp(stu->gender, "man") == 0 || strcmp(stu->gender, "woman") == 0)
		{
			break;
		}
		else
		{
			printf("输入错误，请重新输入：");
		}
	}
	printf("请依次输入出生日期：");
	printf("year:");
	while (1)
	{
		scanf("%d", &stu->year);
		if ((stu->year) > 0 && (stu->year) < 2022)
		{
			break;
		}
		else
		{
			printf("输入错误，请重新输入：");
		}
	}
	printf("month:");
	while (1)
	{
		scanf("%d", &stu->month);
		if ((stu->month) > 0 && (stu->month) < 13)
		{
			break;
		}
		else
		{
			printf("输入错误，请重新输入：");
		}
	}
	printf("day:");
	while (1)
	{
		scanf("%d", &stu->day);
		if ((stu->day) > 0 && (stu->day) < 32)
		{
			break;
		}
		else
		{
			printf("输入错误，请重新输入：");
		}
	}

	for (j = 0; j < count2; j++)
	{
		printf("请输入第%d个成绩:", j+1);
		scanf("%d", &stu->grade[j]);
	}
}

//打印学生信息
void display(struct STUDENT *stu)
{
	int i = 0;
	printf("学号为：%s\t", (stu->number));
	printf("姓名为：%s\t", stu->name);
	printf("性别为：%s\t", stu->gender);
	printf("出生日期为：%d年%2d月%2d日\n", stu->year, stu->month, stu->day);
	for (i = 0; i < count2; i++)
	{
		printf("第%d科成绩:%4d\t", i+1, stu->grade[i]);
	}

}


//检查
void search(struct STUDENT *tem,struct	STUDENT *stu)
{
	int i = 0;
	int a = 0;
	printf("请输入学生姓名：");
	getchar();
	while (1)
	{
		//fgets(tem->name, sizeof(tem->name), stdin);
		gets(&tem->name);
		for (i = 0; i < count1; i++)
		{
			if (strcmp(tem->name, stu[i].name) == 0)
			{
				display(&stu[i]);
				a = 1;
			}
		}
		if (i==count1)
		{
			printf("输入错误,请重新输入:");
		}
		if (a)
		{
			break;
		}
	}
}

//计算平均成绩

void averageScore(struct STUDENT *stu )
{
	int a = 0;//判断是否计算平均数
	int b = 0;//哪一个学科
	double sum = 0;//计算和;
	int n = 0;//第n个学生
	int c = 0;//及格的人数
	printf("\n\n是否计算该班的平均分数?\n1.计算\t0.退出\n");
	do
	{
		scanf("%d", &a);

		switch (a)
		{
		case 1:
		{
			printf("请选择第几科？现在有%d科\n",count2);
			scanf("%d",&b);
			for (n = 0; n < count1; n++)
			{
				sum += stu[n].grade[b];
			}
			printf("平均数为：%lf", sum / count1);
			a = 0;
			break;
		}
		case 0:
		{
			break;
		}
		default:
		{
			printf("输入错误，请重新输入：");
			break;
		}
		}
	} while (a);
	do
	{
	printf("\n\n是否计算该班的及格率?\n1.计算\t0.退出\n");
	scanf("%d", &a);
	switch (a)
	{
	case 1:
	{
		printf("请选择第几科？现在有%d科\n", count2);
		scanf("%d", &b);
		for (n = 0; n < count1; n++)
		{
			if (stu[n].grade > score)
			{
				c++;
			}
		}
		printf("及格率为%.2lf\n",c/count1);
		a = 0;
		break;
	}
	case 0:
	{
		break;
	}
	default:
	{
		printf("输入错误，请重新输入：");
		break;
	}
	}
	} while (a);
}


//找出最小的学生
void comparemin(struct STUDENT* stu)
{
	struct STUDENT min;
	int n = 0;
	for (n = 0; n+1 < count1; n++)
	{
		if (stu[n].year > stu[n + 1].year)
		{
			min = stu[n];
		}
		else if (stu[n].year < stu[n + 1].year)
		{
			min = stu[n + 1];
		}
		else
		{
			if (stu[n].month > stu[n + 1].month)
			{
				min = stu[n];
			}
			else if (stu[n].month < stu[n + 1].month)
			{
				min = stu[n + 1];
			}
			else
			{
				if (stu[n].day > stu[n + 1].day)
				{
					min = stu[n];
				}
				else if (stu[n].day < stu[n + 1].day)
				{
					min = stu[n + 1];
				}
			}
		}
	}
	printf("\n年龄最小的是:%s\n信息如下:", min.name);
	display(&min);
}


int main()
{
	struct STUDENT stu[count1];
	struct date_of_birth birthday;

	struct STUDENT tem;//用于临时比较
	int i = 0;
	int j = 0;



	for (i = 0; i < count1 ; i++)//输入学生数据
	{
		printf("请选择%d个学生数据：\n",i+1);
		input(&stu[i],&birthday);
		printf("\n\n");
	}

	search(&tem,&stu);
	averageScore(&stu);

	comparemin(&stu);
	return 0;
}