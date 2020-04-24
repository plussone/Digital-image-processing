/*手动实现hog*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<vector>

using namespace cv;

#define cellsize 16
void soble(Mat srcMat,float* p)
{
	int nx = srcMat.cols / cellsize;
	int ny = srcMat.rows / cellsize;
	Mat grad_x, grad_y;
	Mat mag, angle;
	memset(p, 0, sizeof(float)*nx*ny*8);
	cv::Sobel(srcMat, grad_x, CV_32F, 1, 0, 1);
	cv::Sobel(srcMat, grad_y, CV_32F, 0, 1, 1);
	cartToPolar(grad_x, grad_y, mag, angle, true);
	for (size_t i = 0; i < mag.cols; ++i)
	{
		for (size_t j = 0; j < mag.rows; ++j)
		{
			int s = (j/16)*(i/16)*8;
			if (angle.at<float>(j,i) < 45)
			{
				p[s] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 90)
			{
				p[s+1] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 135)
			{
				p[s+2] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 180)
			{
				p[s+3] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 225)
			{
				p[s+4] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 270)
			{
				p[s+5] += mag.at<float>(j, i);
			}
			else if (angle.at<float>(j, i) < 315)
			{
				p[s+6] += mag.at<float>(j, i);
			}
			else
			{
				p[s+7] += mag.at<float>(j, i);
			}
		}
	}
}

float diration(float* p1, int width1, float* p2,int width2)
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


void test042401()
{
	cv::Mat src1Mat = imread("D:\\img1.jpg",0);
	cv::Mat src2Mat = imread("D:\\img2.jpg",0);
	cv::Mat src3Mat = imread("D:\\hogTemplate.jpg",0);

	int hog1_width = (src1Mat.cols / cellsize)*(src1Mat.rows / cellsize) * 8;
	float* hog1 = new float[hog1_width];
	int hog2_width = (src2Mat.cols / cellsize)*(src2Mat.rows / cellsize) * 8;
	float* hog2 = new float[hog2_width];
	int hog3_width = (src3Mat.cols / cellsize)*(src3Mat.rows / cellsize) * 8;
	float* hog3 = new float[hog3_width];

	soble(src1Mat, hog1);
	soble(src2Mat, hog2);
	soble(src3Mat, hog3);

	int dir1 = diration(hog1,hog1_width,hog3,hog3_width);
	int dir2 = diration(hog2,hog2_width,hog3,hog3_width);

	std::cout << "img1.jpg和hogTemplate.jpg的距离为" << sqrt(dir1) << std::endl;
	std::cout << "img2.jpg和hogTemplate.jpg的距离为" << sqrt(dir2) << std::endl;
	
	std::cout << "与hogTemplate.jpg比较相似的是";
	if (dir1 > dir2)
	{
		std::cout << "img2.jpg" << std::endl;
	}
	else
	{
		std::cout << "img1.jpg" << std::endl;
	}
	delete[] hog1;
	delete[] hog2;
	delete[] hog3;

	waitKey(0);
}