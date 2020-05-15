/*图中有一些字，由于曝光不足无法观察到，请使用gamma矫正，并设置合适参数，找出隐藏的信息。李竹老师超级帅。*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void gammars(Mat srcMat, float y, Mat * dstMat)
{
	uchar num[300];
	for (int i = 0; i < 256; i++)
	{
		float ne = ((float)i / 255);
		num[i] = floor(pow(ne, y) * 255);
	}
	std::cout << 1;
	for (int i = 0; i<srcMat.rows; i++)
	{
		for (int j = 0; j<srcMat.cols; j++)
		{
			//std::cout << floor(num[srcMat.at<Vec3b>(i, j)[0]])<<" "<< floor(num[srcMat.at<Vec3b>(i, j)[1]])<<" "<< floor(num[srcMat.at<Vec3b>(i, j)[2]])<<std::endl;
			(*dstMat).at<Vec3b>(i, j)[0] = num[srcMat.at<Vec3b>(i, j)[0]];
			(*dstMat).at<Vec3b>(i, j)[1] = num[srcMat.at<Vec3b>(i, j)[1]];
			(*dstMat).at<Vec3b>(i, j)[2] = num[srcMat.at<Vec3b>(i, j)[2]];
		}
	}
}

void test051503()
{
	cv::Mat srcMat = cv::imread("D:\\gtest.jpg");
	cv::Mat dstMat;
	srcMat.copyTo(dstMat);
	gammars(srcMat, 0.75, &dstMat);
	imshow("srcMat", srcMat);
	imshow("dstMat", dstMat);
	cv::waitKey(0);

	return;
}