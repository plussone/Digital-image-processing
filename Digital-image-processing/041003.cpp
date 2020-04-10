/*HuoghLinesP函数实现霍夫变换*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test041003()
{
	cv::Mat srcMat = imread("D:\\metal-part-distorted-03.png", 0);
	cv::Mat dstMat = imread("D:\\metal-part-distorted-03.png");
	cv::Mat linesMat;
	cv::Mat Canny1Mat;
	cv::Mat Canny2Mat;
	cv::Mat dx;
	cv::Mat dy;

	Sobel(srcMat, dx, CV_16SC1, 1, 0, 3);
	Sobel(srcMat, dy, CV_16SC1, 0, 1, 3);

	Canny(dx, dy, Canny1Mat, 60, 180);

	cv::threshold(Canny1Mat, Canny2Mat, 0, 255, CV_THRESH_OTSU);

	HoughLinesP(Canny2Mat, linesMat, 1, CV_PI / 180, 30,50,30);

	for (int i = 0; i < linesMat.rows; i++)
	{
		cv::Point pt1, pt2;
		pt1.x = linesMat.at<Vec4i>(i, 0)[0];
		pt1.y = linesMat.at<Vec4i>(i, 0)[1];
		pt2.x = linesMat.at<Vec4i>(i, 0)[2];
		pt2.y = linesMat.at<Vec4i>(i, 0)[3];
		cv::line(dstMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}

	imshow("dstMat", dstMat);
	imshow("Canny1Mat", Canny1Mat);
	imshow("Canny2Mat", Canny2Mat);

	waitKey(0);
}