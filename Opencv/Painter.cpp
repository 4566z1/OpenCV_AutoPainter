//SYSTEM
#include <opencv2/opencv.hpp>

//USER
#include "Painter.hpp"
#include "Common.hpp"

// SYSTEM
using namespace PAINTER;

//USER
using namespace cv;

bool Painter::UpdateHandle(){
	/*-----���¾��-----*/
	if(!SetForegroundWindow(this->window_hwnd)){
		//this->window_hwnd = GetHwndByProcessName(this->process_name);
		this->window_hwnd = GetWindowHWNDByClass(this->class_name);
	}
	return SetForegroundWindow(this->window_hwnd);
}

void on_track1(int pos, void* user_data){
	Mat* src_mat = reinterpret_cast<Mat*>(user_data);
	Mat new_mat;
	src_mat->copyTo(new_mat);

	Canny(new_mat, new_mat, pos, 200);
	imshow("����", new_mat);
}

void on_track2(int pos, void* user_data) {
	Mat* src_mat = reinterpret_cast<Mat*>(user_data);
	Mat new_mat;
	src_mat->copyTo(new_mat);

	Canny(new_mat, new_mat, 100, pos);
	imshow("����", new_mat);
}

bool Painter::Paint(){
	/*-----��ֵ��-----*/
	Mat src_mat = imread(this->filename);
	cvtColor(src_mat, src_mat, COLOR_BGR2GRAY);
	threshold(src_mat, src_mat, 127, 255, THRESH_BINARY);
	//resize(src_mat, src_mat, Size(300, 300));
	//Canny(src_mat, src_mat, 100, 200);

	int min_threshold = 100;
	int max_threshold = 200;
	namedWindow("����");
	//createTrackbar("����ֵ", "����", &min_threshold, 1000, on_track1, &src_mat);
	createTrackbar("����ֵ", "����", &max_threshold, 1000, on_track2, &src_mat);

	imshow("Previcw", src_mat);
	waitKey();

	/*-----���¾��-----*/
	if (!this->UpdateHandle()) return false;

	/*-----�Զ�����-----*/
	for (int i = 0; i < src_mat.rows; i += 2) {
		const auto ptr = src_mat.ptr<uchar>(i, 0);
		for (int j = 0; j < src_mat.cols; j += 2) {
			/* ��ʼ�� */
			RECT window_rect;
			GetWindowRect(this->window_hwnd, &window_rect);

			/* �Զ����� */
			if(*(ptr + j) == 0){
				SetCursorPos(window_rect.left + j, window_rect.top + i);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			}else{
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
			Sleep(1);
		}
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	return true;
}
