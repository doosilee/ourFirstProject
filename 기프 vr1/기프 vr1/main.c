#include"student.h"

void fuction1();
void fuction2();

void main()
{
	int n;
	do{
		system("cls");
		printf("���� �� �׸��� ��ȣ�� �Է��ϼ���.\n");
		printf("1. �л��ڷ� �߰�, ����, ����\n");
		printf("2. �л��ڷ� ����\n");
		printf("3. �����մϴ�.\n");
		scanf("%d", &n);

		if(n==1)
			fuction1();
		else if(n==2)
			fuction2();
		else if(n==3)
			printf("�����մϴ�.\n");

	}while(n!=3);
}

void fuction1()
{
	int n;
	system("cls");
	printf("���� �� �׸��� ��ȣ�� �Է��ϼ���.\n");
	printf("1. �л��ڷ� �߰�\n");
	printf("2. �л��ڷ� ����\n");
	printf("3. �л��ڷ� ����\n");
	printf("4. ����ȭ������ ���ư��ϴ�.\n");

	scanf("%d", &n);

	if(n==1)
		pluse_student();
	else if(n==2)
		change();
	else if(n==3)
		delete_student();
}

void fuction2()
{
	FILE *inFile;
	STUDENT st[100];
	int i=0, j;
	int n;
	system("cls");
	printf("���� �� �׸��� ��ȣ�� �Է��ϼ���.\n");
	printf("1. �̸��� ����\n");
	printf("2. �й��� ����\n");
	printf("3. ������ ����\n");
	printf("4. ����ȭ������ ���ư��ϴ�.\n");

	scanf("%d", &n);

	inFile = fopen("student.db", "r");
	while(fscanf(inFile, "%s %d %f", st[i].name, &(st[i].id), &(st[i].score)) != EOF) i++;

	fclose(inFile);
	switch(n)
	{
	case 1:
		system("cls");
		qsort(st,i,sizeof(STUDENT), name);
		break;
	case 2:
		system("cls");
		qsort(st,i,sizeof(STUDENT), id);
		break;
	case 3:
		system("cls");
		qsort(st,i,sizeof(STUDENT), score);
		break;
	default:
		return;
	}

	printf("%20s %16s %16s\n", "�л��̸�", "�й�", "����");
	for(j=0;j<i;j++)
		printf("%20s %16d %16f\n", st[j].name, st[j].id, st[j].score);

	fflush(stdin);
	getchar();
}