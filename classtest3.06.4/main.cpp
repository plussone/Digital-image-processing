#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

float histgram[256];
int sum1 = 0;

int main()
{
	cv::Mat srcMat = imread("D:\\ͼƬ1.png");
	int height = srcMat.rows; //���� 
	int width = srcMat.cols; //ÿ��Ԫ�ص���Ԫ������ 
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
		printf("%3d   %f\n", i,histgram[i]);
	}
	waitKey(0);
	return 0;
}