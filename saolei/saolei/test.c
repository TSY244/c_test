#define _CRT_SECURE_NO_WARNINGS 1


#include"game.h"

//��ӡ�˵�
void mune()
{
	printf("********************************\n");
	printf("*********     1.play    ********\n");
	printf("*********     0.exit    ********\n");
	printf("********************************\n");
}

//��Ϸ������
void game()
{
	//������������    
	char mine[ROWS][COLS]={0};
	char show[ROWS][COLS]={0};
	//��ʼ������
	initboard(mine,ROWS,COLS,'0');
	initboard(show,ROWS,COLS,'*');
	//��ӡ��������
	displayboard(show,ROW,COL);
	displayboard(mine,ROW,COL);
	//����ը��
	setmine(mine,ROW,COL);
	displayboard(mine,ROW,COL);
	//�Ų�ը��
	findmine(mine,show,ROW,COL);
}
void test()
{
	int input=0;
	srand((unsigned int)time(NULL));
	do
	{
		mune();
		printf("��ѡ��");
		scanf("%d",&input);
		switch(input)
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
				printf("�������");
				break;
			}
		}
	}while(input);
}
int main()
{
	test();
	return 0;
}