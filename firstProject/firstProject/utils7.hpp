#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;

const char *faceCascadeFilename = "haarcascades/haarcascade_frontalface_alt2.xml";		//fast Harr �� �����
const char *eyeCascadeFilename = "haarcascades/haarcascade_eye.xml";//�⺻ �� �����

//�з��� �б�
void load_classifier(CascadeClassifier &cascade, string filename) {
	try {
		string opencv_classifier_folder = "c:/opencv/sources/data/";	//OpenCV �з��� ���� ����
		cascade.load(opencv_classifier_folder + filename);
	}catch(Exception e) {}
	if(cascade.empty()) {
		cerr<<"���� : ["<<filename<<"] ������ ���� �� �����ϴ�."<<endl;
		exit(-1);
	}
	cout<<"["<<filename<<"] �б� �Ϸ�." <<endl;
}

//ī�޶� �ʱ�ȭ
VideoCapture init_camera(int width, int height, int cameraNumber = 0)
{
	VideoCapture capture;
	try{
		capture.open(cameraNumber);
	}catch(Exception e) {}
	if(!capture.isOpened()) {
		cerr<<"���� : ī�޶� �� �� �����ϴ�." <<endl;
		exit(1);
	}

	capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);

	cout<<"ī�޶� �غ� �Ϸ� (ī�޶� ��ȣ: " <<cameraNumber <<")"<<endl;

	return capture;
}

//ī�޶� ������ �б� �� �¿����
Mat get_videoframe(VideoCapture capture) {
	Mat frame;
	capture.read(frame);						//ī�޶� ���� �ޱ�
	if(frame.empty()) {
		cerr<< "ERROR: ī�޶� �� �� �����ϴ�." <<endl;
		exit(1);
	}
	flip(frame, frame, 1);						//���� �¿� ������ - �߷� ������ �ſ�ó�� ���� ����
	return frame;
}

//�� ǥ��
void draw_face_eyes(Mat &frame, Rect rects[], Point obj_pts[])
{
	//------------------------------------
	//�� ũ�� �� Ÿ�� �׸���
	Size face_size(rects[0].width/2, rects[0].height/2 + 30);
	ellipse(frame, obj_pts[0], face_size, 0, 0, 360, CV_RGB(255, 255, 0), 3);
}

//��ü ����
void detectLargestObject(const Mat &img, CascadeClassifier &cascade, Rect &largestObject, int scaledWidth = 320)
{
	Mat norm_img, equl_img;
	vector<Rect> objects;					//���� ��ü �簢����

	//-------------------------------------
	//ũ�� ��� - �ӵ� ����� ����
	float scale = img.cols / (float)scaledWidth;	//�ʺ� ���� ����
	int scaledHeight = cvRound(img.rows/scale);		//��� ����
	if(img.cols > scaledWidth)
		resize(img, norm_img, Size(scaledWidth, scaledHeight));
	else
		norm_img = img;

	//-------------------------------------
	//��Ȱȭ �� �� ����
	equalizeHist(norm_img, equl_img);
	cascade.detectMultiScale(equl_img, objects);

	//-------------------------------------
	//���� �簢�� ũ�� ����
	if(img.cols > scaledWidth) {
		for(int i = 0; i<(int)objects.size(); ++i) {
			objects[i].x = cvRound(objects[i].x *scale);
			objects[i].y = cvRound(objects[i].y *scale);
			objects[i].width = cvRound(objects[i].width *scale);
			objects[i].height = cvRound(objects[i].height *scale);
		}
	}

	//-------------------------------------
	//���� ó��
	for(int i = 0; i< (int)objects.size(); i++) {
		if(objects[i].x < 0)		objects[i].x = 0;
		if(objects[i].y < 0)		objects[i].y = 0;
		if(objects[i].x + objects[i].width > img.cols) objects[i].x = img.cols - objects[i].width;
		if(objects[i].y + objects[i].height > img.rows) objects[i].y = img.rows - objects[i].height;
	}

	//-------------------------------------
	//���� ū ��ü�� ��ȯ
	if(objects.size() > 0)	largestObject = (Rect)objects.at(0);
	else					largestObject = Rect(-1, -1, -1, -1);
}

//�� ���� �簢������ �߽��� ã��
Point find_center(Rect rect)
{
	Point pt = Point(-1, -1);
	if(rect.width > 0) {	//�߽��� �ʱ�ȭ
		pt = rect.tl() + Point(rect.width/2, rect.height/2);
	}
	return pt;
}

//��ü ���� - ��, ��
Mat detect_object(Mat srcImg, Rect *rects, Point *points, CascadeClassifier &faceCascade, CascadeClassifier &eyeCascade)
{
	//-------------------------------------
	//�÷� �����̸� ��ϵ� ���� ����
	Mat gray;
	if(srcImg.channels() == 3)	cvtColor(srcImg, gray, CV_BGR2GRAY);
	else						gray = srcImg;

	//-------------------------------------
	//�󱼰� �� ���� �ʱ�ȭ
	for(int i=0; i<3; i++) {
		rects[i] = Rect(-1, -1, -1, -1);		//�� �� �簢��
		points[i] = Point(-1, -1);				//�� �� ��ǥ
	}

	//-------------------------------------
	//�� ����
	detectLargestObject(gray, faceCascade, rects[0]);	//���� ū �簢�� �ϳ� ����

	if(rects[0].width > 0)				//���� ����Ǹ�
	{
		Mat face = gray(rects[0]);		//�� ����
		//---------------------------------
		//���� ��, ������ �� �и�
		Size sub_size(cvRound(face.cols * 0.30f), cvRound(face.rows * 0.30f));
		Point margin_left(cvRound(face.cols * 0.16f), cvRound(face.rows * 0.26f));
		Point margin_right(cvRound(face.cols * 0.16f), cvRound(face.rows * 0.26f));

		Mat left_face		= face(Rect(margin_left, sub_size));
		Mat right_face		= face(Rect(margin_right, sub_size));

		//----------------------------------
		//�� ����
		detectLargestObject(left_face, eyeCascade, rects[1]);
		detectLargestObject(right_face, eyeCascade, rects[2]);

		rects[1] += margin_left;				//���鸸ŭ �̵�
		rects[2] += margin_right;

		//-----------------------------------
		//��, �� �߽���
		points[0] = find_center(rects[0]);
		points[1] = find_center(rects[1]);
		points[2] = find_center(rects[2]);

		return face;
	}
	return Mat();
}
