/*使用大津法分割下图，并对其进行连通域标记，利用图像形态学中所
学的知识实现自动计算原点个数。*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test032004()
{
	cv::Mat srcMat = imread("D:\\clip.png", 0);
	Mat newMat;
	Mat lableMat;
	Mat stateMat;
	Mat centrMat;
	Mat resultMat;

	//二值化
	threshold(srcMat, newMat, 100, 255, THRESH_OTSU);
	newMat = 255 - newMat;

	Mat kernel = getStructuringElement(MORPH_RECT, Size(12, 12));

	imshow("srcMat", srcMat);
	imshow("newMat", newMat);
	int nComp = cv::connectedComponentsWithStats(newMat, lableMat, stateMat, centrMat, 8, CV_32S);

	double avg=0;

	for (int i = 1; i < nComp; i++)
	{
		avg += stateMat.at<int>(i, 4);
	}
	avg /= nComp;

	int num = 0;
	for (int i = 0; i < nComp; i++)
	{
		if (abs(stateMat.at<int>(i, 4) - avg) > 2500)
		{
			num++;
		}
	}
	std::cout << "number:" << nComp - num << std::endl;

	waitKey(0);
}
