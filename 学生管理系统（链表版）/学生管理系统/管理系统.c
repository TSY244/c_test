#define _CRT_SECURE_NO_WARNINGS 1



//ͷ�ļ�
#include<string.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define count1 2//����༶������
#define count2 1//����ѧ�Ƹ���
#define score 60//���弰����




//�ṹ��
//��������
struct date_of_birth
{
	int day;
	int month;
	int year;

};



//ѧ����Ϣ
typedef struct STUDENT
{
	char number[100];
	char name[5];
	char gender[5];
	int grade[count2];
	struct date_of_birth birth;
	struct STUDENT* next;
}stu, * pstu;

//��������
void menu();//�˵�
void keydown();//���庯��
pstu stu_creat();//����ѧ����Ϣ
void all_stu_infom();//��ӡ����ѧ����Ϣ
void search();//Ѱ��ѧ��
void display(pstu a);//��ӡѧ����Ϣ
void averageScore();//����ƽ��ֵ
void pass_rate();//���㼰����
void comparemin();//�ҳ�������С��
int stu_storage();//ѧ����Ϣ�洢
void delete();//ͨ��ѧ��ɾ��
void destory();//�ڴ��ͷ�

//head���
//pstu head;
pstu head;


int main()
{
	head = (pstu)malloc(sizeof(stu));
	head->next = NULL;
	keydown(head);
	return 0;
	////ѧ����Ϣ�Ĵ���
	//head = stu_creat();
	//search(head);
	//averageScore(head);
	//comparemin(head);
	//destory(head);
	//return 0;
}

//�˵�����
void menu()
{
	printf("��ӭʹ��ѧ������ϵͳ��\n��Ʒ�ˣ�chg\n");
	printf("\n\n--------0.�˳�ϵͳ--------\n");
	printf("--------1.¼��ѧ����Ϣ--------\n");
	printf("--------2.�鿴����ѧ����Ϣ--------\n");
	printf("--------3.ͨ����������ѧ��--------\n");
	printf("--------4.ͳ�����ƽ���ɼ�--------\n");
	printf("--------5.���㼰����--------\n");
	printf("--------6.�ҳ������С��ѧ��--------\n");
	printf("--------7.ѧ����Ϣ�洢--------\n");
	printf("--------8.ѧ����Ϣ����--------\n");
	printf("--------9.ѧ����Ϣɾ��--------\n");
	printf("��ѡ��:");
	
}
//ͨ��ѧ��
void delete()
{
	pstu move1=NULL;
	pstu move2 = NULL;
	pstu move3 = NULL;
	move1 = head;
	move2 = head->next;
	char arr[30];
	printf("******���ڵ���ѧ����Ϣ******\n");
	printf("��������Ҫɾ���˵�ѧ�ţ�");
	scanf("%s", arr);

	if (head->next == NULL)
	{
		printf("�������ݣ�\n");
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
	printf("ɾ����................\n");
	Sleep(1000);
	printf("ɾ���ɹ���\n");
}


//��ȡ���е�ѧ����Ϣ

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



//ѧ����Ϣ�洢
int stu_storage()
{
	pstu move=NULL;
	move = head->next;
	FILE* pr = NULL;
	int i = 0;//��Ŀ��
	int stu_count;
	pr = fopen("stu_inf.txt", "w");
	printf("******���ڴ���ѧ����Ϣ******\n");
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
	//�ļ��Ĺر�
	fclose(pr);
	pr = NULL;
	printf("�洢��................\n");
	Sleep(1000);
	printf("******�洢��ɣ�******\n");
	return 0;
}


//�������к���

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
				printf("�˳��ɹ���\n");
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
			printf("����������������룺");
			break;
		}
		}
	} while (choose);
}

