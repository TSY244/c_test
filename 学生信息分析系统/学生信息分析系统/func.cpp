#include"root.h"





//�������
double MeanScore(stu* stu1)
{
	return 0;
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
	printf("������������");
	scanf("%d", &stu1->name);
	printf("������ѧ�ɼ���");
	scanf("%d", &stu1->grade[0]);
	printf("����Ӣ��ɼ���");
	scanf("%d", &stu1->grade[1]);
	printf("��������ɼ���");
	scanf("%d", &stu1->grade[2]);
	printf("���뻯ѧ�ɼ���");
	scanf("%d", &stu1->grade[3]);
	printf("�������ĳɼ���");
	scanf("%d", &stu1->grade[4]);
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