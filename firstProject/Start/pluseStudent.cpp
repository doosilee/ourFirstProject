//#include "student.h"
//#include "image.h"
//
//int pluse_student()
//{
//	FILE* inFile;
//
//	int i;
//	int n;
//	STUDENT st[100];	
//
//	system("cls");
//	inFile = fopen("student.db", "a+");
//	if(inFile == NULL)
//	{
//		printf("������ ã�� �� �����ϴ�.\n");
//		exit(1);
//	}
//
//	printf("%20s %16s %16s\n", "�л��̸�", "�й�", "����");
//	i=0;
//	while(fscanf(inFile, "%s %d %f", st[i].name, &(st[i].id), &(st[i].score)) != EOF)
//	{
//		printf("%20s %16d %16f\n", st[i].name, st[i].id, st[i].score);
//		i++;
//	}
//	printf("���� �л� �����Դϴ�.\n");
//
//	printf("�߰� �� �л��� ������ �̸�, �й�, ���� ������ �Է��ϼ���.\n");
//
//	scanf("%s %d %f",st[i].name, &(st[i].id), &(st[i].score));
//	fprintf(inFile, "%s %d %f\n", st[i].name, st[i].id, st[i].score);
//	fclose(inFile);
//
//	printf("�л��� �߰� �Ǿ����ϴ�.\n");
//	fclose(inFile);
//	printf("�ٸ� �л��� �� �߰��Ϸ��� 1, ���� ȭ������ ���ư����� 2�� �Է��ϼ���.\n");
//
//	scanf("%d",&n);
//
//	if(n==1)
//	{
//		system("cls");
//		pluse_student();
//	}
//	else if(n==2)
//		userInterface1();
//
//	return 0;
//}