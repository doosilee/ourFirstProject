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
		printf("���� �� �׸��� ��ȣ�� �Է��ϼ���.\n");
		printf("1. �⼮ ���� ���α׷�\n");
		printf("2. �л� �������� ���α׷�\n");
		printf("3. �����մϴ�.\n");
		scanf("%d", &n);

		if(n==1) studentDB();
		else if(n==2) attendanceBook();
		else if(n==3) printf("�����մϴ�.\n");

	}while(n != 3);
}

//�л��������� ���α׷�-----------------------------------------------------------------------------------
void studentDB()
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
			userInterface1();
		else if(n==2)
			userInterface2();
		else if(n==3)
			printf("�����մϴ�.\n");

	}while(n!=3);
}

void userInterface1()
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
	printf("���� �� �׸��� ��ȣ�� �Է��ϼ���.\n");
	printf("1. �̸��� ����\n");
	printf("2. �й��� ����\n");
	printf("3. ������ ����\n");
	printf("4. ����ȭ������ ���ư��ϴ�.\n");

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

	printf("%20s %16s %16s\n", "�л��̸�", "�й�", "����");
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
		printf("������ ã�� �� �����ϴ�.\n");
		exit(1);
	}

	printf("%20s %16s %16s\n", "�л��̸�", "�й�", "����");
	i=0;
	while(fscanf(inFile, "%s %d %f %s", st[i].name, &(st[i].id), &(st[i].score), st[i].image_url) != EOF)
	{
		printf("%20s %16d %16f\n", st[i].name, st[i].id, st[i].score);
		i++;
	}
	printf("���� �л� �����Դϴ�.\n");

	//--------------------------------------------
	//�߰� �� �л� ���� �Է�
	printf("�߰� �� �л��� ������ �̸�, �й�, ���� ������ �Է��ϼ���.\n");
	scanf("%s %d %f",st[i].name, &(st[i].id), &(st[i].score));
	fprintf(inFile, "%s %d %f", st[i].name, st[i].id, st[i].score);

	printf("�߰� �� �л��� �̹����� �����մϴ�. ī�޶� ���� ��ø� ��ٷ��ּ���.\n");
	fprintf(inFile, " %s\n", save_student_image(st[i]));
	fclose(inFile);

	printf("�л��� �߰� �Ǿ����ϴ�.\n");
	fclose(inFile);
	//----------------------------------------------
	printf("�ٸ� �л��� �� �߰��Ϸ��� 1, ���� ȭ������ ���ư����� 2�� �Է��ϼ���.\n");

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
		printf("������ ã�� �� �����ϴ�.\n");
		exit(1);
	}

	printf("%20s %16s %16s\n", "�л��̸�", "�й�", "����");
	i=0;
	while(fscanf(inFile, "%s %d %f %s", st[i].name, &(st[i].id), &(st[i].score), st[i].image_url) != EOF)
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
		else fprintf(outFile, "%s %d %f %s\n", st[j].name, st[j].id, st[j].score, st[j].image_url);
	}
	fclose(outFile);

	printf("���� �Ǿ����ϴ�.\n");
	fclose(inFile);
	//----------------------------------------------
	printf("�ٸ� �л��� �� �����Ϸ��� 1, ���� ȭ������ ���ư����� 2�� �Է��ϼ���.\n");

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
		printf("������ ã�� �� �����ϴ�.\n");
		exit(1);
	}

	printf("%20s %16s %16s\n", "�л��̸�", "�й�", "����");
	i=0;
	while(fscanf(inFile, "%s %s %d %f", st[i].image_url, st[i].name, &(st[i].id), &(st[i].score)) != EOF)
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
		change_student();
	}
	else if(n==2)
		userInterface1();

	return 0;
}

//�⼮üũ���α׷�-----------------------------------------------------------------------------------------------------------
void attendanceBook()
{
}


//facedetect--------------------------------------------------------------------------------------------------


