#include"student.h"
int delete_student()
{
	FILE* inFile;
	FILE* outFile;
	int i,j;
	int n;
	int delete_name;
	int input_stu;
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

	outFile = fopen("student.db", "w");
	printf("���� �� �л��� �й��� �Է��ϼ���.\n");
	scanf("%d", &input_stu);

	for(j=0;j<i;j++)
	{
		if(st[j].id == input_stu) continue;
		else fprintf(outFile, "%s %d %f\n", st[j].name, st[j].id, st[j].score);
	}
	fclose(outFile);
	return 0;
}