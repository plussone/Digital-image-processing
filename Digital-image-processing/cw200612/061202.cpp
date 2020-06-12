/*openpose����*/
#include "head.h"

// key point ���ӱ�, [model_id][pair_id][from/to]
int POSE_PAIRS[3][20][2] = {
	{   // COCO body
		{ 1,2 },{ 1,5 },{ 2,3 },
		{ 3,4 },{ 5,6 },{ 6,7 },
		{ 1,8 },{ 8,9 },{ 9,10 },
		{ 1,11 },{ 11,12 },{ 12,13 },
		{ 1,0 },{ 0,14 },
		{ 14,16 },{ 0,15 },{ 15,17 }
	},
	{   // MPI body
		{ 0,1 },{ 1,2 },{ 2,3 },
		{ 3,4 },{ 1,5 },{ 5,6 },
		{ 6,7 },{ 1,14 },{ 14,8 },{ 8,9 },
		{ 9,10 },{ 14,11 },{ 11,12 },{ 12,13 }
	},
	{   // hand
		{ 0,1 },{ 1,2 },{ 2,3 },{ 3,4 },         // thumb
		{ 0,5 },{ 5,6 },{ 6,7 },{ 7,8 },         // pinkie
		{ 0,9 },{ 9,10 },{ 10,11 },{ 11,12 },    // middle
		{ 0,13 },{ 13,14 },{ 14,15 },{ 15,16 },  // ring
		{ 0,17 },{ 17,18 },{ 18,19 },{ 19,20 }   // small
	} };

void test061202()
{
	//��������ģ�ͺ�Ȩ���ļ�
	std::string modelTxt = "D:\\openpose_pose_coco.prototxt";
	std::string modelBin = "D:\\caffe_models\\pose\\coco\\pose_iter_440000.caffemodel";

	cv::dnn::Net net = cv::dnn::readNetFromCaffe(modelTxt, modelBin);

	int W_in = 368;
	int H_in = 368;
	float thresh = 0.1;

	cv::VideoCapture cap0;
	cap0.open("D:\\b.mp4");

	if (!cap0.isOpened())return ;

	while (1) {
		cv::Mat frame;
		cap0 >> frame;
		if (frame.empty()) {
			std::cout << "frame is empty!!!" << std::endl;
			return ;
		}

		//��������
		cv::Mat inputBlob = cv::dnn::blobFromImage(frame, 1.0 / 255, cv::Size(W_in, H_in), cv::Scalar(0, 0, 0), false, false);

		//����
		net.setInput(inputBlob);

		//�õ����������������Ϊ����ͼ
		cv::Mat result = net.forward();

		int midx, npairs;
		int H = result.size[2];
		int W = result.size[3];

		//�õ�������Ĺؼ������
		int nparts = result.size[1];


		// find out, which model we have
		//�ж������ģ�����
		if (nparts == 19)
		{   // COCO body
			midx = 0;
			npairs = 17;
			nparts = 18; // skip background
		}
		else if (nparts == 16)
		{   // MPI body
			midx = 1;
			npairs = 14;
		}
		else if (nparts == 22)
		{   // hand
			midx = 2;
			npairs = 20;
		}
		else
		{
			std::cerr << "there should be 19 parts for the COCO model, 16 for MPI, or 22 for the hand one, but this model has " << nparts << " parts." << std::endl;
			return ;
		}

		// ����������������
		std::vector<cv::Point> points(22);
		for (int n = 0; n < nparts; n++)
		{
			// Slice heatmap of corresponding body's part.
			cv::Mat heatMap(H, W, CV_32F, result.ptr(0, n));
			// �ҵ����ֵ�ĵ�
			cv::Point p(-1, -1), pm;
			double conf;
			minMaxLoc(heatMap, 0, &conf, 0, &pm);
			//�ж����Ŷ�
			if (conf > thresh) {
				p = pm;
			}
			points[n] = p;
		}

		//��������������֣����һ���
		float SX = float(frame.cols) / W;
		float SY = float(frame.rows) / H;
		for (int n = 0; n < npairs; n++)
		{
			cv::Point2f a = points[POSE_PAIRS[midx][n][0]];
			cv::Point2f b = points[POSE_PAIRS[midx][n][1]];

			//���ǰһ������û���ҵ���Ӧ�ĵ㣬������
			if (a.x <= 0 || a.y <= 0 || b.x <= 0 || b.y <= 0)
				continue;

			// ������ͼ��ĳߴ�
			a.x *= SX; a.y *= SY;
			b.x *= SX; b.y *= SY;

			//����
			line(frame, a, b, cv::Scalar(0, 200, 0), 2);
			circle(frame, a, 3, cv::Scalar(0, 0, 200), -1);
			circle(frame, b, 3, cv::Scalar(0, 0, 200), -1);
		}

		cv::imshow("frame", frame);
		cv::waitKey(30);

	}

	return ;
}
