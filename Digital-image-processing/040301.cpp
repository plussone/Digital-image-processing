/*cannyËã×Ó*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test040301()
{
	cv::Mat srcMat = imread("D:\\lena.jpg", 0);
	Mat Canny1Mat;
	Mat Canny2Mat;
	Mat dx;
	Mat dy;

	Sobel(srcMat, dx, CV_16SC1, 1, 0, 3);
	Sobel(srcMat, dy, CV_16SC1, 0, 1, 3);

	Canny(dx,dy, Canny1Mat, 60, 180);
	Canny(srcMat, Canny2Mat, 60, 80);

	imshow("srcMat", srcMat);
	imshow("Canny1Mat", Canny1Mat);
	imshow("Canny2Mat", Canny2Mat);

	waitKey(0);
}
