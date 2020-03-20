/*对下图先进行二值化，然后分别进行腐蚀、膨胀、开运算和闭运算。*/

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

	//二值化
	threshold(srcMat, newMat, 100, 255, THRESH_OTSU);

	imshow("Mat_OPEN;", newMat);
	imshow("Mat_CLOSE", Mat_CLOSE);
	imshow("Mat_erode", Mat_erode);
	imshow("Mat_dilate", Mat_dilate);

	waitKey(0);
}
