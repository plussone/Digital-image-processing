/*使用大津法分割下图，并对其进行连通域标记，利用图像形态学中所
学的知识实现自动计算原点个数。*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test032003()
{
	cv::Mat srcMat = imread("D:\\IMG_1989.jpg", 0);
	Mat newMat;
	Mat Mat_erode;
	Mat lableMat;
	Mat stateMat;
	Mat centrMat;
	Mat resultMat;

	//二值化
	threshold(srcMat, newMat, 100, 255, THRESH_OTSU);
	newMat = 255 - newMat;

	Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));

	erode(newMat, Mat_erode, kernel);

	imshow("srcMat", srcMat);
	imshow("Mat_erode", Mat_erode);

	int nComp = cv::connectedComponentsWithStats(newMat, lableMat, stateMat, centrMat, 8, CV_32S);

	std::cout << "number:" << nComp - 1 << std::endl;

	waitKey(0);
}
