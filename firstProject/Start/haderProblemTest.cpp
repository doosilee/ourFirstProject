#include "student.h"
#include "image.h"
#include <cstring>

string save_student_image(STUDENT student);
void onMouse(int event, int x, int y, int flags, void*);

//main--------------------------------------------------------------------------------------------------
void main()
{
	int n;
	do{
		system("cls");
		printf("수행 할 항목의 번호를 입력하세요.\n");
		printf("1. 출석 관리 프로그램\n");
		printf("2. 학생 정보관리 프로그램\n");
		printf("3. 종료합니다.\n");
		scanf("%d", &n);

		if(n==1) studentDB();
		else if(n==2) attendanceBook();
		else if(n==3) printf("종료합니다.\n");

	}while(n != 3);
}

//학생정보관리 프로그램-----------------------------------------------------------------------------------
void studentDB()
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
			userInterface1();
		else if(n==2)
			userInterface2();
		else if(n==3)
			printf("종료합니다.\n");

	}while(n!=3);
}

void userInterface1()
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
		change_student();
	else if(n==3)
		delete_student();
}

void userInterface2()
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
	while(fscanf(inFile, "%s %d %f %s", st[i].name, &(st[i].id), &(st[i].score), st[i].image_url) != EOF) i++;

	fclose(inFile);
	/*switch(n)
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
	}*/

	printf("%20s %16s %16s\n", "학생이름", "학번", "점수");
	for(j=0;j<i;j++)
		printf("%20s %16d %16f\n", st[j].name, st[j].id, st[j].score);

	fflush(stdin);
	getchar();
}


//pluse_student---------------------------------------------------------------------------------------------------------------------

int pluse_student()
{
	FILE* inFile;

	int i;
	int n;
	STUDENT st[100];	

	system("cls");
	inFile = fopen("student.db", "a+");
	if(inFile == NULL)
	{
		printf("파일을 찾을 수 없습니다.\n");
		exit(1);
	}

	printf("%20s %16s %16s\n", "학생이름", "학번", "점수");
	i=0;
	while(fscanf(inFile, "%s %d %f %s", st[i].name, &(st[i].id), &(st[i].score), st[i].image_url) != EOF)
	{
		printf("%20s %16d %16f\n", st[i].name, st[i].id, st[i].score);
		i++;
	}
	printf("현재 학생 정보입니다.\n");

	//--------------------------------------------
	//추가 할 학생 정보 입력
	printf("추가 할 학생의 정보를 이름, 학번, 점수 순으로 입력하세요.\n");
	scanf("%s %d %f",st[i].name, &(st[i].id), &(st[i].score));
	fprintf(inFile, "%s %d %f", st[i].name, st[i].id, st[i].score);

	printf("추가 할 학생의 이미지를 저장합니다. 카메라를 보며 잠시만 기다려주세요.\n");
	fprintf(inFile, " %s\n", save_student_image(st[i]));
	fclose(inFile);

	printf("학생이 추가 되었습니다.\n");
	fclose(inFile);
	//----------------------------------------------
	printf("다른 학생을 더 추가하려면 1, 이전 화면으로 돌아가려면 2를 입력하세요.\n");

	scanf("%d",&n);

	if(n==1)
	{
		system("cls");
		pluse_student();
	}
	else if(n==2)
		userInterface1();

	return 0;
}

//delete_sutdent------------------------------------------------------------------------------------------------------------------------

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
		printf("파일을 찾을 수 없습니다.\n");
		exit(1);
	}

	printf("%20s %16s %16s\n", "학생이름", "학번", "점수");
	i=0;
	while(fscanf(inFile, "%s %d %f %s", st[i].name, &(st[i].id), &(st[i].score), st[i].image_url) != EOF)
	{
		printf("%20s %16d %16f\n", st[i].name, st[i].id, st[i].score);
		i++;
	}
	printf("현재 학생 정보입니다.\n");
	fclose(inFile);

	outFile = fopen("student.db", "w");
	printf("삭제 할 학생의 학번을 입력하세요.\n");
	scanf("%d", &input_stu);

	for(j=0;j<i;j++)
	{
		if(st[j].id == input_stu) continue;
		else fprintf(outFile, "%s %d %f %s\n", st[j].name, st[j].id, st[j].score, st[j].image_url);
	}
	fclose(outFile);

	printf("삭제 되었습니다.\n");
	fclose(inFile);
	//----------------------------------------------
	printf("다른 학생을 더 삭제하려면 1, 이전 화면으로 돌아가려면 2를 입력하세요.\n");

	scanf("%d",&n);

	if(n==1)
	{
		system("cls");
		delete_student();
	}
	else if(n==2)
		userInterface1();

	return 0;
}

//change_student------------------------------------------------------------------------------------------------------------------


int change_student()
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
	while(fscanf(inFile, "%s %s %d %f", st[i].image_url, st[i].name, &(st[i].id), &(st[i].score)) != EOF)
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
		change_student();
	}
	else if(n==2)
		userInterface1();

	return 0;
}

