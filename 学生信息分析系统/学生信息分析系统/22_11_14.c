
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<math.h>

typedef struct stu_information
{
	double grade[5];
}stu;


//��������
void get_stu(stu* stu1);//�õ�ѧ����Ϣ
void menu();//�˵�����
void func();//���庯��
double average_value(stu* stu1);//����ƽ��ֵ
double Variance(stu* stu1);//�������
double Deviaion(stu* stu1);//�������
double Best_subject(stu* stu1);//�ҳ���õĿ�Ŀ
double WorstSubjects(stu* stu1);//Ѱ�����Ŀ�Ŀ



int main()
{
	stu stu1={0};
	get_stu(&stu1);//�õ�ѧ����Ϣ
	func(&stu1);
	return 0;
}

//���庯��
void func(stu* stu1)
{
	int a = 0;//����ѡ���ж�
	double b = 0;//����ƽ��ֵ
	double c;//���շ���
	double d;//���
	double e;//��õĿ�Ŀ�ɼ������de
	do
	{
		menu();
		scanf("%d", &a);
		switch (a)
		{
		case 0:
		{
			printf("�˳��ɹ���\n");
			break;
		}
		case 1:
		{
			b=average_value(stu1);
			printf("ƽ��ֵΪ��%.4lf\n", b);
			break;
		}
		case 2:
		{
			c = Variance(stu1);
			printf("������Ϊ��%.4lf\n", c);
			break;
		}
		case 3:
		{
			d=Deviaion(stu1);
			printf("���Ϊ��%.4lf\n", d);
			break;
		}
		case 4:
		{
			e=Best_subject(stu1);
			if (e == stu1->grade[0])
			{
				printf("��õĿ�Ŀ����ѧ��\n");
			}
			else if (e == stu1->grade[1])
			{
				printf("��õĿ�Ŀ��Ӣ�\n");
			}
			else if (e == stu1->grade[2])
			{
				printf("��õĿ�Ŀ������\n");
			}
			else if (e == stu1->grade[3])
			{
				printf("��õĿ�Ŀ�ǻ�ѧ��\n");
			}
			else if (e == stu1->grade[4])
			{
				printf("��õĿ�Ŀ�����ģ�\n");
			}
			break;
		}
		case 5:
		{
			e=WorstSubjects(stu1);
			if (e == stu1->grade[0])
			{
				printf("���Ŀ�Ŀ����ѧ��\n");
			}
			else if (e == stu1->grade[1])
			{
				printf("���Ŀ�Ŀ��Ӣ�\n");
			}
			else if (e == stu1->grade[2])
			{
				printf("���Ŀ�Ŀ������\n");
			}
			else if (e == stu1->grade[3])
			{
				printf("���Ŀ�Ŀ�ǻ�ѧ��\n");
			}
			else if (e == stu1->grade[4])
			{
				printf("���Ŀ�Ŀ�����ģ�\n");
			}
			break;
		}
		default:
		{
			printf("�������!\n");
			break;
		}
		}
	} while (a);
}

//���Ŀ�Ŀ
double WorstSubjects(stu*stu1)
{
	double min;//�����Сֵ
	int i;//ѭ������
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

//�ҳ���õĿ�Ŀ
double Best_subject(stu* stu1)
{
	double Max;//������ֵ
	int i;//ѭ������
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

//�������
double Deviaion(stu* stu1)
{
	int b = average_value(stu1);//ƽ��ֵ
	int d = 0;//�������
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		d = d + sqrt((stu1->grade[i] - b) * (stu1->grade[i] - b));
	}
	return d;
}




//�������
double Variance(stu* stu1)//bΪƽ��ֵ
{
	double a = 0;//���ܾ�����
	double b = 0;//����ƽ��ֵ
	b = average_value(stu1);
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		a = a + ((stu1->grade[i] - b) * (stu1->grade[i] - b));
	}
	return a;
}

//����ƽ��ֵ
double average_value(stu* stu1)
{
	double a;//����ƽ��ֵ
	double sum = 0;//�ɼ�֮��
	sum = stu1->grade[0] + stu1->grade[1] + stu1->grade[2] + stu1->grade[3] + stu1->grade[4];
	return sum / 5;
}

//�õ�ѧ����Ϣ
void get_stu(stu* stu1)
{
	printf("������ѧ�ɼ���");
	scanf("%lf", &stu1->grade[0]);
	printf("����Ӣ��ɼ���");
	scanf("%lf", &stu1->grade[1]);
	printf("��������ɼ���");
	scanf("%lf", &stu1->grade[2]);
	printf("���뻯ѧ�ɼ���");
	scanf("%lf", &stu1->grade[3]);
	printf("�������ĳɼ���");
	scanf("%lf", &stu1->grade[4]);
	printf("��Ϣ��ȡ���\n");
}


//�˵�����
void menu()
{
	printf("-----------0.exit-----------\n");
	printf("-----------1.����ƽ����-----------\n");
	printf("-----------2.������-----------\n");
	printf("-----------3.���-----------\n");
	printf("-----------4.���ſ�Ŀ-----------\n");
	printf("-----------5.����Ŀ-----------\n");
	printf("��ѡ��");

}
