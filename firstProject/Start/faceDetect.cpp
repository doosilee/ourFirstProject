//#include "student.h"
//#include "image.h"
//
////------------------------------------
////���� ����
//Rect btn0, btn1;					//��ư�� ���� �簢��
//bool isSaved = false;				//��ư Ŭ���� ���� ����
//bool isChanged = false;
//
////�з��� �б�
//void load_classifier(CascadeClassifier &cascade, string filename) {
//	try {
//		string opencv_classifier_folder = "c:/opencv/sources/data/";	//OpenCV �з��� ���� ����
//		cascade.load(opencv_classifier_folder + filename);
//	}catch(Exception e) {}
//	if(cascade.empty()) {
//		cerr<<"���� : ["<<filename<<"] ������ ���� �� �����ϴ�."<<endl;
//		exit(-1);
//	}
//	cout<<"["<<filename<<"] �б� �Ϸ�." <<endl;
//}
//
////ī�޶� �ʱ�ȭ
//VideoCapture init_camera(int width, int height, int cameraNumber = 0)
//{
//	VideoCapture capture;
//	try{
//		capture.open(cameraNumber);
//	}catch(Exception e) {}
//	if(!capture.isOpened()) {
//		cerr<<"���� : ī�޶� �� �� �����ϴ�." <<endl;
//		exit(1);
//	}
//
//	capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
//	capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);
//
//	cout<<"ī�޶� �غ� �Ϸ� (ī�޶� ��ȣ: " <<cameraNumber <<")"<<endl;
//
//	return capture;
//}
//
////ī�޶� ������ �б� �� �¿����
//Mat get_videoframe(VideoCapture capture) {
//	Mat frame;
//	capture.read(frame);						//ī�޶� ���� �ޱ�
//	if(frame.empty()) {
//		cerr<< "ERROR: ī�޶� �� �� �����ϴ�." <<endl;
//		exit(1);
//	}
//	flip(frame, frame, 1);						//���� �¿� ������ - �߷� ������ �ſ�ó�� ���� ����
//	return frame;
//}
//
////�� ǥ��
//void draw_face_eyes(Mat &frame, Rect rects[], Point obj_pts[])
//{
//	//------------------------------------
//	//�� ũ�� �� Ÿ�� �׸���
//	Size face_size(rects[0].width/2, rects[0].height/2 + 30);
//	ellipse(frame, obj_pts[0], face_size, 0, 0, 360, CV_RGB(255, 255, 0), 3);
//}
//
////��ü ����
//void detectLargestObject(const Mat &img, CascadeClassifier &cascade, Rect &largestObject, int scaledWidth = 320)
//{
//	Mat norm_img, equl_img;
//	vector<Rect> objects;					//���� ��ü �簢����
//
//	//-------------------------------------
//	//ũ�� ��� - �ӵ� ����� ����
//	float scale = img.cols / (float)scaledWidth;	//�ʺ� ���� ����
//	int scaledHeight = cvRound(img.rows/scale);		//��� ����
//	if(img.cols > scaledWidth)
//		resize(img, norm_img, Size(scaledWidth, scaledHeight));
//	else
//		norm_img = img;
//
//	//-------------------------------------
//	//��Ȱȭ �� �� ����
//	equalizeHist(norm_img, equl_img);
//	cascade.detectMultiScale(equl_img, objects);
//
//	//-------------------------------------
//	//���� �簢�� ũ�� ����
//	if(img.cols > scaledWidth) {
//		for(int i = 0; i<(int)objects.size(); ++i) {
//			objects[i].x = cvRound(objects[i].x *scale);
//			objects[i].y = cvRound(objects[i].y *scale);
//			objects[i].width = cvRound(objects[i].width *scale);
//			objects[i].height = cvRound(objects[i].height *scale);
//		}
//	}
//
//	//-------------------------------------
//	//���� ó��
//	for(int i = 0; i< (int)objects.size(); i++) {
//		if(objects[i].x < 0)		objects[i].x = 0;
//		if(objects[i].y < 0)		objects[i].y = 0;
//		if(objects[i].x + objects[i].width > img.cols) objects[i].x = img.cols - objects[i].width;
//		if(objects[i].y + objects[i].height > img.rows) objects[i].y = img.rows - objects[i].height;
//	}
//
//	//-------------------------------------
//	//���� ū ��ü�� ��ȯ
//	if(objects.size() > 0)	largestObject = (Rect)objects.at(0);
//	else					largestObject = Rect(-1, -1, -1, -1);
//}
//
////�� ���� �簢������ �߽��� ã��
//Point find_center(Rect rect)
//{
//	Point pt = Point(-1, -1);
//	if(rect.width > 0) {	//�߽��� �ʱ�ȭ
//		pt = rect.tl() + Point(rect.width/2, rect.height/2);
//	}
//	return pt;
//}
//
////��ü ���� - ��, ��
//Mat detect_object(Mat srcImg, Rect *rects, Point *points, CascadeClassifier &faceCascade, CascadeClassifier &eyeCascade)
//{
//	//-------------------------------------
//	//�÷� �����̸� ��ϵ� ���� ����
//	Mat gray;
//	if(srcImg.channels() == 3)	cvtColor(srcImg, gray, CV_BGR2GRAY);
//	else						gray = srcImg;
//
//	//-------------------------------------
//	//�󱼰� �� ���� �ʱ�ȭ
//	for(int i=0; i<3; i++) {
//		rects[i] = Rect(-1, -1, -1, -1);		//�� �� �簢��
//		points[i] = Point(-1, -1);				//�� �� ��ǥ
//	}
//
//	//-------------------------------------
//	//�� ����
//	detectLargestObject(gray, faceCascade, rects[0]);	//���� ū �簢�� �ϳ� ����
//
//	if(rects[0].width > 0)				//���� ����Ǹ�
//	{
//		Mat face = gray(rects[0]);		//�� ����
//		//---------------------------------
//		//���� ��, ������ �� �и�
//		Size sub_size(cvRound(face.cols * 0.30f), cvRound(face.rows * 0.30f));
//		Point margin_left(cvRound(face.cols * 0.16f), cvRound(face.rows * 0.26f));
//		Point margin_right(cvRound(face.cols * 0.16f), cvRound(face.rows * 0.26f));
//
//		Mat left_face		= face(Rect(margin_left, sub_size));
//		Mat right_face		= face(Rect(margin_right, sub_size));
//
//		//----------------------------------
//		//�� ����
//		detectLargestObject(left_face, eyeCascade, rects[1]);
//		detectLargestObject(right_face, eyeCascade, rects[2]);
//
//		rects[1] += margin_left;				//���鸸ŭ �̵�
//		rects[2] += margin_right;
//
//		//-----------------------------------
//		//��, �� �߽���
//		points[0] = find_center(rects[0]);
//		points[1] = find_center(rects[1]);
//		points[2] = find_center(rects[2]);
//
//		return face;
//	}
//	return Mat();
//}
//
////------------------------------------
////���콺 �̺�Ʈ �ݹ� �Լ�
//void onMouse(int event, int x, int y, int flags, void*)
//{
//	if(event == CV_EVENT_LBUTTONDOWN)//���� ���콺 ��ư DOWN
//	{
//		if(btn0.contains(Point(x, y))) isSaved = !isSaved;	//save ��ư Ŭ���� ��� ����
//		if(btn1.contains(Point(x, y))) isChanged = true;	//change ��ư Ŭ���� true ����
//		//Rect����ü�� contains�޽�� : ������ ������ �簢�� �ȿ� ������ ����
//	}
//}
//
//void save_student_image(STUDENT student)
//{
//	//---------------------------------
//	//���콺 �ݹ� �Լ� ���
//	namedWindow("�� ����");					//"�� ����"�� �������� �ϴ� ������ ����
//	setMouseCallback("�� ����", onMouse);		//"�� ����"�ȿ��� ���콺 �̺�Ʈ �߻��� onMouse�Լ��� ó��
//
//	//---------------------------------
//	//���� ����
//	int h_cnt = 0, f_cnt = -1;
//	string image_url = "C:/Users/Administrator/Desktop/�л��������� ���α׷�/ourFirstProject/�л� ����/";
//	string msg,fn;
//
//	btn0 = Rect(Point(10, 10), Size(200, 40));
//	btn1 = Rect(Point(10, 50), Size(200, 40));
//
//	//---------------------------------
//	//����� �б�
//	CascadeClassifier faceCascade, eyeCascade;
//	load_classifier(faceCascade, faceCascadeFilename);
//	load_classifier(eyeCascade, eyeCascadeFilename);
//
//	//---------------------------------
//	//ī�޶� �ʱ�ȭ
//	//---------------------------------
//	VideoCapture capture = init_camera(640, 480);
//
//	//---------------------------------
//	//�ǽð� �� ����
//	//---------------------------------
//
//	while(1) {
//		Mat frame = get_videoframe(capture);	//ī�޶� ���� �Է�
//		Mat copy = frame.clone();				//������ ���� ���纻
//		//-----------------------------
//		//��ư �����
//		Mat tmp = frame(btn0);
//		tmp += (isSaved)? Scalar(50, 50, 50):Scalar(0, 0, 0);
//		tmp = frame(btn1);
//		tmp += (isChanged)? Scalar(50, 50, 50):Scalar(0, 0, 0);
//
//		putText (frame, "save face", btn0.tl() + Point(5, 26), 0.6f, 1., Scalar(0, 255, 0));
//		rectangle(frame, btn0, Scalar(100, 100, 100));
//		putText (frame, "change face", btn1.tl() + Point(5, 26), 0.6f, 1., Scalar(0, 255, 0));
//		rectangle(frame, btn1, Scalar(Scalar(100, 100, 100)));
//
//		//-----------------------------
//		//change ��ư ���
//		if(isChanged) {
//			h_cnt++; f_cnt = -1;
//			isChanged = false;
//			isSaved = false;
//		}
//
//		//-----------------------------
//		//�󱼰� �� ����
//		Rect face_rects[3];
//		Point obj_pts[3];
//		Mat detectedFace = detect_object(frame, face_rects, obj_pts, faceCascade, eyeCascade);
//
//		//-----------------------------
//		//�� �� �� ���� ǥ��
//		if(obj_pts[1].x > 0 && obj_pts[2].x > 0)			//�� ������ ����Ǹ�
//		{
//			draw_face_eyes(frame, face_rects, obj_pts);
//
//			//-------------------------
//			//���� ���� - save ��ư ���
//			if(isSaved){
//				fn = format("%d", student.id);
//				imwrite(image_url+ fn, copy);
//				isChanged = true;
//			}
//		}
//
//		//-----------------------------
//		//���� ���� ǥ��
//		if(f_cnt>=0)
//			putText(frame, fn+" is saved.", Point(20, 460), 0.6f, 1., Scalar(0, 255, 0));
//
//		imshow("�� ����", frame);
//
//		if(waitKey(100) == 27) break;				//���� ���� Ű(ESCŰ) ����
//	}
//}