#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

int main()
{
	cv::Mat srcMat = Mat(500,500,CV_8UC3);
	//»­Ô²
	cv::Point pt;
	pt.x = 10;
	pt.y = 10;
	circle(srcMat, pt, 5, CV_RGB(255, 0, 0), 1, 8, 0);
	//»­Ïß¶Î
	cv::Point pt1,pt2;
	pt1.x = 20;
	pt1.y = 10;
	pt2.x = 30;
	pt2.y = 20;
	line(srcMat, pt1, pt2, CV_RGB(0, 0, 255), 1, 8, 0);
	//»­¾ØÐÎ¿ò
	cv::Rect rect;
	rect.x = 50;
	rect.y = 50;
	rect.width=10;
	rect.height=10;
	rectangle(srcMat, rect, CV_RGB(0, 255, 0), 1, 8, 0);
	cv::imshow("src", srcMat);
	waitKey(0);
	return 0;
}