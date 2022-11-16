#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>

typedef struct date
{
	int year;
	int month;
	int day;
}time;


//����������
int finddyear(time* year1, time* year2);//��������
void Find_old(time* time1, time* time2);//��year1����С��

int little(time* time1);//����С��
int bigger(time* time2);//������

int Find_month(time* time1, time* time2);//����ȹ��󣬼���������
int litter_month(time* time1);//����С��
int bigger_month(time* time2);//�������


//������������֮���������ע���ж�����Ƿ�Ϊ����ķ���&mdash;&mdash;Ϊ400�ı���Ϊ���꣬��2000�ꣻ����100�ı���������4�ı�����Ϊ���꣬��1996�ꡣ
int main()
{
	time time1 = { 0 };
	time time2 = { 0 };


	int sum = 0;
	//���ݵ�¼��
	printf("from the date (****/**/**):\n");
	scanf("%d/%d/%d", &time1.year, &time1.month, &time1.day);
	printf("to the date(****/**/**):\n");
	scanf("%d/%d/%d", &time2.year, &time2.month, &time2.day);


	Find_old(&time1,&time2);


	if (time1.year == time2.year && time1.month == time2.month)
	{
		sum = time2.day - time1.day;
	}
	else if (time1.year == time2.year&&time1.month!=time2.month)
	{
		sum +=	Find_month(&time1,&time2);
		sum += litter_month(&time1);
		sum += bigger_month(&time2);
	}
	else 
	{
		sum += finddyear(&time1, &time2);
		sum += little(&time1);
		sum += bigger(&time2);
	}
	//��������Ĳ��

	printf("Output:\nsum=%d\n", sum);
	return 0;
}

//��h
int bigger_month(time*time2)
{
	return time2->day;

}



//С�h
int litter_month(time* time1)
{
	int all = 0;
	int b=0;
	int a = time1->month;

	if  ((0 == (time1->year % 4) && 0 != (time1->year % 100)) || (0 == (time1->year % 400)))
	{
		switch (a)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			all += 31;
			break;
		}
		case 2:
		{
			all += 29;
			break;
		}
		default:
			all += 30;
			break;
		}
	}
	else
	{
		switch (a)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			all += 31;
			break;
		}
		case 2:
		{
			all += 28;
			break;
		}
		default:
			all += 30;
			break;
		}
	}
	return all - time1->day;
}








//����ȣ���������
int Find_month(time*time1,time*time2)
{
	int b = 0;//�е�����
	int i;//ѭ������
	if ((0 == (time1->year % 4) && 0 != (time1->year % 100)) || (0 == (time1->year % 400)))
	{
		for (i = time1->month+1; i < time2->month; i++)
		{
			switch (i)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
			{
				b += 31;
				break;
			}
			case 2:
			{
				b += 29;
				break;
			}
			default:
				b += 30;
				break;
			}
		}
	}
	else
	{
		for (i = time1->month+1; i < time2->month; i++)
		{
			switch (i)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
			{
				b += 31;
				break;
			}
			case 2:
			{
				b += 28;
				break;
			}
			default:
				b += 30;
				break;
			}
		}
	}
	return b;
}


//�������

void Find_old(time* time1, time* time2)
{
	time tem ;//�м����
	if (time1->year > time2->year)
	{
		tem = *time1;
		*time1 = *time2;
		*time2 = tem;
	}
	else if (time1->year == time2->year)
	{
		if (time1->month > time2->month)
		{
			tem = *time1;
			*time1 = *time2;
			*time2 = tem;
		}
		else if (time1->month == time2->month)
		{
			if (time1->day > time2->day)
			{
				tem = *time1;
				*time1 = *time2;
				*time2 = tem;
			}
		}
	}
}


//�������
int bigger(time* time2)
{
	int b=0;//����ֵ
	int i=0;
	if ((0 == (time2->year % 4) && 0 != (time2->year % 100)) || (0 == (time2->year % 400)))
	{
		for (i = 1; i < time2->month; i++)
		{
			switch (i)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
			{
				b += 31;
				break;
			}
			case 2:
			{
				b += 29;
				break;
			}
			default:
				b += 30;
				break;
			}
		}
	}
	else
	{
		for (i = 1; i < time2->month; i++)
		{
			switch (i)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
			{
				b += 31;
				break;
			}
			case 2:
			{
				b += 28;
				break;
			}
			default:
				b += 30;
				break;
			}
		}
	}
	b += time2->day;
	return b;
}

//����С��
int little(time*time1)
{
	int all = 0;//�ܵ�����
	int b=0;//�е�����
	int i;//ѭ������
	//�ҵ�����һ�������
	if ((0 == ((time1->year) % 4) && 0 != (time1->year % 100)) || (0 == (time1->year % 400)))
	{
		all = 366;
	}
	else
		all = 365;
	if ((0 == (time1->year % 4) && 0 != (time1->year % 100)) || (0 == (time1->year % 400)))
	{
		for (i = 1; i < time1->month; i++)
		{
			switch (i)
			{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
				{
					b += 31;
					break;
				}
				case 2:
				{
					b += 29;
					break;
				}
			default:
				b += 30;
				break;
			}
		}
	}
	else
	{
		for (i = 1; i < time1->month; i++)
		{
			switch (i)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
			{
				b += 31;
				break;
			}
			case 2:
			{
				b += 28;
				break;
			}
			default:
				b += 30;
				break;
			}
		}
	}
	b += time1->day;
	return all - b;
	
}



//������Ĳ��
int finddyear(time* time1,time* time2)
{
	int sum = 0;
	int y=0;
	for (y =(time1->year)+1 ; y < (time2->year); y++)
	{
		if ((0 == (y % 4) && 0 != (y % 100)) || (0 == (y % 400)))
		{
			sum += 366;
		}
		else
			sum += 365;
	}
	return sum;
}