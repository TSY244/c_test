#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void menu()//�˵�����
{
	printf("*****************************\n");
	printf("******* 1.play  0.exit ******\n");
	printf("*****************************\n");
}
void game()
{
	//��������
	char board[row][col] = { 0 };
	//��������ֵ
	char ret ;
	//��ʼ��
	InitBoard(board, row, col);
	//��ӡ
	display(board, row, col);
	//һ�������
	while (1)
	{
		fistplayermove(board, row, col);
		display(board, row, col);
		ret=iswin(board, row, col);
		if (ret != 'c')
		{
			break;
		}
		/*secondplayermove(board, row, col);*/
		computermove(board, row, col);
		display(board, row, col);
		ret=iswin(board, row, col);
		if (ret != 'c')
		{
			break;
		}
	}
	if (ret == '*')
	{
		printf("��һ�ʤ��\n");
	}
	else if (ret == '#')
	{
		printf("���Ի�ʤ��\n");
	}
	else if(ret == 'd')
	{
		printf("ƽ��!\n");
	}
}
void test()//���к���
{
	srand((unsigned int)time(NULL));
	int input;
	do
	{
		menu();
		printf("��ѡ��");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{
			printf("��������Ϸ��\n");
			game();
			break;
		}
		case 0:
		{
			printf("�˳���Ϸ��\n");
			break;
		}
		default:
		{
			printf("�������\n");
			break;
		}
		}
	} while (input);
}
int main()
{
	test();
	return 0;
}