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
//		printf("파일을 찾을 수 없습니다.\n");
//		exit(1);
//	}
//
//	printf("%20s %16s %16s\n", "학생이름", "학번", "점수");
//	i=0;
//	while(fscanf(inFile, "%s %d %f", st[i].name, &(st[i].id), &(st[i].score)) != EOF)
//	{
//		printf("%20s %16d %16f\n", st[i].name, st[i].id, st[i].score);
//		i++;
//	}
//	printf("현재 학생 정보입니다.\n");
//
//	printf("추가 할 학생의 정보를 이름, 학번, 점수 순으로 입력하세요.\n");
//
//	scanf("%s %d %f",st[i].name, &(st[i].id), &(st[i].score));
//	fprintf(inFile, "%s %d %f\n", st[i].name, st[i].id, st[i].score);
//	fclose(inFile);
//
//	printf("학생이 추가 되었습니다.\n");
//	fclose(inFile);
//	printf("다른 학생을 더 추가하려면 1, 이전 화면으로 돌아가려면 2를 입력하세요.\n");
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