//------------------------------------
//���� ����
Rect btn0, btn1;					//��ư�� ���� �簢��
bool isSaved = false;				//��ư Ŭ���� ���� ����
bool isChanged = false;

//------------------------------------
//���콺 �̺�Ʈ �ݹ� �Լ�
void onMouse(int event, int x, int y, int flags, void*)
{
	if(event == CV_EVENT_LBUTTONDOWN)//���� ���콺 ��ư DOWN
	{
		if(btn0.contains(Point(x, y))) isSaved = !isSaved;	//save ��ư Ŭ���� ��� ����
		if(btn1.contains(Point(x, y))) isChanged = true;	//change ��ư Ŭ���� true ����
		//Rect����ü�� contains�޽�� : ������ ������ �簢�� �ȿ� ������ ����
	}
}

String save_student_image(STUDENT student)
{
	//---------------------------------
	//���콺 �ݹ� �Լ� ���
	namedWindow("�� ����");					//"�� ����"�� �������� �ϴ� ������ ����
	setMouseCallback("�� ����", onMouse);		//"�� ����"�ȿ��� ���콺 �̺�Ʈ �߻��� onMouse�Լ��� ó��

	//---------------------------------
	//���� ����
	string image_url = "C:/Users/Administrator/Desktop/�л���������_���α׷�/ourFirstProject/�л�����/";
	string msg,fn;

	btn0 = Rect(Point(10, 10), Size(200, 40));
	btn1 = Rect(Point(10, 50), Size(200, 40));

	//---------------------------------
	//����� �б�
	CascadeClassifier faceCascade, eyeCascade;
	load_classifier(faceCascade, faceCascadeFilename);
	load_classifier(eyeCascade, eyeCascadeFilename);

	//---------------------------------
	//ī�޶� �ʱ�ȭ
	//---------------------------------
	VideoCapture capture = init_camera(640, 480);

	//---------------------------------
	//�ǽð� �� ����
	//---------------------------------

	while(1) {
		Mat frame = get_videoframe(capture);	//ī�޶� ���� �Է�
		Mat copy = frame.clone();				//������ ���� ���纻
		//-----------------------------
		//��ư �����
		Mat tmp = frame(btn0);
		tmp += (isSaved)? Scalar(50, 50, 50):Scalar(0, 0, 0);
		tmp = frame(btn1);
		tmp += (isChanged)? Scalar(50, 50, 50):Scalar(0, 0, 0);

		putText (frame, "save face", btn0.tl() + Point(5, 26), 0.6f, 1., Scalar(0, 255, 0));
		rectangle(frame, btn0, Scalar(100, 100, 100));
		putText (frame, "change face", btn1.tl() + Point(5, 26), 0.6f, 1., Scalar(0, 255, 0));
		rectangle(frame, btn1, Scalar(Scalar(100, 100, 100)));

		//-----------------------------
		//change ��ư ���
		if(isChanged) {
			isChanged = false;
			isSaved = false;
		}

		//-----------------------------
		//�󱼰� �� ����
		Rect face_rects[3];
		Point obj_pts[3];
		Mat detectedFace = detect_object(frame, face_rects, obj_pts, faceCascade, eyeCascade);

		//-----------------------------
		//�� ���� ǥ��
		if(obj_pts[1].x > 0 && obj_pts[2].x > 0)			//�� ������ ����Ǹ�
		{
			draw_face_eyes(frame, face_rects, obj_pts);

			//-------------------------
			//���� ���� - save ��ư ���
			if(isSaved){
				fn = format("%d", student.id);
				imwrite(image_url + fn + ".png", copy);
				putText(frame,"image is saved.", Point(20, 460), 0.6f, 1., Scalar(0, 255, 0));
				
				isChanged = true;
				}
		}			

		imshow("�� ����", frame);
		if(waitKey(100) == 27)			//���� ���� Ű(ESCŰ) ����
		{
			destroyWindow("�� ����");
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