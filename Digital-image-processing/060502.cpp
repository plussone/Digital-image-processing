/*K means视频绿布处理*/
#include<iostream>
#include<opencv2\opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

void test060502()
{
	cv::VideoCapture cap0("https://vdept.bdstatic.com/786a59363949567762765a4368765353/4b4a786c5158516d/081c031103b7ce08bcaac767a3bdfe46ec6e5dc02c9c268860c7df4f24bfa3a97b671bc2babe30c124d29dcbc9586a29.mp4?auth_key=1591348910-0-0-3ae4b2257ddbd3d935e7d0796f6758a3");
	cv::VideoCapture cap1("https://video.699pic.com/videos/10/90/93/b_9Tuhhatmxeey1591109093.mp4");
	cv::Mat frame0;
	cv::Mat frame1;

ex1:
	if (!cap0.isOpened() || !cap1.isOpened()) //检查打开是否成功 
		return;
	while (1)
	{
		ex2:
			cap0 >> frame0;
			cap1 >> frame1;
			if (!frame0.empty() && !frame1.empty()) //判断当前 帧是否为空 
			{
				cv::Mat mask = cv::Mat::zeros(frame1.size(), CV_8UC3);

				int length = frame0.cols*frame0.rows;
				cv::Mat labels;
				cv::Mat centers;

				//制作kmeans用的数据
				cv::Mat sampleData = frame0.reshape(3, length);
				cv::Mat km_data;
				sampleData.convertTo(km_data, CV_32F);

				//执行kmeans
				cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 0.1);
				cv::kmeans(km_data, 2, labels, criteria, 2, cv::KMEANS_PP_CENTERS, centers);

				//制作mask
				for (int i = 0; i < mask.rows; i++)
				{
					for (int j = 0; j < mask.cols; j++)
					{
						if (frame0.rows>i && frame0.cols>j)
						{
							mask.at<cv::Vec3b>(i, j) = labels.at<int>(i*frame0.cols + j) ? frame0.at<cv::Vec3b>(i,j) : frame1.at<cv::Vec3b>(i,j);
						}
						else
						{
							mask.at<cv::Vec3b>(i, j) = frame1.at<cv::Vec3b>(i, j);
						}
					}
				}
				//std::cout << frame0.cols << " " << frame0.rows << std::endl;
				//std::cout << frame1.cols << " " << frame1.rows << std::endl;
				cv::imshow("video0", frame0);
				cv::imshow("video1", frame1);
				cv::imshow("video2", mask);
				cv::waitKey(10);
			}
			else
			{
				break;
			}
	}
}