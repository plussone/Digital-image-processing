/*�Ľ������ת*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test040306()
{
	cv::Mat dstMat;
	cv::Mat newMat;
	cv::Mat srcMat = imread("D:\\lena.jpg", 1);
	if (srcMat.empty())	return;

	//��ת30�㣬���ų߶�Ϊ1
	float angle = 30, scale = 1;
	//��ת����Ϊͼ������
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	//�任����
	const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);

	int height = srcMat.rows; //����
	int width = srcMat.cols; //ÿ��Ԫ�ص���Ԫ������

	for (int j = height-1; j >=0; j--){
		for (int i = width-1; i >= 0; i--)
		{
			std::cout << j <<" "<<i <<" "<<std::endl;
			newMat.at<Vec3b>(j + width*(1 + abs(sin(angle))), i + height*(1 + abs(sin(angle))))[0] = srcMat.at<Vec3b>(j, i)[0];
			newMat.at<Vec3b>(j + width*(1 + abs(sin(angle))), i + height*(1 + abs(sin(angle))))[1] = srcMat.at<Vec3b>(j, i)[1];
			newMat.at<Vec3b>(j + width*(1 + abs(sin(angle))), i + height*(1 + abs(sin(angle))))[2] = srcMat.at<Vec3b>(j, i)[2];
		}
	}

	imshow("1",newMat);
	cv::warpAffine(srcMat, dstMat, affine_matrix, dstMat.size());

	imshow("srcMat", srcMat);
	imshow("dst", dstMat);

	waitKey(0);
}