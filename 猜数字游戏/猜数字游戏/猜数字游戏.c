#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void game()
{
	int b = 0, c = 0, d = 0, e = 100, i = 1;
	printf("��ӭ�����������Ϸ��\n���������֣�");
	c = rand(srand) % 100 + 1;
	while (c<101)
	{
		scanf("%d", &b);
		if (b == c)
		{
			printf("��ϲ���Ҷ��ˣ�\nһ������%d�Σ�\n",i);
			if (i == 1)
			{
				printf("��ѡ֮�ӣ�");
			}
			else if (i < 3 && i != 1)
			{
				printf("�������ˣ���");
			}
			else if (i >= 3 && i < 7)
			{
				printf("��������̫�У�");
			}
			else if (i >= 7)
			{
				printf("����Ĳ��а�����������������");
			}
			break;
		}
		else if (b > c)
		{
			printf("�´��ˣ�\n");
			e = b;
			printf("��ΧΪ%d--%d\nС������û�¶��أ�\n", d, e);
			i++;
		}
		else if (b < c)
		{
			printf("��С�ˣ�\n");
			d = b;
			printf("��ΧΪ%d--%d\n��ȵ�ʺ�ӵ�����!\n", d, e);
			i++;
		}
		printf("��������ɣ�������");
	}
}
void menu()
{
	printf("\n********************************\n");
	printf("******  1.play   0.exit  *******\n");
	printf("********************************\n");
}
int main()
{
	int a = 0;
	srand((unsigned int)time(NULL));
	
	do
	{ 
		menu();
		printf("��ѡ��");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
		{
			game();
			break;
		}
		case 0:
		{
			printf("�˳���Ϸ��");
			break;
		}
		default:
		{
			printf("�������!");
			break;
		}
		}
	} while (a);
	return 0;
}