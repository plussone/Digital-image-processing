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
		cap >> frame;
		Sobel(frame, newMat, -1, 1, 1);
		imshow("frame", frame);
		imshow("newMat", newMat);

		waitKey(30);
	}
}