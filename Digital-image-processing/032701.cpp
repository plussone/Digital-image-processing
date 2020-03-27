/*读取摄像头图像，并对摄像头图像进行中值滤波。*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test032701()
{
	VideoCapture cap(0);
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