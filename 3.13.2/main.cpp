#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

int main()
{
	cv::Mat srcMat = imread("D:\\1.jpg",0);
	cv::Mat qjMat; //ȫ�ֶ�ֵ��
	cv::Mat jbMat; //�ֲ���ֵ��

	threshold(srcMat, qjMat, 120, 255, THRESH_OTSU);
	adaptiveThreshold(srcMat,jbMat, 255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,15,10);

	imshow("srcMat", srcMat);
	imshow("qjMat", qjMat);
	imshow("jbMat", jbMat);
	waitKey(0);
	return 0;

}