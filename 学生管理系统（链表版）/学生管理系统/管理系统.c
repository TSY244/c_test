#define _CRT_SECURE_NO_WARNINGS 1



//头文件
#include<string.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define count1 2//定义班级的人数
#define count2 1//定义学科个数
#define score 60//定义及格线




//结构体
//出生日期
struct date_of_birth
{
	int day;
	int month;
	int year;

};



//学生信息
typedef struct STUDENT
{
	char number[100];
	char name[5];
	char gender[5];
	int grade[count2];
	struct date_of_birth birth;
	struct STUDENT* next;
}stu, * pstu;

//函数声明
void menu();//菜单
void keydown();//主体函数
pstu stu_creat();//创建学生信息
void all_stu_infom();//打印所有学生信息
void search();//寻找学生
void display(pstu a);//打印学生信息
void averageScore();//计算平均值
void pass_rate();//计算及格率
void comparemin();//找出年龄最小的
int stu_storage();//学生信息存储
void delete();//通过学号删除
void destory();//内存释放

//head结点
//pstu head;
pstu head;


int main()
{
	head = (pstu)malloc(sizeof(stu));
	head->next = NULL;
	keydown(head);
	return 0;
	////学生信息的创建
	//head = stu_creat();
	//search(head);
	//averageScore(head);
	//comparemin(head);
	//destory(head);
	//return 0;
}

//菜单制作
void menu()
{
	printf("欢迎使用学生管理系统！\n出品人：chg\n");
	printf("\n\n--------0.退出系统--------\n");
	printf("--------1.录入学生信息--------\n");
	printf("--------2.查看所有学生信息--------\n");
	printf("--------3.通过姓名查找学生--------\n");
	printf("--------4.统计输出平均成绩--------\n");
	printf("--------5.计算及格率--------\n");
	printf("--------6.找出年纪最小的学生--------\n");
	printf("--------7.学生信息存储--------\n");
	printf("--------8.学生信息导入--------\n");
	printf("--------9.学生信息删除--------\n");
	printf("请选择:");
	
}
//通过学号
void delete()
{
	pstu move1=NULL;
	pstu move2 = NULL;
	pstu move3 = NULL;
	move1 = head;
	move2 = head->next;
	char arr[30];
	printf("******现在导入学生信息******\n");
	printf("请输入想要删除人的学号：");
	scanf("%s", arr);

	if (head->next == NULL)
	{
		printf("暂无数据！\n");
	}

	while (move2 != NULL)
	{
		move3 = move2->next;
		if (strcmp(arr, move2->number) == 0)
		{
			move1->next = move3;
		}
		move1 = move2;
		move2 = move3;
	}
	printf("删除中................\n");
	Sleep(1000);
	printf("删除成功！\n");
}


//读取已有的学生信息

int stu_search()
{
	int i,stu_count = 0;;
	FILE* pr = NULL;
	pr = fopen("stu_inf.txt","r");
	pstu s = NULL;
	pstu move = head;
	printf("******Now import the student information******\n");
	while (feof(pr)==0)
	{
		stu_count++;
		s = (pstu)malloc(sizeof(stu));
		s->next = NULL;
		fscanf(pr, "%d", &stu_count);
		int a = fscanf(pr, "%s", s->number);
		fscanf(pr, "%s", s->name);
		fscanf(pr, "%s ", s->gender);
		fscanf(pr, "%d %2d %2d ", &s->birth.year, &s->birth.month, &s->birth.day);
		for (i = 1; i <= count2; i++)
		{
			fscanf(pr, "%d %4d",& i , &s->grade[i-1]);
		}
		move->next = s;
		move = s;
	}
	fclose(pr);
	pr = NULL;
	printf("******over******\n");
	return 0;
}



