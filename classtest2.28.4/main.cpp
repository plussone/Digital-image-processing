#include<iostream>
#include<opencv2\opencv.hpp>

#define compare(a,b) a>b?255:0 //�Ƚϴ�С

using namespace cv;

int main()
{
	cv::Mat srcMat = imread("D:\\1.jpg");
	cv::Mat deepMat; //���
	cv::Mat shallowMat; //ǳ����

	shallowMat = srcMat;
	srcMat.copyTo(deepMat);

	/***�޸�srcMat��ֵ***/
	int height = srcMat.rows; //���� 
	int width = srcMat.cols; //ÿ��Ԫ�ص���Ԫ������ 
	uchar threshold = 100;
	for (int j = 0; j<height; j++) {
		for (int i = 0; i<width; i++) {
			//-----------------��ʼ����ÿ������----------------
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
			average = compare(average, threshold);
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
			//-------------�������ش���-----------------------
		} //���д������ 
	}
	imshow("srcMat", srcMat);
	imshow("deepMat", deepMat);
	imshow("shallowMat", shallowMat);
	waitKey(0);
	return 0;

}