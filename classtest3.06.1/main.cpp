#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

int main()
{
	cv::Mat srcMat = imread("D:\\ͼƬ1.png");
	std::vector<cv::Mat> channels;
	cv::split(srcMat, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	cv::imshow("red", R);
	cv::imshow("blue",B);
	cv::imshow("green",G);
	cv::imshow("src", srcMat);
	waitKey(0);
	return 0;
}