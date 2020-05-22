/*实现高斯建模及背景差分*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void gaosifenbu(std::vector<cv::Mat> srcMat, cv::Mat & Mat1, cv::Mat & Mat2)
{
	int rows = srcMat[0].rows;
	int cols = srcMat[0].cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int sum = 0;
			float fc = 0;
			for (int k = 0; k < srcMat.size(); k++)
			{
				sum += srcMat[k].at<uchar>(i, j);
			}
			Mat1.at<uchar>(i, j) = sum / srcMat.size();
			for (int k = 0; k < srcMat.size(); k++)
			{
				fc += pow((srcMat[k].at<uchar>(i, j) - Mat1.at<uchar>(i, j)), 2);
			}
			Mat2.at<float>(i, j) = fc / srcMat.size();
		}
	}
}

void erzhihua(cv::Mat srcMat, cv::Mat Mat1, cv::Mat Mat2,float w,cv::Mat & dstMat)
{
	int rows = srcMat.rows;
	int cols = srcMat.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int src = srcMat.at<uchar>(i, j);
			int m1 = Mat1.at<uchar>(i, j);
			int sub = abs(src - m1);
			float m2 = w*Mat2.at<float>(i, j);
			if (sub > m2)
			{
				dstMat.at<uchar>(i, j) = 255;
			}
			else
			{
				dstMat.at<uchar>(i, j) = 0;
			}
		}
	}
}

void test052202()
{
	std::vector<cv::Mat> srcMat;
	int nbg = 200;
	float wVar = 2;
	int cnt = 0;
	cv::Mat jzMat;
	cv::Mat fcMat;
	cv::Mat dstMat;
	cv::Mat frame;
	VideoCapture cap(0);
	while (1)
	{
		cap >> frame;
		cvtColor(frame, frame, COLOR_BayerBG2GRAY);
		if (cnt < nbg)
		{
			srcMat.push_back(frame);
		}
		else if(cnt == nbg)
		{
			jzMat.create(frame.size(), CV_8UC1);
			fcMat.create(frame.size(), CV_32FC1);
			gaosifenbu(srcMat,jzMat,fcMat);
		}
		else
		{
			dstMat.create(frame.size(), CV_8SC1);
			erzhihua(frame, jzMat, fcMat, wVar, dstMat);
			imshow("dstMat", dstMat);
			imshow("frame", frame);
			waitKey(1);
		}
		cnt++;
	}
	return;
}