/*K means练习*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

void test060501()
{
	cv::Mat src = cv::imread("D:\\temp.jpg");
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);

	int length = src.cols*src.rows;
	cv::Mat labels;
	cv::Mat centers;

	//制作kmeans用的数据
	cv::Mat sampleData = src.reshape(3, length);
	cv::Mat km_data;
	sampleData.convertTo(km_data, CV_32F);

	//执行kmeans
	cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 0.1);
	cv::kmeans(km_data, 2, labels, criteria, 2, KMEANS_PP_CENTERS, centers);

	//制作mask
	for (int i = 0; i < mask.rows; i++)
	{
		for (int j = 0; j < mask.cols; j++)
		{
			mask.at<uchar>(i, j) = labels.at<int>(i*src.cols + j) ? 255 : 0;
		}
	}

	cv::imshow("src", src);
	cv::imshow("mask", mask);

	cv::waitKey(0);
}