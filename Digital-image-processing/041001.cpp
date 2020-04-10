/*ͨ��OpenCV����ͼ�����ת�󣬳���ԭ�ߴ�Ĳ��֣��ᱻ�Զ��ü������ʵ�� ���Զ��ü���ͼ����ת*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test041001()
{
	cv::Mat dstMat;
	cv::Mat newMat;
	cv::Mat srcMat = imread("D:\\lena.jpg", 1);
	if (srcMat.empty())	return;

	//��ת30�㣬���ų߶�Ϊ1
	float angle = 30, scale = 1;
	//��ת����Ϊͼ������
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	//��ȡ����ı���
	cv::Rect bbox = cv::RotatedRect(center, srcMat.size(), angle).boundingRect();
	//��������������
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.width / 2.0 - center.y;
	//����任
	cv::warpAffine(srcMat, dstMat, rot, bbox.size());

	imshow("srcMat", srcMat);
	imshow("dst", dstMat);

	waitKey(0);
}