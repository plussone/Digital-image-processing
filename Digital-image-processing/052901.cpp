/*利用第九周缩写的基于HOG的图片相似度计算的函数，完
成一个基于HOG的目标物体追踪程序。以下图中的右图为
模板，实现在右图中的定位功能*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<vector>

using namespace cv;

#define cellsize 16
void soble01(Mat srcMat, float* p)
{
	int nx = srcMat.cols / cellsize;
	int ny = srcMat.rows / cellsize;
	Mat grad_x, grad_y;
	Mat mag, angle;
	memset(p, 0, sizeof(float)*nx*ny * 8);
	cv::Sobel(srcMat, grad_x, CV_32F, 1, 0, 1);
	cv::Sobel(srcMat, grad_y, CV_32F, 0, 1, 1);
	cartToPolar(grad_x, grad_y, mag, angle, true);
	for (size_t i = 0; i < mag.cols; ++i)
	{
		for (size_t j = 0; j < mag.rows; ++j)
		{
			int s = (j / 16)*(i / 16) * 8;
			if (angle.at<float>(j, i) < 45)
			{
				p[s] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 90)
			{
				p[s + 1] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 135)
			{
				p[s + 2] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 180)
			{
				p[s + 3] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 225)
			{
				p[s + 4] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 270)
			{
				p[s + 5] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 315)
			{
				p[s + 6] += mag.at<float>(j, i);
			}
			else
			{
				p[s + 7] += mag.at<float>(j, i);
			}
		}
	}
}

float diration01(float* p1, int width1, float* p2, int width2)
{
	float sum = 0;
	if (width1 > width2)
	{
		float* p3 = p1;
		p1 = p2;
		p2 = p3;
		int width3 = width1;
		width1 = width2;
		width2 = width3;
	}
	int i = 0;
	for (; i < width1; ++i)
	{
		sum += (p1[i] - p2[i])*(p1[i] - p2[i]);
	}
	i = width1 - 1;
	while ((++i) < width2)
	{
		sum += p2[i] * p2[i];
	}
	return sum;
}


void test052901()
{
	cv::Mat src1Mat = imread("D:\\img.png", 0); 
	cv::Mat src2Mat = imread("D:\\template.png", 0);
	cv::Mat src3Mat = imread("D:\\template.png", 0);

	int hog2_width = (src2Mat.cols / cellsize)*(src2Mat.rows / cellsize) * 8;
	float* hog2 = new float[hog2_width];
	soble01(src2Mat, hog2);

	float mindir = 1000000000;
	int mx = 0;
	int my = 0;
	for (int i =0;i<=src1Mat.rows - src2Mat.rows;i++)
	{
		std::cout << i << std::endl;
		for (int j = 0;j<=src1Mat.cols-src2Mat.cols;j++)
		{
			for (int x = 0; x < src3Mat.rows; x++)
			{
				for (int y = 0; y < src3Mat.cols; y++)
				{
					src3Mat.at<uchar>(x, y) = src1Mat.at<uchar>(i+x,j+y);
				}
			}
			int hog3_width = (src3Mat.cols / cellsize)*(src3Mat.rows / cellsize) * 8;
			float* hog3 = new float[hog3_width];

			soble01(src3Mat, hog3);
			float dir1 = diration01(hog2, hog2_width, hog3, hog3_width);
			//std::cout << dir1 << std::endl;
			if (dir1 < mindir)
			{
				mx = i;
				my = j;
				mindir = dir1;
			}
			delete[] hog3;
		}
	}

	std::cout << "img1.jpg的坐标为x:" << mx <<" y:"<< my << std::endl;
	delete[] hog2;

	cv::imshow("src1", src1Mat);
	cv::imshow("src2", src2Mat);

	cv::waitKey(0);

}
