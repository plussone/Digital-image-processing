/*使用已经学过的算法，实现一个简单的磨皮程序，即人物皮肤的部分显得光滑。（mask，卷积，HSV范围限制）*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test032705()
{
	VideoCapture cap(0);
	double scale = 0.5;

	double i_minH = 0;
	double i_maxH = 20;

	double i_minS = 43;
	double i_maxS = 255;

	double i_minV = 55;
	double i_maxV = 255;

	Mat frame;
	Mat hsvMat;
	Mat detectMat;
	Mat newface;
	Mat newrFrame;

	while(1)
	{
		//cap >> frame;
		frame = imread("D:\\照片.jpg");
		//HSV
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		rFrame.copyTo(detectMat);
		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		int height = rFrame.rows; //行数
		int width = rFrame.cols; //每行元素的总元素数量
		rFrame.copyTo(newface);
		for (int j = 0; j<height; j++) {
		for (int i = 0; i<width; i++) {
			if (int(detectMat.at<uchar>(j, i)) == 255)
			{
				newface.at<Vec3b>(j, i)[0] = 0;
				newface.at<Vec3b>(j, i)[1] = 0;
				newface.at<Vec3b>(j, i)[2] = 0;
			}
		}
		}
		newrFrame = rFrame - newface;
		GaussianBlur(newface, newface, Size(3, 3), 0.1);
		newrFrame = newrFrame + newface;
		for (int j = 0; j<height; j++) {
			for (int i = 0; i<width; i++) {
				newrFrame.at<Vec3b>(j, i)[0] = newrFrame.at<Vec3b>(j, i)[0] > 255 ? 255 : newrFrame.at<Vec3b>(j, i)[0];
				newrFrame.at<Vec3b>(j, i)[1] = newrFrame.at<Vec3b>(j, i)[1] > 255 ? 255 : newrFrame.at<Vec3b>(j, i)[1];
				newrFrame.at<Vec3b>(j, i)[2] = newrFrame.at<Vec3b>(j, i)[2] > 255 ? 255 : newrFrame.at<Vec3b>(j, i)[2];
			}
		}

		imwrite("D:\\照片ps.jpg", newrFrame);
		imshow("rFrame", newrFrame);
		imshow("frame", rFrame);

		waitKey(30);
	}
}