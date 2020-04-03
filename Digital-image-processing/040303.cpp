/*����任*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test040303()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("D:\\lena.jpg", 1);
	if (srcMat.empty())	return;

	//�任ǰ����������
	const cv::Point2f src_pt[] = {
		cv::Point2f(200,200),
		cv::Point2f(250,200),
		cv::Point2f(200,100)
	};
	//�任�����������
	const cv::Point2f dst_pt[] = {
		cv::Point2f(100,300),
		cv::Point2f(200,350),
		cv::Point2f(200,100)
	};
	//����������
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);

	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	cv::imshow("srcMat", srcMat);
	cv::imshow("dst", dstMat);

	cv::waitKey(0);
}