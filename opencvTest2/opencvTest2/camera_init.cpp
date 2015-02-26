#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
using namespace cv;

void main(){
	//------------------------------------------------
	//비디오 캡쳐 클래스 선언 및 초기화
	VideoCapture cap(0);
	//------------------------------------------------
	//예외처리
	if(!cap.isOpened()) {
		printf("카메라가 연결되지 않았습니다.\n");
		exit(-1);
	}
	//------------------------------------------------
	//카메라 속성 정보 출력
	printf("너비 = %3.1f\n", cap.get(CV_CAP_PROP_FRAME_WIDTH));
	printf("높이 = %3.1f\n", cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	printf("노출 = %3.1f\n", cap.get(CV_CAP_PROP_EXPOSURE));
	printf("밝기 = %3.1f\n", cap.get(CV_CAP_PROP_BRIGHTNESS));
	
	//-----------------------------------------------
	//카메라 프레임 출력
	for(;;){
		Mat frame;
		cap.read(frame);
		imshow("카메라 영상보기", frame);
		if(waitKey(30) >= 0) break;
	}
}