//学生信息存储
int stu_storage()
{
	pstu move=NULL;
	move = head->next;
	FILE* pr = NULL;
	int i = 0;//科目数
	int stu_count;
	pr = fopen("stu_inf.txt", "w");
	printf("******现在储存学生信息******\n");
	if (pr == NULL)
	{
		perror("fopen:");
		return 1;
	}
	while (move!=NULL)
	{
		stu_count = 1;
		fprintf(pr, "%d ",stu_count);
		fprintf(pr,"%s ", move->number);
		fprintf(pr,"%s ", move->name);
		fprintf(pr,"%s ", move->gender);
		fprintf(pr,"%d %d %d ", move->birth.year, move->birth.month, move->birth.day);
		for (i = 0; i < count2; i++)
		{
			fprintf(pr," %d %d", i + 1, move->grade[i]);
		}
		move = move->next;
	}
	//文件的关闭
	fclose(pr);
	pr = NULL;
	printf("存储中................\n");
	Sleep(1000);
	printf("******存储完成！******\n");
	return 0;
}


//主体运行函数

void keydown()
{
	int choose;
	do
	{
		menu();
		scanf("%d", &choose);
		switch (choose)
		{
		case 0:
			{
				printf("退出成功！\n");
				break;
			}
		case 1:
			{
				head = stu_creat();
				break;
			}
		case 2:
			{
				all_stu_infom();
				break;
			}
		case 3:
			{
				search();
				break;
			}
		case 4:
			{
				averageScore();
				break;
			}
		case 5:
			{
				pass_rate();
				break;
			}
		case 6:
		{
			comparemin();
			break;
		}
		case 7:
		{
			stu_storage();
			break;
		}
		case 8:
		{
			stu_search();
			break;
		}
		case 9:
		{
			delete();
			break;
		}
		default:
		{
			printf("输入错误，请重新输入：");
			break;
		}
		}
	} while (choose);
}

//所有学生信息
void all_stu_infom()
{
	
	while (1)
	{
		if (head->next == NULL)
		{
			printf("请输入学生信息!\n");
			break;
		}
		pstu move = NULL;
		move = head->next;
		while (move != NULL)
		{
			display(move);
			move = move->next;
		}
		if (move == NULL)
		{
			break;
		}
	}
}



//学生信息的创建
pstu stu_creat()
{
	int j;
	int ret = 0;
	int count;
	pstu p = NULL, s = NULL;

	printf("******现在创建学生信息******\n");


	printf("请输入学生信息\n");
	printf("是否输入学生信息\n1.contine 0. exit\n");
	scanf("%d", &ret);
	count = 1;
	while (1)
	{
		if (ret == 0)
		{
			break;
		}
		s = (pstu)malloc(sizeof(stu));
		s->next = NULL;
		printf("请依次输入学生资料：\n");
		printf("number:");
		scanf("%s", &s->number);
		printf("name:");
		scanf("%s", &s->name);
		printf("gender:");
		while (1)
		{
			scanf("%s", &s->gender);
			if (strcmp(s->gender, "man") == 0 || strcmp(s->gender, "woman") == 0)
			{
				break;
			}
			else
			{
				printf("输入错误，请重新输入：");
			}
		}
		printf("请依次输入出生日期：\n");
		printf("year:");
		while (1)
		{
			scanf("%d", &s->birth.year);
			if ((s->birth.year) > 0 && (s->birth.year) < 2022)
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
			scanf("%d", &s->birth.month);
			if ((s->birth.month) > 0 && (s->birth.month) < 13)
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
			scanf("%d", &s->birth.day);
			if ((s->birth.day) > 0 && (s->birth.day) < 32)
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
			printf("请输入第%d个成绩:", j + 1);
			scanf("%d", &s->grade[j]);
		}
		printf("1.contine 0. exit\n");
		scanf("%d", &ret);
		if (count == 1)
		{
			head->next = s;
		}
		else
		{
			p->next = s;
		}
		count++;
		p = s;
		if (ret == 0)
		{
			s->next = NULL;
			break;
		}
	}
	return head;
}


//打印学生信息


void display(pstu stu)
{
	while (1)
	{
		printf("******现在是打印所有学生信息模块******\n");

		if (head->next == NULL)
		{
			printf("请输入学生信息\n");
			break;
		}


		int i = 0;
		printf("学号为：%s\t", stu->number);
		printf("姓名为：%s\t", stu->name);
		printf("性别为：%s\t", stu->gender);
		printf("出生日期为：%d年%2d月%2d日\n", stu->birth.year, stu->birth.month, stu->birth.day);
		for (i = 0; i < count2; i++)
		{
			printf("第%d科成绩:%4d\t\n\n", i + 1, stu->grade[i]);
		}
		if (i == count2)
			break;
	}
}


