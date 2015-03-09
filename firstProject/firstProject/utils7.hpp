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

const char* facerecAlgorithm = "FaceRecognizer.Fisherfaces";		//LDA���ν�
const double EYE_LEFT = 0.16;
const double EYE_RIGHT = (1.0f - EYE_LEFT);
const double EYE_LEFT_Y = 0.14;


//---------------------------------------------------------------------------------------
//���� �б� = ����ó�� ����
Mat readImage(char* fn, int mode = 1)
{
	string image_path = "../../image/";			//�̹��� ���� �⺻ ���
	Mat image = imread(image_path + fn, mode);
	if(image.empty()) {
		cout<< "������ �����ϴ�." <<endl;
		exit(1);
	}
	return image;
}

//��վ󱼰� �������ͷ� �� �籸��
Mat reconstructFace(const Ptr<FaceRecognizer> model, const Mat preprocessedFace)
{
	try{
		//���� ���Ϳ� ��� ��
		Mat eigenvectors = model->get<Mat>("eigenvectors");
		Mat mean_face    = model->get<Mat>("mean");				//1�� �����ͷ� ������

		//-------------------------------------
		//1�� ������ ���� �� �������� ����
		Mat oneRow_face = preprocessedFace.reshape(1, preprocessedFace.rows);
		Mat projection = subspaceReconstruct(eigenvectors, mean_face, projection);
		Mat reconstructionRow = subspaceReconstruct(eigenvectors, mean_face, projection);

		//-------------------------------------
		//�� �� ���� ���� ũ��� �籸��
		Mat reconstruc_face = reconstructionRow.reshape(1, preprocessedFace.rows);
		reconstruc_face.convertTo(reconstruc_face, CV_8U);

		return reconstruc_face;
	}catch(cv::Exception e) {
		return Mat();
	}
}

//Compare two images by getting the L2 error(square-root of sum of squared error).
double getSimilarity(const Mat A, const Mat B)
{
	if(A.total()>0 && A.total() == B.total()) {
		return norm(A, B, NORM_L2)/(A.total());			//�� ������ ����Ҽ��� ���� ��
	}
	else {
		return 100000000.0;								//���� �� ��ȯ
	}
}

//�� ���� ���� �� Ÿ�� ��� �߰�
Mat rotated_face(Mat faceImg, Point* eyes, Size n_face)
{
	//-----------------------------------
	//ȸ�� ���� �� ��濡 ����ũ ����
	if(eyes[1].x >= 0 && eyes[2].x >= 0)
	{
		//------------------------------
		//�� �� �Ÿ� �� ���� ����
		Point2f delta = eyes[2] - eyes[1];
		double angle = atan2(delta.y, delta.x) * 180.0/CV_PI;	//�� ���� ���� ���
		double eyes_len = n_face.width * (EYE_RIGHT - EYE_LEFT);//��������
		double scale = eyes_len / sqrt(delta.x*delta.x + delta.y*delta.y);

		//------------------------------
		//ȸ���� ���
		int n_face_size_2 = n_face.width/2;						//�� ���� �߽�
		Point2f eyesCenter = eyes[2] + eyes[1];					//�� �߽� ��ǥ
		eyesCenter.x /= 2, eyesCenter.y /= 2;
		Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, scale);//ȸ�� ���� ���
		rot_mat.at<double>(0, 2) += n_face_size_2 - eyesCenter.x;   //x�� �����̵�
		rot_mat.at<double>(1, 2) += n_face.width * EYE_LEFT_Y - eyesCenter.y;//y�� �����̵�

		//------------------------------
		//ȸ�� ���� ���� - ������ �� ����
		Mat warped = Mat(n_face, CV_8U, Scalar(128));
		warpAffine(faceImg, warped, rot_mat, warped.size());

		equalizeHist(warped, warped);					//������׷� ��Ȱȭ
		Mat mask = Mat(n_face, CV_8U, Scalar(0));		//ȸ����� ����ũ
		Mat dstImg = Mat(n_face, CV_8U, Scalar(128));	//���� ��ȯ �� ����

		//-----------------------------
		//��濵���� Ÿ�� �߰�
		Point faceCenter(n_face_size_2, cvRound(n_face.width * 0.4f));//Ÿ�� �߽�
		Size size(n_face_size_2, cvRound(n_face.width * 0.8f));			//Ÿ�� ũ��
		ellipse(mask, faceCenter, size, 0, 0, 360, Scalar(255), CV_FILLED);//����ũ �߽ɺ� ��� ����
		warped.copyTo(dstImg, mask);
		return dstImg;
	}
	else 
		return Mat();
}


void display_topface(Mat &frame, Mat corrected_face, Size n_face, int BORDER)
{

	//--------------------------------
	//����� �� �÷� ��ȯ
	Mat tmpBGR;
	cvtColor(corrected_face, tmpBGR, CV_GRAY2BGR);	//����� �� �÷� �������� ǥ��

	//--------------------------------
	//������ �߽� ��ġ ����
	int centerx = (frame.cols - n_face.width) /2;
	Rect face_roi(Point(centerx, BORDER), n_face);	//��� �߾� �簢��
	Mat topface = frame(face_roi);					//�簢�� ��ŭ frame����

	//---------------------------------
	//�÷� ����� �� ���� �� �簢�� �׸���
	tmpBGR.copyTo(topface);
	rectangle(frame, face_roi-Point(1, 1)+Size(2, 2), CV_RGB(200, 200, 200), 1, CV_AA);
}