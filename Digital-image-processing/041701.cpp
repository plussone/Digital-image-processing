/*findContours提取和筛选轮廓*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<vector>

using namespace cv;

void test041703()
{
	cv::Mat srcMat = imread("D:\\topic1.JPG");
	cv::Mat dstMat = imread("D:\\topic1.JPG", 0);

	threshold(dstMat, dstMat, 100, 255, THRESH_OTSU);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(dstMat, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++)
	{
		cv::RotatedRect X;
		X = cv::minAreaRect(contours[i]);
		if (contourArea(contours[i]) > 3000 && contourArea(contours[i]) < 6000)
		{
			cv::Point2f vtx[4];
			X.points(vtx);
			for (int j = 0; j<4; j++)
				cv::line(srcMat, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
		}
		//cv::drawContours(srcMat, contours, i, Scalar(0, 0, 255), 1, 8);
	}

	imshow("srcMat", srcMat);

	waitKey(0);
}