//����ѧ����Ϣ
void all_stu_infom()
{
	
	while (1)
	{
		if (head->next == NULL)
		{
			printf("������ѧ����Ϣ!\n");
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



//ѧ����Ϣ�Ĵ���
pstu stu_creat()
{
	int j;
	int ret = 0;
	int count;
	pstu p = NULL, s = NULL;

	printf("******���ڴ���ѧ����Ϣ******\n");


	printf("������ѧ����Ϣ\n");
	printf("�Ƿ�����ѧ����Ϣ\n1.contine 0. exit\n");
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
		printf("����������ѧ�����ϣ�\n");
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
				printf("����������������룺");
			}
		}
		printf("����������������ڣ�\n");
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
				printf("����������������룺");
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
				printf("����������������룺");
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
				printf("����������������룺");
			}
		}

		for (j = 0; j < count2; j++)
		{
			printf("�������%d���ɼ�:", j + 1);
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


//��ӡѧ����Ϣ


void display(pstu stu)
{
	while (1)
	{
		printf("******�����Ǵ�ӡ����ѧ����Ϣģ��******\n");

		if (head->next == NULL)
		{
			printf("������ѧ����Ϣ\n");
			break;
		}


		int i = 0;
		printf("ѧ��Ϊ��%s\t", stu->number);
		printf("����Ϊ��%s\t", stu->name);
		printf("�Ա�Ϊ��%s\t", stu->gender);
		printf("��������Ϊ��%d��%2d��%2d��\n", stu->birth.year, stu->birth.month, stu->birth.day);
		for (i = 0; i < count2; i++)
		{
			printf("��%d�Ƴɼ�:%4d\t\n\n", i + 1, stu->grade[i]);
		}
		if (i == count2)
			break;
	}
}


//����ѧ��
//���
void search()
{
	int a = 0;
	char tem[10] = { 0 };
	getchar();

	while (1)
	{


		printf("******������ͨ����������ѧ��******\n");


		if (head->next== NULL)
		{
			printf("������ѧ����Ϣ\n");
			break;
		}
		
		pstu move = head;
		printf("������ѧ��������\n");
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
			printf("���޴��ˣ�\n");
		}
		printf("�Ƿ�������룿\n1.contine\t0.exit\n");
		scanf("%d", &a);
		if (a == 0)
		{
			break;
		}

	}
}


//����ƽ���ɼ�



void averageScore()
{
	int a = 0;//�ж��Ƿ����ƽ����
	int b = 0;//��һ��ѧ��
	int sum = 0;//�����;
	int n = 0;//��n��ѧ��
	int c = 0;//���������
	int d = 0;
	pstu move = NULL;
	move = head->next;


	
	while (1)
	{
		printf("******�����Ǽ���ƽ���ɼ���******\n");


		if (head->next == NULL)
		{
			printf("������ѧ����Ϣ\n");
			break;
		}

		printf("\n\n�Ƿ����ð��ƽ������?\n1.����\t0.�˳�\n");
		do
		{

			
			scanf("%d", &a);

			switch (a)
			{
			case 1:
			{
				printf("��ѡ��ڼ��ƣ�������%d��\n", count2);
				scanf("%d", &b);
				for (n = 0; move != NULL; n++)
				{
					sum += move->grade[b - 1];
					move = move->next;
					d++;
				}
				printf("ƽ����Ϊ��%lf\n", (1.0) * sum / d);
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
		if (a == 0)
			break;
	}
	
}


//���㼰����
void pass_rate()
{
	int a = 0;//�ж��Ƿ����ƽ����
	int b = 0;//��һ��ѧ��
	int n = 0;//��n��ѧ��
	int c = 0;//���������
	int d = 0;//��������
	pstu move = NULL;
	move = head->next;
	while (1)
	{
		printf("******�����Ǽ��㼰����******\n");

		if (head->next == NULL)
		{
			printf("������ѧ������\n");
			break;
		}
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
				for (n = 0; move != NULL; n++)
				{
					if (move->grade[b - 1] > score)
					{
						c++;
					}
					d++;
					move = move->next;
				}
				printf("������Ϊ%.2lf\n", (1.0) * c / d);
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
		if(a==0)
		{
			break;
		}

	}
	
}




//�ҳ���С��ѧ��
void comparemin()
{
	pstu move1 = head;
	pstu move2 = head->next;
	pstu min = NULL;
	int n = 0;
	while (1)
	{
		printf("******�������ҳ���С��ѧ��******\n");
		if (head->next == NULL)
		{
			printf("������ѧ������\n");
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
		printf("�ҵ��ˣ���С������\n");
		display(min);
		break;
	}
	
}




//�ڴ��ͷ�

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