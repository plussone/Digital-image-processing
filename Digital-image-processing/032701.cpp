/*��ȡ����ͷͼ�񣬲�������ͷͼ�������ֵ�˲���*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

VideoCapture cap(0);

void test032701()
{
	while (1)
	{
		Mat frame;
		Mat newMat;
		cap >> frame;
		medianBlur(frame, newMat, 3);
		imshow("frame", frame);
		imshow("newMat", newMat);

		waitKey(30);
	}
}