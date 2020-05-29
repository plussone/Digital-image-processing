/*OpenCV模板匹配功能调用练习。*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test052902()
{

	Mat frame;
	Mat tmpMat;
	Mat resMat;
	Mat refMat;
	Mat disMat;
	VideoCapture cap(0);

	int flag = 0;

	while (1)
	{
		cap >> frame;
		if (frame.empty())
			break;
		if (flag == 0)
		{
			Rect2d r;
			r = selectROI(frame, true);
			tmpMat = frame(r);
			tmpMat.copyTo(refMat);
			destroyAllWindows();
		}

		matchTemplate(frame, refMat, resMat, 0);

		normalize(resMat, resMat, 0, 1, NORM_MINMAX, -1, Mat());
		double minVal, maxVal;
		Point minLoc, maxLoc,matchLoc;

		matchLoc = minLoc;

		minMaxLoc(resMat, &minVal, &maxVal, &minLoc, &maxLoc,Mat());

		frame.copyTo(disMat);
		rectangle(disMat, matchLoc, Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows),Scalar::all(0),2,8,0);

		flag++;
		imshow("refMat", refMat);
		imshow("disMat", disMat);
		waitKey(30);
	}
	return;
}