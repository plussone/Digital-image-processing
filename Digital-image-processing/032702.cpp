/*��ȡ����ͷͼ�񣬲�������ͷͼ����о�ֵ�˲���*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test032702()
{
	VideoCapture cap(0);
	while (1)
	{
		Mat frame;
		Mat newMat;
		cap >> frame;
		blur(frame, newMat,Size(3,3));
		imshow("frame", frame);
		imshow("newMat", newMat);

		waitKey(30);
	}
}