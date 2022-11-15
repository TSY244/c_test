#include"root.h"





//计算均差
double MeanScore(stu* stu1)
{
	return 0;
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
	printf("请输入姓名：");
	scanf("%d", &stu1->name);
	printf("输入数学成绩：");
	scanf("%d", &stu1->grade[0]);
	printf("输入英语成绩：");
	scanf("%d", &stu1->grade[1]);
	printf("输入物理成绩：");
	scanf("%d", &stu1->grade[2]);
	printf("输入化学成绩：");
	scanf("%d", &stu1->grade[3]);
	printf("输入语文成绩：");
	scanf("%d", &stu1->grade[4]);
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