//출석체크프로그램-----------------------------------------------------------------------------------------------------------
void attendanceBook()
{
}


//facedetect--------------------------------------------------------------------------------------------------


//------------------------------------
//전역 변수
Rect btn0, btn1;					//버튼을 위한 사각형
bool isSaved = false;				//버튼 클릭시 제어 변수
bool isChanged = false;

//------------------------------------
//마우스 이벤트 콜백 함수
void onMouse(int event, int x, int y, int flags, void*)
{
	if(event == CV_EVENT_LBUTTONDOWN)//왼쪽 마우스 버튼 DOWN
	{
		if(btn0.contains(Point(x, y))) isSaved = !isSaved;	//save 버튼 클릭시 토글 반전
		if(btn1.contains(Point(x, y))) isChanged = true;	//change 버튼 클릭시 true 설정
		//Rect구조체의 contains메쏘드 : 지정된 지점이 사각형 안에 들어가는지 검출
	}
}

String save_student_image(STUDENT student)
{
	//---------------------------------
	//마우스 콜백 함수 등록
	namedWindow("얼굴 검출");					//"얼굴 검출"을 제목으로 하는 윈도우 생성
	setMouseCallback("얼굴 검출", onMouse);		//"얼굴 검출"안에서 마우스 이벤트 발생시 onMouse함수로 처리

	//---------------------------------
	//변수 설정
	string image_url = "C:/Users/Administrator/Desktop/학생정보관리_프로그램/ourFirstProject/학생사진/";
	string msg,fn;

	btn0 = Rect(Point(10, 10), Size(200, 40));
	btn1 = Rect(Point(10, 50), Size(200, 40));

	//---------------------------------
	//검출기 읽기
	CascadeClassifier faceCascade, eyeCascade;
	load_classifier(faceCascade, faceCascadeFilename);
	load_classifier(eyeCascade, eyeCascadeFilename);

	//---------------------------------
	//카메라 초기화
	//---------------------------------
	VideoCapture capture = init_camera(640, 480);

	//---------------------------------
	//실시간 얼굴 검출
	//---------------------------------

	while(1) {
		Mat frame = get_videoframe(capture);	//카메라 영상 입력
		Mat copy = frame.clone();				//저장을 위한 복사본
		//-----------------------------
		//버튼 만들기
		Mat tmp = frame(btn0);
		tmp += (isSaved)? Scalar(50, 50, 50):Scalar(0, 0, 0);
		tmp = frame(btn1);
		tmp += (isChanged)? Scalar(50, 50, 50):Scalar(0, 0, 0);

		putText (frame, "save face", btn0.tl() + Point(5, 26), 0.6f, 1., Scalar(0, 255, 0));
		rectangle(frame, btn0, Scalar(100, 100, 100));
		putText (frame, "change face", btn1.tl() + Point(5, 26), 0.6f, 1., Scalar(0, 255, 0));
		rectangle(frame, btn1, Scalar(Scalar(100, 100, 100)));

		//-----------------------------
		//change 버튼 토글
		if(isChanged) {
			isChanged = false;
			isSaved = false;
		}

		//-----------------------------
		//얼굴과 눈 검출
		Rect face_rects[3];
		Point obj_pts[3];
		Mat detectedFace = detect_object(frame, face_rects, obj_pts, faceCascade, eyeCascade);

		//-----------------------------
		//얼굴 영역 표시
		if(obj_pts[1].x > 0 && obj_pts[2].x > 0)			//눈 영역이 검출되면
		{
			draw_face_eyes(frame, face_rects, obj_pts);

			//-------------------------
			//영상 저장 - save 버튼 토글
			if(isSaved){
				fn = format("%d", student.id);
				imwrite(image_url + fn + ".png", copy);
				putText(frame,"image is saved.", Point(20, 460), 0.6f, 1., Scalar(0, 255, 0));
				
				isChanged = true;
				}
		}			

		imshow("얼굴 검출", frame);
		if(waitKey(100) == 27)			//실행 중지 키(ESC키) 설정
		{
			destroyWindow("얼굴 검출");
			break;
		}
	}
	return image_url;
}

//sorting--------------------------------------------------------------------------------------
int score(void *a, void *b)
{
	STUDENT *temp1, *temp2;
	temp1 = (STUDENT *) a;
	temp2 = (STUDENT *) b;
	return temp1->score - temp2->score;
}

int name(void *a, void *b)
{
	STUDENT *temp1, *temp2;
	temp1 = (STUDENT *) a;
	temp2 = (STUDENT *) b;
	return strcmp(temp1->name, temp2->name);
}

int id(void *a, void *b)
{
	STUDENT *temp1, *temp2;
	temp1 = (STUDENT *) a;
	temp2 = (STUDENT *) b;
	return temp1->id - temp2->id;
}