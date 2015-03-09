#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;

const char *faceCascadeFilename = "haarcascades/haarcascade_frontalface_alt2.xml";		//fast Harr 얼굴 검출기
const char *eyeCascadeFilename = "haarcascades/haarcascade_eye.xml";//기본 눈 검출기

//분류기 읽기
void load_classifier(CascadeClassifier &cascade, string filename) {
	try {
		string opencv_classifier_folder = "c:/opencv/sources/data/";	//OpenCV 분류기 파일 폴더
		cascade.load(opencv_classifier_folder + filename);
	}catch(Exception e) {}
	if(cascade.empty()) {
		cerr<<"에러 : ["<<filename<<"] 파일을 읽을 수 없습니다."<<endl;
		exit(-1);
	}
	cout<<"["<<filename<<"] 읽기 완료." <<endl;
}

//카메라 초기화
VideoCapture init_camera(int width, int height, int cameraNumber = 0)
{
	VideoCapture capture;
	try{
		capture.open(cameraNumber);
	}catch(Exception e) {}
	if(!capture.isOpened()) {
		cerr<<"에러 : 카메라를 열 수 없습니다." <<endl;
		exit(1);
	}

	capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);

	cout<<"카메라 준비 완료 (카메라 번호: " <<cameraNumber <<")"<<endl;

	return capture;
}

//카메라 프레임 읽기 및 좌우반전
Mat get_videoframe(VideoCapture capture) {
	Mat frame;
	capture.read(frame);						//카메라 영상 받기
	if(frame.empty()) {
		cerr<< "ERROR: 카메라를 열 수 없습니다." <<endl;
		exit(1);
	}
	flip(frame, frame, 1);						//영상 좌우 뒤집기 - 추력 영상을 거울처럼 보기 위해
	return frame;
}

//얼굴 표시
void draw_face_eyes(Mat &frame, Rect rects[], Point obj_pts[])
{
	//------------------------------------
	//얼굴 크기 및 타원 그리기
	Size face_size(rects[0].width/2, rects[0].height/2 + 30);
	ellipse(frame, obj_pts[0], face_size, 0, 0, 360, CV_RGB(255, 255, 0), 3);
}

//객체 검출
void detectLargestObject(const Mat &img, CascadeClassifier &cascade, Rect &largestObject, int scaledWidth = 320)
{
	Mat norm_img, equl_img;
	vector<Rect> objects;					//검출 객체 사각형들

	//-------------------------------------
	//크기 축소 - 속도 향상을 위해
	float scale = img.cols / (float)scaledWidth;	//너비 비율 설정
	int scaledHeight = cvRound(img.rows/scale);		//축소 높이
	if(img.cols > scaledWidth)
		resize(img, norm_img, Size(scaledWidth, scaledHeight));
	else
		norm_img = img;

	//-------------------------------------
	//평활화 및 얼굴 검출
	equalizeHist(norm_img, equl_img);
	cascade.detectMultiScale(equl_img, objects);

	//-------------------------------------
	//검출 사각형 크기 복원
	if(img.cols > scaledWidth) {
		for(int i = 0; i<(int)objects.size(); ++i) {
			objects[i].x = cvRound(objects[i].x *scale);
			objects[i].y = cvRound(objects[i].y *scale);
			objects[i].width = cvRound(objects[i].width *scale);
			objects[i].height = cvRound(objects[i].height *scale);
		}
	}

	//-------------------------------------
	//예외 처리
	for(int i = 0; i< (int)objects.size(); i++) {
		if(objects[i].x < 0)		objects[i].x = 0;
		if(objects[i].y < 0)		objects[i].y = 0;
		if(objects[i].x + objects[i].width > img.cols) objects[i].x = img.cols - objects[i].width;
		if(objects[i].y + objects[i].height > img.rows) objects[i].y = img.rows - objects[i].height;
	}

	//-------------------------------------
	//가장 큰 객체만 반환
	if(objects.size() > 0)	largestObject = (Rect)objects.at(0);
	else					largestObject = Rect(-1, -1, -1, -1);
}

//눈 검출 사각형에서 중심점 찾기
Point find_center(Rect rect)
{
	Point pt = Point(-1, -1);
	if(rect.width > 0) {	//중심점 초기화
		pt = rect.tl() + Point(rect.width/2, rect.height/2);
	}
	return pt;
}

//객체 검출 - 얼굴, 눈
Mat detect_object(Mat srcImg, Rect *rects, Point *points, CascadeClassifier &faceCascade, CascadeClassifier &eyeCascade)
{
	//-------------------------------------
	//컬러 영상이면 명암도 영상 변경
	Mat gray;
	if(srcImg.channels() == 3)	cvtColor(srcImg, gray, CV_BGR2GRAY);
	else						gray = srcImg;

	//-------------------------------------
	//얼굴과 눈 정보 초기화
	for(int i=0; i<3; i++) {
		rects[i] = Rect(-1, -1, -1, -1);		//얼굴 눈 사각형
		points[i] = Point(-1, -1);				//얼굴 눈 좌표
	}

	//-------------------------------------
	//얼굴 검출
	detectLargestObject(gray, faceCascade, rects[0]);	//가장 큰 사각형 하나 검출

	if(rects[0].width > 0)				//얼굴이 검출되면
	{
		Mat face = gray(rects[0]);		//얼굴 영상
		//---------------------------------
		//왼쪽 얼굴, 오른쪽 얼굴 분리
		Size sub_size(cvRound(face.cols * 0.30f), cvRound(face.rows * 0.30f));
		Point margin_left(cvRound(face.cols * 0.16f), cvRound(face.rows * 0.26f));
		Point margin_right(cvRound(face.cols * 0.16f), cvRound(face.rows * 0.26f));

		Mat left_face		= face(Rect(margin_left, sub_size));
		Mat right_face		= face(Rect(margin_right, sub_size));

		//----------------------------------
		//눈 검출
		detectLargestObject(left_face, eyeCascade, rects[1]);
		detectLargestObject(right_face, eyeCascade, rects[2]);

		rects[1] += margin_left;				//여백만큼 이동
		rects[2] += margin_right;

		//-----------------------------------
		//얼굴, 눈 중심점
		points[0] = find_center(rects[0]);
		points[1] = find_center(rects[1]);
		points[2] = find_center(rects[2]);

		return face;
	}
	return Mat();
}

