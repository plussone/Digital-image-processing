#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

float histgram[256];
int sum1 = 0;

int main()
{
	cv::Mat srcMat = imread("D:\\图片1.png");
	cv::Mat map = Mat(800,1300,CV_8UC3);
	int height = srcMat.rows; //行数 
	int width = srcMat.cols; //每行元素的总元素数量 
	for (int i = 0; i < 256; i++)
	{
		histgram[i] = 0;
	}
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			histgram[srcMat.at<Vec3b>(j, i)[0]]++;
			sum1++;
		}
	}
	for (int i = 0; i < 256; i++)
	{
		histgram[i] /= sum1;
	}
	cv::Point pt1, pt2;
	pt2.x = 0;
	pt2.y = histgram[0]*1000;
	for (int i = 1; i < 256; i++)
	{
		pt1 = pt2;
		pt2.x = i*5;
		pt2.y = histgram[i] * 50000;
		line(map, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);
	}
	flip(map, map, 0);
	cv::imshow("src", map);
	waitKey(0);
	return 0;
}