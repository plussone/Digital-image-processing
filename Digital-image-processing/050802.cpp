/*����Ҷ�任*/
#include<iostream>
#include<opencv2\opencv.hpp>

using namespace cv;

void test050802() {

	cv::Mat srcMat = imread("D:\\lena.jpg", 0);

	if (srcMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return ;
	}

	Mat padMat;
	//��ͼ��ĳߴ���2��3��5��������ʱ����ɢ����Ҷ�任�ļ����ٶ���졣	
	//�������ͼ�����ѱ任�ߴ�
	int m = getOptimalDFTSize(srcMat.rows);
	int n = getOptimalDFTSize(srcMat.cols);
	//���³ߴ��ͼƬ���б�Ե��Ե���
	copyMakeBorder(srcMat, padMat, 0, m - srcMat.rows, 0, n - srcMat.cols, BORDER_CONSTANT, Scalar::all(0));

	//����һ������,�洢Ƶ��ת����float���͵Ķ����ٴ洢һ������һ����С�ռ�Ķ������洢��������
	Mat planes[] = { Mat_<float>(padMat), Mat::zeros(padMat.size(), CV_32F) };
	Mat complexMat;

	//��2����ͨ����ͼ��ϳ�һ����ͨ��ͼ��
	merge(planes, 2, complexMat);
	//���и���Ҷ�任,���������ԭMat��,����Ҷ�任���Ϊ����.ͨ��1�����ʵ��,ͨ����������鲿
	dft(complexMat, complexMat);
	//��˫ͨ����ͼ�����������ͨ����ͼ 
	//ʵ����planes[0] = Re(DFT(I),
	//�鲿��planes[1]=  Im(DFT(I))) 
	split(complexMat, planes);
	//����λ��������planes[0]
	magnitude(planes[0], planes[1], planes[0]);

	//���²����Ϊ����ʾ����
	Mat magMat = planes[0];
	// log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	magMat += Scalar::all(1);
	log(magMat, magMat);

	//ȷ���Գ�
	magMat = magMat(Rect(0, 0, magMat.cols & -2, magMat.rows & -2));
	int cx = magMat.cols / 2;
	int cy = magMat.rows / 2;
	//��ͼ������
	/*
	0 | 1         3 | 2
	-------  ===> -------
	2 | 3         1 | 0
	*/
	Mat q0(magMat, Rect(0, 0, cx, cy));
	Mat q1(magMat, Rect(cx, 0, cx, cy));
	Mat q2(magMat, Rect(0, cy, cx, cy));
	Mat q3(magMat, Rect(cx, cy, cx, cy));
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//Ϊ��imshow������ʾ����һ����0��1֮��
	normalize(magMat, magMat, 0, 1, NORM_MINMAX);
	//magMat = magMat * 255;

	imshow("Input Image", srcMat);    // Show the result
	imshow("spectrum magnitude", magMat);
	//std::cout << (int)magMat.at<uchar>(12, 12) << std::endl;
	waitKey(0);

	return ;

}
