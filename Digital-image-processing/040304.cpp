/*投影变换*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test040304()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("D:\\lena.jpg", 1);
	if (srcMat.empty())	return;

	//变换前的四点坐标
	const cv::Point2f pts1[] = {
		cv::Point2f(200,200),
		cv::Point2f(250,200),
		cv::Point2f(200,100),
		cv::Point2f(350,150)

	};
	//变换后的四点坐标
	const cv::Point2f pts2[] = {
		cv::Point2f(100,300),
		cv::Point2f(200,350),
		cv::Point2f(200,100),
		cv::Point2f(340,180)
	};
	//计算仿射矩阵
	const cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);

	cv::warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	cv::imshow("srcMat", srcMat);
	cv::imshow("dst", dstMat);

	cv::waitKey(0);
}