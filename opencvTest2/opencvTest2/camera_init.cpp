#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
using namespace cv;

void main(){
	//------------------------------------------------
	//���� ĸ�� Ŭ���� ���� �� �ʱ�ȭ
	VideoCapture cap(0);
	//------------------------------------------------
	//����ó��
	if(!cap.isOpened()) {
		printf("ī�޶� ������� �ʾҽ��ϴ�.\n");
		exit(-1);
	}
	//------------------------------------------------
	//ī�޶� �Ӽ� ���� ���
	printf("�ʺ� = %3.1f\n", cap.get(CV_CAP_PROP_FRAME_WIDTH));
	printf("���� = %3.1f\n", cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	printf("���� = %3.1f\n", cap.get(CV_CAP_PROP_EXPOSURE));
	printf("��� = %3.1f\n", cap.get(CV_CAP_PROP_BRIGHTNESS));
	
	//-----------------------------------------------
	//ī�޶� ������ ���
	for(;;){
		Mat frame;
		cap.read(frame);
		imshow("ī�޶� ���󺸱�", frame);
		if(waitKey(30) >= 0) break;
	}
}