/*����Ҷ�任�ϳ�����ͼƬ*/
#include<iostream>
#include<string>
#include<string.h>
#include<opencv2\opencv.hpp>

using namespace cv;

double maxVal;

void dftDemo(Mat src ,Mat *m1,Mat *m2) {
	cv::Mat dst;

	int m = getOptimalDFTSize(src.rows); //2,3,5�ı����и���Ч�ʵĸ���Ҷ�任
	int n = getOptimalDFTSize(src.cols);
	Mat padded;
	//�ѻҶ�ͼ��������Ͻ�,���ұߺ��±���չͼ��,��չ�������Ϊ0;
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
	//planes[0]Ϊdft�任��ʵ����planes[1]Ϊ�鲿��phΪ��λ�� plane_true=magΪ��ֵ
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat planes_true = Mat_<float>(padded);
	Mat ph = Mat_<float>(padded);
	Mat complexImg;
	//��ͨ��complexImg����ʵ�������鲿
	merge(planes, 2, complexImg);
	//���ϱߺϳɵ�mat���и���Ҷ�任,***֧��ԭ�ز���***,����Ҷ�任���Ϊ����.ͨ��1�����ʵ��,ͨ����������鲿
	dft(complexImg, complexImg);
	//�ѱ任��Ľ���ָ����mat,һ��ʵ��,һ���鲿,�����������
	split(complexImg, planes);

	//---------------�˲���Ŀ��Ϊ���õ���ʾ��ֵ---�����ָ�ԭͼʱ�����ٴ���һ��-------------------------
	magnitude(planes[0], planes[1], planes_true);//������mag
	phase(planes[0], planes[1], ph);//��λ��ph
	Mat A = planes[0];
	Mat B = planes[1];
	Mat mag = planes_true;

	mag += Scalar::all(1);//�Է�ֵ��1
	log(mag, mag);//������ķ�ֵһ��ܴ󣬴ﵽ10^4,ͨ��û�а취��ͼ������ʾ��������Ҫ�������log��⡣

				  //ȡ�����е����ֵ�����ں�����ԭʱȥ��һ��
	minMaxLoc(mag, 0, &maxVal, 0, 0);

	//�޼�Ƶ��,���ͼ����л������������Ļ�,����Ƶ���ǲ��ԳƵ�,���Ҫ�޼�
	mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
	ph = ph(Rect(0, 0, mag.cols & -2, mag.rows & -2));
	Mat _magI = mag.clone();
	//�����ȹ�һ��������ʾ��Χ��
	normalize(_magI, _magI, 0, 1, CV_MINMAX);
	//imshow("before rearrange", _magI);

	//��ʾ����Ƶ��ͼ
	int cx = mag.cols / 2;
	int cy = mag.rows / 2;

	//������������Ϊ��׼����magͼ��ֳ��Ĳ���
	Mat tmp;
	Mat q0(mag, Rect(0, 0, cx, cy));
	Mat q1(mag, Rect(cx, 0, cx, cy));
	Mat q2(mag, Rect(0, cy, cx, cy));
	Mat q3(mag, Rect(cx, cy, cx, cy));
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(mag, mag, 0, 1, CV_MINMAX);
	//imshow("ԭͼ�Ҷ�ͼ", src);
	//imshow("Ƶ�׷���", mag);
	*m1 = ph;
	*m2 = mag;
	return ;
}

void ifftDemo(Mat mag ,Mat ph ,Mat src ,Mat *dst)
{
	int cx = mag.cols / 2;
	int cy = mag.rows / 2;

	//ǰ�����跴����һ�飬Ŀ����Ϊ����任��ԭͼ
	Mat q00(mag, Rect(0, 0, cx, cy));
	Mat q10(mag, Rect(cx, 0, cx, cy));
	Mat q20(mag, Rect(0, cy, cx, cy));
	Mat q30(mag, Rect(cx, cy, cx, cy));

	Mat tmp;
	//��������
	q00.copyTo(tmp);
	q30.copyTo(q00);
	tmp.copyTo(q30);
	q10.copyTo(tmp);
	q20.copyTo(q10);
	tmp.copyTo(q20);

	mag = mag * maxVal;//����һ���ľ���ԭ 
	exp(mag, mag);//��Ӧ��ǰ��ȥ����
	mag = mag - Scalar::all(1);//��Ӧǰ��+1
	Mat planes[2];
	polarToCart(mag, ph, planes[0], planes[1]);//�ɷ�����mag����λ��ph�ָ�ʵ��planes[0]���鲿planes[1]
	Mat complexImg;
	merge(planes, 2, complexImg);//��ʵ���鲿�ϲ�


								 //-----------------------����Ҷ����任-----------------------------------
	Mat ifft(Size(src.cols, src.rows), CV_8UC1);
	//����Ҷ��任
	idft(complexImg, ifft, DFT_REAL_OUTPUT);
	normalize(ifft, ifft, 0, 1, CV_MINMAX);

	Rect rect(0, 0, src.cols, src.rows);

	*dst = ifft(rect);
	*dst = *dst * 255;

	cv::Mat dspMat;
	(*dst).convertTo(dspMat, CV_8UC1);
	
	return ;

}

void test050804()
{
	cv::Mat srcMat1 = imread("D:\\s1.jpg", 0);
	cv::Mat srcMat2 = imread("D:\\s2.jpg", 0);
	cv::Mat magMat1;
	cv::Mat magMat2;
	cv::Mat phMat1;
	cv::Mat phMat2;
	cv::Mat dstMat;
	for(int p =1;p<300;p+=1)
	{
		dftDemo(srcMat1, &phMat1, &magMat1);
		dftDemo(srcMat2, &phMat2, &magMat2);
		cv::Mat magMat = magMat1;
		cv::Mat phMat = phMat1;

		int nr = magMat.rows; // number of rows  
		int nc = magMat.cols; // total number of elements per line  
		printf("%d %d\n", nc, nr);
		int r = p;
		for (int j = 0; j < nr; j++) {
			if (nr / 2 - r < j&&j < nr / 2 + r)
			{
				for (int i = 0; i < nc; i++) {
					if (nc / 2 - r < i&&i < nc / 2 + r)
					{
						magMat.at<float>(j, i) = magMat2.at<float>(j, i);
						phMat.at<float>(j, i) = phMat2.at<float>(j, i);
					}
				}
			}
		}
		ifftDemo(magMat, phMat, srcMat1, &dstMat);

		/*imshow("Input Image", magMat);    // Show the result
		imshow("spectrum magnitude1", magMat1);
		imshow("spectrum magnitude2", magMat2);
		imshow("output", dstMat);*/
		std::string s = "D:\\result\\"+std::to_string(p)+".jpg";
		imwrite(s.c_str(), dstMat);
	}
}