const char* facerecAlgorithm = "FaceRecognizer.Fisherfaces";		//LDA얼굴인식
const double EYE_LEFT = 0.16;
const double EYE_RIGHT = (1.0f - EYE_LEFT);
const double EYE_LEFT_Y = 0.14;


//---------------------------------------------------------------------------------------
//영상 읽기 = 예외처리 포함
Mat readImage(char* fn, int mode = 1)
{
	string image_path = "../../image/";			//이미지 파일 기본 경로
	Mat image = imread(image_path + fn, mode);
	if(image.empty()) {
		cout<< "파일이 없습니다." <<endl;
		exit(1);
	}
	return image;
}

//평균얼굴과 고유벡터로 얼굴 재구성
Mat reconstructFace(const Ptr<FaceRecognizer> model, const Mat preprocessedFace)
{
	try{
		//고유 벡터와 평균 얼굴
		Mat eigenvectors = model->get<Mat>("eigenvectors");
		Mat mean_face    = model->get<Mat>("mean");				//1행 데이터로 가져옴

		//-------------------------------------
		//1행 데이터 구성 및 프로젝션 수행
		Mat oneRow_face = preprocessedFace.reshape(1, preprocessedFace.rows);
		Mat projection = subspaceReconstruct(eigenvectors, mean_face, projection);
		Mat reconstructionRow = subspaceReconstruct(eigenvectors, mean_face, projection);

		//-------------------------------------
		//원 얼굴 검출 영상 크기로 재구성
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
		return norm(A, B, NORM_L2)/(A.total());			//두 영상이 비슷할수록 작은 값
	}
	else {
		return 100000000.0;								//에러 값 반환
	}
}

//얼굴 기울기 보정 및 타원 배경 추가
Mat rotated_face(Mat faceImg, Point* eyes, Size n_face)
{
	//-----------------------------------
	//회전 보정 및 배경에 마스크 설정
	if(eyes[1].x >= 0 && eyes[2].x >= 0)
	{
		//------------------------------
		//두 눈 거리 및 보정 비율
		Point2f delta = eyes[2] - eyes[1];
		double angle = atan2(delta.y, delta.x) * 180.0/CV_PI;	//두 눈의 기울기 계산
		double eyes_len = n_face.width * (EYE_RIGHT - EYE_LEFT);//보정길이
		double scale = eyes_len / sqrt(delta.x*delta.x + delta.y*delta.y);

		//------------------------------
		//회전각 계산
		int n_face_size_2 = n_face.width/2;						//얼굴 가로 중심
		Point2f eyesCenter = eyes[2] + eyes[1];					//눈 중심 좌표
		eyesCenter.x /= 2, eyesCenter.y /= 2;
		Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, scale);//회전 보정 행렬
		rot_mat.at<double>(0, 2) += n_face_size_2 - eyesCenter.x;   //x축 평행이동
		rot_mat.at<double>(1, 2) += n_face.width * EYE_LEFT_Y - eyesCenter.y;//y축 평행이동

		//------------------------------
		//회전 보정 수행 - 기울어진 얼굴 보정
		Mat warped = Mat(n_face, CV_8U, Scalar(128));
		warpAffine(faceImg, warped, rot_mat, warped.size());

		equalizeHist(warped, warped);					//히스토그램 평활화
		Mat mask = Mat(n_face, CV_8U, Scalar(0));		//회색배경 마스크
		Mat dstImg = Mat(n_face, CV_8U, Scalar(128));	//최종 반환 얼굴 영상

		//-----------------------------
		//배경영역에 타원 추가
		Point faceCenter(n_face_size_2, cvRound(n_face.width * 0.4f));//타원 중심
		Size size(n_face_size_2, cvRound(n_face.width * 0.8f));			//타원 크기
		ellipse(mask, faceCenter, size, 0, 0, 360, Scalar(255), CV_FILLED);//마스크 중심부 흰색 설정
		warped.copyTo(dstImg, mask);
		return dstImg;
	}
	else 
		return Mat();
}


void display_topface(Mat &frame, Mat corrected_face, Size n_face, int BORDER)
{

	//--------------------------------
	//검출된 얼굴 컬러 변환
	Mat tmpBGR;
	cvtColor(corrected_face, tmpBGR, CV_GRAY2BGR);	//검출된 얼굴 컬러 영상으로 표시

	//--------------------------------
	//프레임 중심 위치 참조
	int centerx = (frame.cols - n_face.width) /2;
	Rect face_roi(Point(centerx, BORDER), n_face);	//상단 중앙 사각형
	Mat topface = frame(face_roi);					//사각형 만큼 frame참조

	//---------------------------------
	//컬러 검출된 얼굴 복사 및 사각형 그리기
	tmpBGR.copyTo(topface);
	rectangle(frame, face_roi-Point(1, 1)+Size(2, 2), CV_RGB(200, 200, 200), 1, CV_AA);
}