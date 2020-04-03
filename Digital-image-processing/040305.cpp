/*图像矫正*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;
using namespace std;

void test040305()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("D:\\lena_rot.jpg", 1);
	if (srcMat.empty())	return;

	int height = srcMat.rows; //行数
	int width = srcMat.cols; //每行元素的总元素数量
	//变换前的四点坐标
	cv::Point2f pts1[4];
	//变换后的四点坐标
	const cv::Point2f pts2[] = {
		cv::Point2f(0,0),
		cv::Point2f(width - 1,0),
		cv::Point2f(0,height-1),
		cv::Point2f(width-1,height - 1)
	};
	for (int j = 0; j<height; j++) {
		for (int i = 0; i<width; i++) {
			if (srcMat.at<Vec3b>(j, i)[0] < 240||srcMat.at<Vec3b>(j, i)[1] <240||srcMat.at<Vec3b>(j, i)[2] <240)
			{
				pts1[0] = cv::Point2f(i, j);
				goto A;
			}
		}
	}
	A:
	for (int i = width-1; i>=0; i--) {
		for (int j = 0; j<height; j++) {
			if (srcMat.at<Vec3b>(j, i)[0] < 240 || srcMat.at<Vec3b>(j, i)[1] <240 || srcMat.at<Vec3b>(j, i)[2] <240)
			{
				pts1[1] = cv::Point2f(i, j);
				goto B;
			}
		}
	}
	B:
	for (int i = 0; i<width; i++) {
		for (int j = height-1; j>=0; j--) {
			if (srcMat.at<Vec3b>(j, i)[0] < 240 || srcMat.at<Vec3b>(j, i)[1] <240 || srcMat.at<Vec3b>(j, i)[2] <240)
			{
				pts1[2] = cv::Point2f(i, j);
				goto C;
			}
		}
	}
	C:
	for (int j = height-1; j>=0; j--) {
		for (int i = width-1; i>=0; i--) {
			if (srcMat.at<Vec3b>(j, i)[0] < 240 || srcMat.at<Vec3b>(j, i)[1] <240 || srcMat.at<Vec3b>(j, i)[2] <240)
			{
				pts1[3] = cv::Point2f(i, j);
				goto D;
			}
		}
	}
	D:

	//计算仿射矩阵
	const cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);

	cv::warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	cv::imshow("srcMat", srcMat);
	cv::imshow("dst", dstMat);

	cv::waitKey(0);
}