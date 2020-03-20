/*����ͼ�Ƚ��ж�ֵ����Ȼ��ֱ���и�ʴ�����͡�������ͱ����㡣*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test032002()
{
	cv::Mat srcMat = imread("D:\\coin.png",0);
	Mat newMat;
	Mat Mat_OPEN;
	Mat Mat_CLOSE;
	Mat Mat_erode;
	Mat Mat_dilate;

	//��ֵ��
	threshold(srcMat, newMat, 100, 255, THRESH_OTSU);

	imshow("Mat_OPEN;", newMat);
	imshow("Mat_CLOSE", Mat_CLOSE);
	imshow("Mat_erode", Mat_erode);
	imshow("Mat_dilate", Mat_dilate);

	waitKey(0);
}
