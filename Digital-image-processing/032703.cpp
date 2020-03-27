/*读取摄像头图像，并对摄像头图像进行高斯均值滤波。*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test032703()
{
	VideoCapture cap(0);
	while (1)
	{
		Mat frame;
		Mat newMat;

		cap >> frame;
		GaussianBlur(frame, newMat, Size(3,3),0.1);
		imshow("frame", frame);
		imshow("newMat", newMat);

		waitKey(30);
	}
}