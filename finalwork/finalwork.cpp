/*实现工程大作业*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include<algorithm>

using namespace cv;

int rs = 250, gs = 230, bs = 230, ss = 0.95;
Mat fw_kernel = getStructuringElement(MORPH_RECT, Size(15, 15));
cv::Mat fw_bgMat;
Point fw_p1,fw_p2,fw_p3;
std::vector <cv::Vec3b> colors(1000);
std::vector <cv::Mat> fw_srcMat;
cv::Mat fw_jzMat;
cv::Mat fw_fcMat;

void firework(Mat *frame)
{
	cv::Mat fireMat = cv::Mat::zeros((*frame).size(), CV_8UC1);

	int height = (*frame).rows, width = (*frame).cols;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double r = (*frame).at<Vec3b>(i, j)[2];
			double g = (*frame).at<Vec3b>(i, j)[1];
			double b = (*frame).at<Vec3b>(i, j)[0];
			double minValue = min(min(b, g), r);
			double s = (1 - 3.0 * minValue / (r + g + b));

			if (r > g&& g > b&& r > rs&& s > ss&& g < gs && b < bs)
			{
				fireMat.at<uchar>(i, j) = 255;
			}
			else
			{
				fireMat.at<uchar>(i, j) = 0;
			}
		}
	}

	Mat Mat_CLOSE;
	morphologyEx(fireMat, Mat_CLOSE, MORPH_CLOSE, fw_kernel);

	Mat lableMat;
	Mat stateMat;
	Mat centrMat;
	int nComp = cv::connectedComponentsWithStats(Mat_CLOSE, lableMat, stateMat, centrMat, 8, CV_32S);
	std::cout << "number:" << nComp - 1 << std::endl;
	for (int i = 1; i < nComp; i++)
	{
		Rect bndbox;

		bndbox.x = stateMat.at<int>(i, 0);
		bndbox.y = stateMat.at<int>(i, 1);

		bndbox.width = stateMat.at<int>(i, 2);
		bndbox.height = stateMat.at<int>(i, 3);

		rectangle(*frame, bndbox, CV_RGB(100, 255, 100), 1, 8, 0);
	}
}

int fw_compare(Point a, Point b)
{
	return (a.x + a.y) > (b.x + b.y);
}

void fw_drawcircle(Mat* frame, Point fw_p2)
{
	if (fw_p2.x > 0 && fw_p2.y > 0)
	{
		circle(*frame, fw_p2, 5, Scalar(100, 100, 255), -1);
	}
}

void fw_erzhihua(cv::Mat srcMat, cv::Mat Mat1, cv::Mat Mat2, float w, cv::Mat& dstMat)
{
	int rows = srcMat.rows;
	int cols = srcMat.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			/*int src = srcMat.at<uchar>(i, j);
			int m1 = Mat1.at<uchar>(i, j);
			int sub = abs(src - m1);
			float m2 = w*Mat2.at<float>(i, j);*/

			int dif = abs(srcMat.at<uchar>(i, j) - Mat1.at<uchar>(i, j));
			int th = (int)(w * Mat2.at<float>(i, j));
			if (dif > th)
			{
				dstMat.at<uchar>(i, j) = 255;
			}
			else
			{
				dstMat.at<uchar>(i, j) = 0;
			}
		}
	}
}

void fw_gaosifenbu(std::vector<cv::Mat> srcMat, cv::Mat& Mat1, cv::Mat& Mat2)
{
	int rows = srcMat[0].rows;
	int cols = srcMat[0].cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int sum = 0;
			float fc = 0;
			//求均值
			for (int k = 0; k < srcMat.size(); k++)
			{
				sum += srcMat[k].at<uchar>(i, j);
			}
			Mat1.at<uchar>(i, j) = (uchar)(sum / srcMat.size());
			//求方差
			for (int k = 0; k < srcMat.size(); k++)
			{
				fc += (float)pow((srcMat[k].at<uchar>(i, j) - Mat1.at<uchar>(i, j)), 2);
			}
			Mat2.at<float>(i, j) = fc / srcMat.size();
		}
	}
}

