#include"student.h"
int change()
{
	FILE* inFile;
	FILE* outFile;
	int i, j;
	int n;
	int x;
	long input_id;
	STUDENT st[100];	

	system("cls");
	inFile = fopen("student.db", "r+");
	if(inFile == NULL)
	{
		printf("������ ã�� �� �����ϴ�.\n");
		exit(1);
	}

	printf("%20s %16s %16s\n", "�л��̸�", "�й�", "����");
	i=0;
	while(fscanf(inFile, "%s %d %f", st[i].name, &(st[i].id), &(st[i].score)) != EOF)
	{
		printf("%20s %16d %16f\n", st[i].name, st[i].id, st[i].score);
		i++;
	}
	printf("���� �л� �����Դϴ�.\n");
	fclose(inFile);

	printf("�����ϰ� ���� �л��� �й��� �Է��ϼ���.\n");
	scanf("%d", &input_id);
	
	outFile = fopen("student.db", "w");
	j=0;
	for(j=0; j< i; ++j)
	{
		if(input_id==st[j].id)
		{
			printf("������ �л��� ������ �л��̸�, �й�, ���� ������ �Է��ϼ���.\n");
			scanf("%s %d %f", st[j].name, &st[j].id, &st[j].score);
		}
		fprintf(outFile,"%s %d %f", st[j].name, st[j].id, st[j].score);	
	}
	fclose(outFile);
	
	printf("�л��� ������ ����Ǿ����ϴ�.\n");
	printf("�ݺ������ϰ� ������ 1, ���� ȭ������ ���ư����� 2�� �Է��ϼ���.\n");
	scanf("%d", &n);
	if(n==1)
	{
		system("cls");
		change();
	}
	else if(n==2)
		fuction1();

	return 0;
}