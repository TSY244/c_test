#define _CRT_SECURE_NO_WARNINGS 1


#define count1 2//����༶������
#define count2 4//����ѧ�Ƹ���
#define score 60//���弰����

#include<stdio.h>
void display(struct STUDENT* stu);

enum gender
{
	man = 0,
	woman = 1
};

//��������
struct date_of_birth
{
	int day;
	int month;
	int year;

};



//ѧ����Ϣ
struct STUDENT
{
	int number[100];
	char name[5];
	char gender[3];
	int grade[count2];
	struct date_of_birth;
};

//¼�����ݣ�
void input(struct STUDENT *stu,struct date_of_birth *DOB)
{
	int j = 0;
	printf("����������ѧ�����ϣ�\n");
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
			printf("����������������룺");
		}
	}
	printf("����������������ڣ�");
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
			printf("����������������룺");
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
			printf("����������������룺");
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
			printf("����������������룺");
		}
	}

	for (j = 0; j < count2; j++)
	{
		printf("�������%d���ɼ�:", j+1);
		scanf("%d", &stu->grade[j]);
	}
}

//��ӡѧ����Ϣ
void display(struct STUDENT *stu)
{
	int i = 0;
	printf("ѧ��Ϊ��%s\t", (stu->number));
	printf("����Ϊ��%s\t", stu->name);
	printf("�Ա�Ϊ��%s\t", stu->gender);
	printf("��������Ϊ��%d��%2d��%2d��\n", stu->year, stu->month, stu->day);
	for (i = 0; i < count2; i++)
	{
		printf("��%d�Ƴɼ�:%4d\t", i+1, stu->grade[i]);
	}

}


//���
void search(struct STUDENT *tem,struct	STUDENT *stu)
{
	int i = 0;
	int a = 0;
	printf("������ѧ��������");
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
			printf("�������,����������:");
		}
		if (a)
		{
			break;
		}
	}
}

//����ƽ���ɼ�

void averageScore(struct STUDENT *stu )
{
	int a = 0;//�ж��Ƿ����ƽ����
	int b = 0;//��һ��ѧ��
	double sum = 0;//�����;
	int n = 0;//��n��ѧ��
	int c = 0;//���������
	printf("\n\n�Ƿ����ð��ƽ������?\n1.����\t0.�˳�\n");
	do
	{
		scanf("%d", &a);

		switch (a)
		{
		case 1:
		{
			printf("��ѡ��ڼ��ƣ�������%d��\n",count2);
			scanf("%d",&b);
			for (n = 0; n < count1; n++)
			{
				sum += stu[n].grade[b];
			}
			printf("ƽ����Ϊ��%lf", sum / count1);
			a = 0;
			break;
		}
		case 0:
		{
			break;
		}
		default:
		{
			printf("����������������룺");
			break;
		}
		}
	} while (a);
	do
	{
	printf("\n\n�Ƿ����ð�ļ�����?\n1.����\t0.�˳�\n");
	scanf("%d", &a);
	switch (a)
	{
	case 1:
	{
		printf("��ѡ��ڼ��ƣ�������%d��\n", count2);
		scanf("%d", &b);
		for (n = 0; n < count1; n++)
		{
			if (stu[n].grade > score)
			{
				c++;
			}
		}
		printf("������Ϊ%.2lf\n",c/count1);
		a = 0;
		break;
	}
	case 0:
	{
		break;
	}
	default:
	{
		printf("����������������룺");
		break;
	}
	}
	} while (a);
}


//�ҳ���С��ѧ��
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
	printf("\n������С����:%s\n��Ϣ����:", min.name);
	display(&min);
}


int main()
{
	struct STUDENT stu[count1];
	struct date_of_birth birthday;

	struct STUDENT tem;//������ʱ�Ƚ�
	int i = 0;
	int j = 0;



	for (i = 0; i < count1 ; i++)//����ѧ������
	{
		printf("��ѡ��%d��ѧ�����ݣ�\n",i+1);
		input(&stu[i],&birthday);
		printf("\n\n");
	}

	search(&tem,&stu);
	averageScore(&stu);

	comparemin(&stu);
	return 0;
}