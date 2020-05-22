/* µœ÷±≥æ∞≤Ó∑÷*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test052201()
{
	
	cv::Mat bgMat;
	cv::Mat subMat;
	cv::Mat bny_subMat;
	int cnt = 0;
	VideoCapture cap(0);
	while (1)
	{
		cv::Mat frame;
		cap >> frame;
		cvtColor(frame, frame, COLOR_BayerBG2GRAY);
		if (cnt == 0)
		{
			frame.copyTo(bgMat);
			cnt = 1;
		}
		else
		{
			absdiff(frame, bgMat, subMat);
			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);
			imshow("b_subMat", bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}
	}
	return;
}