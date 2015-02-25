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
		printf("파일을 찾을 수 없습니다.\n");
		exit(1);
	}

	printf("%20s %16s %16s\n", "학생이름", "학번", "점수");
	i=0;
	while(fscanf(inFile, "%s %d %f", st[i].name, &(st[i].id), &(st[i].score)) != EOF)
	{
		printf("%20s %16d %16f\n", st[i].name, st[i].id, st[i].score);
		i++;
	}
	printf("현재 학생 정보입니다.\n");
	fclose(inFile);

	printf("변경하고 싶은 학생의 학번을 입력하세요.\n");
	scanf("%d", &input_id);
	
	outFile = fopen("student.db", "w");
	j=0;
	for(j=0; j< i; ++j)
	{
		if(input_id==st[j].id)
		{
			printf("변경할 학생의 정보를 학생이름, 학번, 점수 순으로 입력하세요.\n");
			scanf("%s %d %f", st[j].name, &st[j].id, &st[j].score);
		}
		fprintf(outFile,"%s %d %f", st[j].name, st[j].id, st[j].score);	
	}
	fclose(outFile);
	
	printf("학생의 정보가 변경되었습니다.\n");
	printf("반복수행하고 싶으면 1, 이전 화면으로 돌아가려면 2를 입력하세요.\n");
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