//查找学生
//检查
void search()
{
	int a = 0;
	char tem[10] = { 0 };
	getchar();

	while (1)
	{


		printf("******现在是通过姓名查找学生******\n");


		if (head->next== NULL)
		{
			printf("请输入学生信息\n");
			break;
		}
		
		pstu move = head;
		printf("请输入学生姓名：\n");
		//fgets(tem->name, sizeof(tem->name), stdin);
		/*gets(&tem->name);*/
		scanf("%s", tem);
		while (move != NULL)
		{
			if (strcmp(tem, move->name) == 0)
			{
				display(move);
				break;
			}
			move = move->next;
		}
		if (move == NULL)
		{
			printf("查无此人！\n");
		}
		printf("是否继续输入？\n1.contine\t0.exit\n");
		scanf("%d", &a);
		if (a == 0)
		{
			break;
		}

	}
}


//计算平均成绩



void averageScore()
{
	int a = 0;//判断是否计算平均数
	int b = 0;//哪一个学科
	int sum = 0;//计算和;
	int n = 0;//第n个学生
	int c = 0;//及格的人数
	int d = 0;
	pstu move = NULL;
	move = head->next;


	
	while (1)
	{
		printf("******现在是计算平均成绩！******\n");


		if (head->next == NULL)
		{
			printf("请输入学生信息\n");
			break;
		}

		printf("\n\n是否计算该班的平均分数?\n1.计算\t0.退出\n");
		do
		{

			
			scanf("%d", &a);

			switch (a)
			{
			case 1:
			{
				printf("请选择第几科？现在有%d科\n", count2);
				scanf("%d", &b);
				for (n = 0; move != NULL; n++)
				{
					sum += move->grade[b - 1];
					move = move->next;
					d++;
				}
				printf("平均数为：%lf\n", (1.0) * sum / d);
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
		if (a == 0)
			break;
	}
	
}


//计算及格率
void pass_rate()
{
	int a = 0;//判断是否计算平均数
	int b = 0;//哪一个学科
	int n = 0;//第n个学生
	int c = 0;//及格的人数
	int d = 0;//计算人数
	pstu move = NULL;
	move = head->next;
	while (1)
	{
		printf("******现在是计算及格率******\n");

		if (head->next == NULL)
		{
			printf("请输入学生数据\n");
			break;
		}
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
				for (n = 0; move != NULL; n++)
				{
					if (move->grade[b - 1] > score)
					{
						c++;
					}
					d++;
					move = move->next;
				}
				printf("及格率为%.2lf\n", (1.0) * c / d);
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
		if(a==0)
		{
			break;
		}

	}
	
}




//找出最小的学生
void comparemin()
{
	pstu move1 = head;
	pstu move2 = head->next;
	pstu min = NULL;
	int n = 0;
	while (1)
	{
		printf("******现在是找出最小的学生******\n");
		if (head->next == NULL)
		{
			printf("请输入学生数据\n");
			break;
		}
		while (move2->next != NULL && move1->next != NULL)
		{
			move1 = move2;
			move2 = move2->next;

			if (move1->birth.year > move2->birth.year)
			{
				min = move2;
			}
			else if (move1->birth.year < move2->birth.year)
			{
				min = move1;
			}
			else
			{
				if (move1->birth.month > move2->birth.month)
				{
					min = move2;
				}
				else if (move1->birth.month < move2->birth.month)
				{
					min = move1;
				}
				else
				{
					if (move1->birth.day > move2->birth.day)
					{
						min = move2;
					}
					else if (move1->birth.day < move2->birth.day)
					{
						min = move1;
					}
				}
			}
		}
		if (move2->next == NULL)
		{
			min = move2;
		}
		printf("找到了，最小的人是\n");
		display(min);
		break;
	}
	
}




//内存释放

void destory()
{
	pstu move1 = head;
	pstu move2 = head;

	while (move2 != NULL)
	{
		move1 = move2;
		move2 = move2->next;
		free(move1);
	}
}