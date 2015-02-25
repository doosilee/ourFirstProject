#include"student.h"

void fuction1();
void fuction2();

void main()
{
	int n;
	do{
		system("cls");
		printf("수행 할 항목의 번호를 입력하세요.\n");
		printf("1. 학생자료 추가, 변경, 삭제\n");
		printf("2. 학생자료 정렬\n");
		printf("3. 종료합니다.\n");
		scanf("%d", &n);

		if(n==1)
			fuction1();
		else if(n==2)
			fuction2();
		else if(n==3)
			printf("종료합니다.\n");

	}while(n!=3);
}

void fuction1()
{
	int n;
	system("cls");
	printf("수행 할 항목의 번호를 입력하세요.\n");
	printf("1. 학생자료 추가\n");
	printf("2. 학생자료 변경\n");
	printf("3. 학생자료 삭제\n");
	printf("4. 이전화면으로 돌아갑니다.\n");

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
	printf("수행 할 항목의 번호를 입력하세요.\n");
	printf("1. 이름순 정렬\n");
	printf("2. 학번순 정렬\n");
	printf("3. 성적순 정렬\n");
	printf("4. 이전화면으로 돌아갑니다.\n");

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

	printf("%20s %16s %16s\n", "학생이름", "학번", "점수");
	for(j=0;j<i;j++)
		printf("%20s %16d %16f\n", st[j].name, st[j].id, st[j].score);

	fflush(stdin);
	getchar();
}