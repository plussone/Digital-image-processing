/*读取摄像头图像，并对摄像头图像进行边缘提取，分别提取x，y方向上的边缘，观察结果有何区别。*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test032704()
{
	VideoCapture cap(0);
	while (1)
	{
		Mat frame;
		Mat newMat;
		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;

		cap >> frame;
		Sobel(frame, grad_x, CV_16S, 1, 0);
		convertScaleAbs(grad_x, abs_grad_x);
		Sobel(frame, grad_y, CV_16S, 0, 1);
		convertScaleAbs(grad_y, abs_grad_y);
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, newMat);
		imshow("frame", frame);
		imshow("newMat", newMat);

		waitKey(30);
	}
}