/*��ȡ����ͷͼ�񣬲�������ͷͼ����б�Ե��ȡ���ֱ���ȡx��y�����ϵı�Ե���۲����к�����*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test032704()
{
	VideoCapture cap(0);
	while (1)
	{
		Mat frame;
		Mat newMat;
		cap >> frame;
		Sobel(frame, newMat, -1, 1, 1);
		imshow("frame", frame);
		imshow("newMat", newMat);

		waitKey(30);
	}
}