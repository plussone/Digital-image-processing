#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;
using namespace std;

string window_name = "binaryMat";

void threshod_Mat(int th, void*data)
{
	Mat src = *(Mat*)(data);
	Mat dst;
	//二值化
	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
}

int main()
{
	cv::Mat srcMat = imread("D:\\1.jpg");
	cv::Mat gryMat; //全局二值化
	int lowth = 30;
	int maxth = 255;
	if (!srcMat.data) //判断图像是否载入
	{
		cout << "图像载入失败!" << endl;
		return 0;
	}
	cvtColor(srcMat, gryMat, CV_BGR2GRAY);
	imshow(window_name, gryMat);
	createTrackbar("threshold", window_name, &lowth, maxth, threshod_Mat, &gryMat);
	waitKey(0);
	return 0;

}