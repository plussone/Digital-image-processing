/*HuoghLines函数实现霍夫变换*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test041002()
{
	cv::Mat srcMat = imread("D:\\metal-part-distorted-03.png", 0);
	cv::Mat dstMat = imread("D:\\metal-part-distorted-03.png");
	cv::Mat linesMat;
	cv::Mat Canny1Mat;
	cv::Mat Canny2Mat;
	cv::Mat dx;
	cv::Mat dy;

	Sobel(srcMat, dx, CV_16SC1, 1, 0, 3);
	Sobel(srcMat, dy, CV_16SC1, 0, 1, 3);

	Canny(dx, dy, Canny1Mat, 60, 180);

	cv::threshold(Canny1Mat, Canny2Mat, 0, 255, CV_THRESH_OTSU);

	HoughLines(Canny2Mat, linesMat,1,CV_PI/180,90);

	for (int i = 0; i < linesMat.rows; i++)
	{
		float rho = linesMat.at<Vec2f>(i, 0)[0], theta = linesMat.at<Vec2f>(i, 0)[1];
		cv::Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a*rho;
		double y0 = b*rho;
		pt1.x = cv::saturate_cast<int>(x0 + 500 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 500 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 500 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 500 * (a));
		cv::line(dstMat, pt1, pt2, cv::Scalar(0, 255, 255), 1, CV_AA);
	}

	imshow("dstMat", dstMat);
	imshow("Canny1Mat", Canny1Mat);
	imshow("Canny2Mat", Canny2Mat);

	waitKey(0);
}