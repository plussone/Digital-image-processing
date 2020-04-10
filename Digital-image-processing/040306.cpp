/*改进后的旋转*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test040306()
{
	cv::Mat dstMat;
	cv::Mat newMat;
	cv::Mat srcMat = imread("D:\\lena.jpg", 1);
	if (srcMat.empty())	return;

	//旋转30°，缩放尺度为1
	float angle = 30, scale = 1;
	//旋转中心为图像中心
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	//变换矩阵
	const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);

	int height = srcMat.rows; //行数
	int width = srcMat.cols; //每行元素的总元素数量

	for (int j = height-1; j >=0; j--){
		for (int i = width-1; i >= 0; i--)
		{
			std::cout << j <<" "<<i <<" "<<std::endl;
			newMat.at<Vec3b>(j + width*(1 + abs(sin(angle))), i + height*(1 + abs(sin(angle))))[0] = srcMat.at<Vec3b>(j, i)[0];
			newMat.at<Vec3b>(j + width*(1 + abs(sin(angle))), i + height*(1 + abs(sin(angle))))[1] = srcMat.at<Vec3b>(j, i)[1];
			newMat.at<Vec3b>(j + width*(1 + abs(sin(angle))), i + height*(1 + abs(sin(angle))))[2] = srcMat.at<Vec3b>(j, i)[2];
		}
	}

	imshow("1",newMat);
	cv::warpAffine(srcMat, dstMat, affine_matrix, dstMat.size());

	imshow("srcMat", srcMat);
	imshow("dst", dstMat);

	waitKey(0);
}