void waterwork(Mat *frame,int &cnt)
{
	int nbg = 70;
	float wVar = 2;
	cv::Mat dstMat;
	cv::Mat newMat;

	cvtColor(*frame, newMat, CV_RGB2GRAY);

	if (cnt <= nbg)
	{
		fw_srcMat.push_back(newMat);
	}
	else
	{
		if (cnt == nbg + 1)
		{
			//计算模型
			fw_jzMat.create(newMat.size(), CV_8UC1);
			fw_fcMat.create(newMat.size(), CV_32FC1);
			//调用计算模型函数
			fw_gaosifenbu(fw_srcMat, fw_jzMat, fw_fcMat);
		}

		//背景差分
		dstMat.create(newMat.size(), CV_8UC1);
		//利用均值mat和方差mat，计算差分
		fw_erzhihua(newMat, fw_jzMat, fw_fcMat, wVar, dstMat);
		threshold(dstMat, dstMat, 150, 255, CV_THRESH_BINARY);

		Mat Mat_CLOSE;
		medianBlur(dstMat, dstMat, 27);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
		dilate(dstMat, Mat_CLOSE, kernel);
		//morphologyEx(dstMat, Mat_CLOSE, MORPH_CLOSE, fw_kernel);
		//GaussianBlur(dstMat, dstMat, Size(9, 9), 0, 0, BORDER_DEFAULT);
		//Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
		//morphologyEx(dstMat, dstMat, MORPH_OPEN, kernel);

		Mat lableMat;
		Mat stateMat;
		Mat centrMat;
		int nComp = cv::connectedComponentsWithStats(Mat_CLOSE, lableMat, stateMat, centrMat, 8, CV_32S);

		int max_num = 0, max_size = 0;
		for (int i = 1; i < nComp; i++)
		{
			if (stateMat.at<int>(i, cv::CC_STAT_AREA) > max_size)
			{
				max_num = i;
				max_size = stateMat.at<int>(i, cv::CC_STAT_AREA);
			}
		}

		std::vector <cv::Point> fw_ps1, fw_ps2;
		std::vector <int> fw_y;
		int height = (*frame).rows, width = (*frame).cols;
		
		fw_y.clear();

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//std::cout << i << " " << j << std::endl;
				if (lableMat.at<int>(i,j) == max_num && max_num != 0)
				{
					if (0<i&&i<height-1&&0<j&&j<width-1)
					{
						if (lableMat.at<int>(i - 1, j + 1) != max_num && find(fw_y.begin(),fw_y.end(),j) == fw_y.end())
						{
							fw_y.push_back(j);
							fw_p1.x = j;
							fw_p1.y = i;
							fw_ps1.push_back(fw_p1);
							//fw_drawcircle(frame, fw_p1);
						}
						/*if (lableMat.at<int>(i - 1,j+1) != max_num)
						{
							fw_p1.x = j;
							fw_p1.y = i;
							fw_ps1.push_back(fw_p1);
						}
						else if (lableMat.at<int>(i + 1, j + 1) != max_num)
						{
							fw_p3.x = j;
							fw_p3.y = i;
							fw_ps2.push_back(fw_p3);
						}*/
					}
				}
			}
		}

		if (fw_ps1.size() >= 2 )
		{
			std::sort(fw_ps1.begin(), fw_ps1.end(), fw_compare);

			fw_drawcircle(frame, fw_ps1[0]);
			fw_drawcircle(frame, fw_ps1[fw_ps1.size() - 1]);

			fw_p1 = fw_ps1[0];
			fw_p3 = fw_ps1[fw_ps1.size() - 1];

			//fw_drawcircle(frame, fw_p1);
			//fw_drawcircle(frame, fw_p2);
			//fw_drawcircle(frame, fw_p3);

			CvMat* matA = cvCreateMat(3, 3, CV_32FC1);
			CvMat* matB = cvCreateMat(3, 1, CV_32FC1);
			CvMat* matC = cvCreateMat(3, 1, CV_32FC1);
			float A[3][3] = { {0, 0, 1}, {0, 0, 1}, {0, 0, 1} };
			float B[3] = { 0, 0, 0 };
			float C[3] = { 0, 0, 0 };
			A[0][0] = fw_p2.x * fw_p2.x;
			A[0][1] = fw_p2.x;
			A[1][0] = fw_p3.x * fw_p3.x;
			A[1][1] = fw_p3.x;
			A[2][0] = fw_p1.x * fw_p1.x;
			A[2][1] = fw_p1.x;
			B[0] = fw_p2.y;
			B[1] = fw_p3.y;
			B[2] = fw_p1.y;

			cvSetData(matA, A, CV_AUTOSTEP);
			cvSetData(matB, B, CV_AUTOSTEP);
			cvSolve(matA, matB, matC, CV_LU);

			int mxa = max(max(A[0][1], A[1][1]), A[2][1]);
			int mya = max(max(B[0], B[1]), B[2]);
			int mxi = min(min(A[0][1], A[1][1]), A[2][1]);
			int myi = min(min(B[0], B[1]), B[2]);

			//double fw_dif = abs((int)(fw_p1.x * fw_p1.x * matC->data.fl[0] + fw_p1.x * matC->data.fl[1] + matC->data.fl[0]) - fw_p1.y) + abs((int)(fw_p2.x * fw_p2.x * matC->data.fl[0] + fw_p2.x * matC->data.fl[1] + matC->data.fl[0]) - i) + abs((int)(j * j * matC->data.fl[0] + j * matC->data.fl[1] + matC->data.fl[0]) - i);
			//fw_dif /= 3;
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (mxi <= j && j <= mxa && myi <= i && i <= mya)
					{
						double dif = (int)(j * j * matC->data.fl[0] + j * matC->data.fl[1] + matC->data.fl[2]) - i;
						if (dif == 0)
						{
							fw_p1.x = j;
							fw_p1.y = i;
							fw_drawcircle(frame, fw_p1);
						}
					}
				}
			}
		}

		/*for (int i = 0; i < fw_ps1.size(); i++)
		{
			fw_p1.x = x / fw_ps1.size();
			fw_p1.y = y / fw_ps1.size();
		}*/

		/*for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				/*if (fw_p2.x * fw_p2.y > 1)
				{
					if (lableMat.at<int>(fw_p2.x, fw_p2.y) == lableMat.at<int>(i, j))
					{
						(*frame).at<Vec3b>(i, j)[2] = 255;
						(*frame).at<Vec3b>(i, j)[1] = 100;
						(*frame).at<Vec3b>(i, j)[0] = 100;
					}
					else
					{
						//std::cout << i << " " << j << std::endl;
					}
				}*/
				/*int lable = lableMat.at<int>(i, j);
				CV_Assert(0 <= lable && lable <= nComp);
				(*frame).at<cv::Vec3b>(i, j) = (lable == max_num) ? colors[1] : (*frame).at<cv::Vec3b>(i, j);
			}
		}*/

		//fw_drawcircle(frame, fw_p1);
		//fw_drawcircle(frame, fw_p3);

		//imshow("results", Mat_CLOSE);
		//imshow("result", dstMat);
		//imshow("newMat", newMat);

		cv::waitKey(1);
	}
	std::cout << cnt << std::endl;
	cnt++;

	/*cv::Mat subMat;
	cv::Mat bny_subMat;
	cv::Mat newMat;
	cv::Mat newMats;
	int n = 0;

	cvtColor(*frame, newMat, CV_RGB2GRAY);

	GaussianBlur(newMat, newMat, Size(9, 9), 0, 0, BORDER_DEFAULT);

	//medianBlur(newMat, newMat, 17);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat kernels = getStructuringElement(MORPH_RECT, Size(9, 9));
	//dilate(newMat, newMats, kernel);

	//newMats.copyTo(newMat);

	std::cout << cnt << std::endl;
	if (cnt == n)
	{
		newMat.copyTo(fw_bgMat);
		//cnt = 1;
	}
	else if(cnt > n)
	{
		absdiff(newMat, fw_bgMat, subMat);
		threshold(subMat, bny_subMat, 6, 255, CV_THRESH_BINARY);

		Mat Mat_CLOSE;
		Mat Mat_OPEN;
		//morphologyEx(bny_subMat, Mat_CLOSE, MORPH_CLOSE, fw_kernel);

		//Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
		//morphologyEx(bny_subMat, Mat_CLOSE, MORPH_OPEN, kernel);

		dilate(bny_subMat, Mat_CLOSE, kernel);
		erode(Mat_CLOSE, Mat_OPEN, kernels);

		Mat lableMat;
		Mat stateMat;
		Mat centrMat;
		int nComp = cv::connectedComponentsWithStats(Mat_OPEN, lableMat, stateMat, centrMat, 8, CV_32S);

		int height = (*frame).rows, width = (*frame).cols;
		std::cout << fw_p2.x << " " << fw_p2.y << " " << lableMat.at<int>(fw_p2.x, fw_p2.y) << std::endl;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//if (fw_p2.x * fw_p2.y > 1)
				{
					if (lableMat.at<int>(fw_p2.x, fw_p2.y) == lableMat.at<int>(i, j))
					{
						(*frame).at<Vec3b>(i, j)[2] = 255;
						(*frame).at<Vec3b>(i, j)[1] = 100;
						(*frame).at<Vec3b>(i, j)[0] = 100;
					}
					else
					{
						//std::cout << i << " " << j << std::endl;
					}
				}//
				int lable = lableMat.at<int>(i, j);
				CV_Assert(0 <= lable && lable <= nComp);
				(*frame).at<cv::Vec3b>(i, j) = lable? colors[lable] : (*frame).at<cv::Vec3b>(i, j);
			}
		}
		cv::imshow("b_subMat", bny_subMat);
		cv::imshow("subMat", subMat);
		cv::waitKey(30);
	}
	cnt++;*/
}

void fw_on_mouse(int event, int x, int y, int flags, void* frame)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		fw_p2.x = x;
		fw_p2.y = y;
		Mat* newMat = (Mat*)frame;
		circle(*newMat, fw_p2, 3, Scalar(100, 100, 255), -1);
		printf("(%d,%d)", x, y);
	}
}

void fw()
{
	int cnt = 0;
	int x = 0,y = 0;

	VideoCapture cap("D:\\a.mp4");
	
	colors[0] = cv::Vec3b(0, 0, 0);

	for (int n = 1; n < 100; n++)
	{
		colors[n] = cv::Vec3b(rand() / 255, rand() / 255, rand() / 255);
	}

	std::cout << "请点击视频，选择水枪位置" << std::endl;

	while (1)
	{
		cv::Mat frame;
		cap >> frame;
		
		Mat* mouseMat = &frame;
		cvSetMouseCallback("frame", fw_on_mouse, (void*)mouseMat);

		if (frame.empty())
		{
			break;
		}

		firework(&frame);
		waterwork(&frame,cnt);

		//fw_drawcircle(&frame, fw_p2);
		cv::imshow("frame", frame);
		cv::waitKey(30);
	}
	cv::waitKey(0);
	return;
}