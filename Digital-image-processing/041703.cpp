/*findContours提取和筛选轮廓*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<vector>

using namespace cv;

void test041701()
{
	cv::Mat srcMat = imread("D:\\rim.png");
	cv::Mat dstMat = imread("D:\\rim.png",0);

	int x, y, w, h;

	threshold(dstMat, dstMat, 100, 255, THRESH_OTSU);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(dstMat, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++)
	{
		Rect X = cv::boundingRect(contours[i]);
		if (double(X.width /X.height) ==1&&double(X.width / X.height)==1 && contourArea(contours[i])>200&& contourArea(contours[i])<6000)
			cv::drawContours(srcMat, contours, i, Scalar(0,0,255),1,8);
	}
	
	imshow("srcMat", srcMat);

	waitKey(0);
}