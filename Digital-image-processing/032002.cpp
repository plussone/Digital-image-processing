/*对下图先进行二值化，然后进行连通域标记，并绘制出每个连通域的
外接四边形（bounding box），并使用 cout <<，将硬币的个数 输
出至状态栏。*/

#include<iostream>
#include<opencv2\opencv.hpp>
#include<vector>

using namespace cv;

void test032002()
{
	cv::Mat srcMat = imread("D:\\coin.png",0);
	Mat newMat;
	Mat lableMat;
	Mat stateMat;
	Mat centrMat;
	Mat resultMat;

	//二值化
	threshold(srcMat, newMat, 100, 255, THRESH_OTSU);

	int nComp = cv::connectedComponentsWithStats(newMat, lableMat, stateMat, centrMat, 8, CV_32S);

	std::cout << "number:" << nComp - 1 << std::endl;	

	resultMat = cv::Mat::zeros(srcMat.size(),CV_8UC3);
	std::vector <cv::Vec3b> colors(nComp);
	colors[0]= cv::Vec3b(0, 0, 0);

	for (int n = 1; n < nComp; n++)
	{
		colors[n] = cv::Vec3b(rand() / 255, rand() / 255, rand() / 255);
	}

	for (int y = 0; y < srcMat.rows; y++)
	{
		for (int x=0; x < srcMat.cols; x++)
		{
			int lable = lableMat.at<int>(y, x);
			CV_Assert(0 <= lable&&lable <= nComp);
			resultMat.at<cv::Vec3b>(y, x) = colors[lable];
		}
	}

	for (int i = 1; i < nComp;i++)
	{
		Rect bndbox;

		bndbox.x = stateMat.at<int>(i, 0);
		bndbox.y = stateMat.at<int>(i, 1);

		bndbox.width = stateMat.at<int>(i, 2);
		bndbox.height = stateMat.at<int>(i, 3);

		rectangle(resultMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}

	imshow("resultMat", resultMat);

	waitKey(0);
}
