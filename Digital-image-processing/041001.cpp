/*通过OpenCV进行图像的旋转后，超出原尺寸的部分，会被自动裁剪，如何实现 不自动裁剪的图像旋转*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test041001()
{
	cv::Mat dstMat;
	cv::Mat newMat;
	cv::Mat srcMat = imread("D:\\lena.jpg", 1);
	if (srcMat.empty())	return;

	//旋转30°，缩放尺度为1
	float angle = 30, scale = 1;
	//旋转中心为图像中心
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	//获取外界四边形
	cv::Rect bbox = cv::RotatedRect(center, srcMat.size(), angle).boundingRect();
	//调整仿射矩阵参数
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.width / 2.0 - center.y;
	//仿射变换
	cv::warpAffine(srcMat, dstMat, rot, bbox.size());

	imshow("srcMat", srcMat);
	imshow("dst", dstMat);

	waitKey(0);
}