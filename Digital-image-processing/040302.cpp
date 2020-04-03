/*canny算子*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test040302()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("D:\\lena.jpg", 1);
	if (srcMat.empty())	return ;

	//旋转30°，缩放尺度为1
	float angle = 30, scale = 1;
	//旋转中心为图像中心
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	//变换矩阵
	const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);

	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("srcMat", srcMat);
	imshow("dst", dstMat);

	waitKey(0);
}