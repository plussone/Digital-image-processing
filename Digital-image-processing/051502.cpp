/*����ֱ��ͼ���⺯��������ֱ��ͼ���⴦��opencvԭ����ֻ�ܶԵ�ͨ��ͼ�����ֱ��ͼ���⣬Ҫ��ʵ�ֿ��Զ�3ͨ��ͼ�����ֱ��ͼ����*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void three_equalizeHist(Mat srcMat, Mat * dstMat)
{
	Mat srcchannels[3];
	Mat dstchannels[3];
	split(srcMat, srcchannels);
	equalizeHist(srcchannels[0], dstchannels[0]);
	equalizeHist(srcchannels[1], dstchannels[1]);
	equalizeHist(srcchannels[2], dstchannels[2]);
	merge(dstchannels, 3, *dstMat);
}


void test051502()
{
	cv::Mat srcMat = cv::imread("D:\\etest.jpg");
	cv::Mat dstMat;
	three_equalizeHist(srcMat, &dstMat);
	imshow("srcMat", srcMat);
	namedWindow("dstMat", WINDOW_AUTOSIZE);
	imshow("dstMat", dstMat);
	cv::waitKey(0);

	return;
}