/*yolov3����*/
#include "head.h"

std::vector<std::string> classes;

float confThreshold = 0.5; // Confidence threshold
float nmsThreshold = 0.4;  // Non-maximum suppression threshold
int inpWidth = 416;        // Width of network's input image
int inpHeight = 416;       // Height of network's input image

std::vector<cv::String> getOutputsNames(const cv::dnn::Net& net)
{
	static std::vector<cv::String> names;
	if (names.empty())
	{
		//Get the indices of the output layers, i.e. the layers with unconnected outputs
		std::vector<int> outLayers = net.getUnconnectedOutLayers();

		//get the names of all the layers in the network
		std::vector<cv::String> layersNames = net.getLayerNames();

		// Get the names of the output layers in names
		names.resize(outLayers.size());
		for (size_t i = 0; i < outLayers.size(); ++i)
			names[i] = layersNames[outLayers[i] - 1];
	}
	return names;
}

//���������
void drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame)
{
	//���Ƽ���
	cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(0, 0, 255));
	//���ʶ�����������ƣ��Լ����Ŷ�
	std::string label = cv::format("%.2f", conf);
	if (!classes.empty())
	{
		CV_Assert(classId < (int)classes.size());
		label = classes[classId] + ":" + label;
	}
	else
	{
		std::cout << "classes is empty..." << std::endl;
	}
	//���Ʊ�ǩ
	int baseLine;
	cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 2, &baseLine);
	top = std::max(top, labelSize.height);
	cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
}

//�Ǽ���ֵ���ƣ�ȥ�����ŶȽ�С�ļ����
void postprocess(cv::Mat& frame, std::vector<cv::Mat>& outs)
{
	std::vector<int> classIds;
	std::vector<float> confidences;
	std::vector<cv::Rect> boxes;

	for (size_t i = 0; i < outs.size(); ++i)
	{
		// Scan through all the bounding boxes output from the network and keep only the
		// ones with high confidence scores. Assign the box's class label as the class
		// with the highest score for the box.
		//
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			cv::Point classIdPoint;
			double confidence;

			//��õ÷���ߵĽ���ķ�ֵ��λ��
			cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

			if (confidence > confThreshold)
			{
				int centerX = (int)(data[0] * frame.cols);
				int centerY = (int)(data[1] * frame.rows);
				int width = (int)(data[2] * frame.cols);
				int height = (int)(data[3] * frame.rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(cv::Rect(left, top, width, height));
			}
		}
	}

	//�Ǽ���ֵ���ƣ�ȥ�����ŶȽ�С�ļ����
	std::vector<int> indices;
	cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		cv::Rect box = boxes[idx];
		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, frame);
	}
}

//opencv ���� yolov3 demo
void test061201()
{
	cv::VideoCapture cap("D://a.mp4");
	if (!cap.isOpened())return ;

	//coco���ݼ��������ļ���80��
	std::string classesFile = "D:\\coco.names";
	//yolov3����ģ���ļ�
	std::string yolov3_model = "D:\\yolov3.cfg";
	//Ȩ��
	std::string weights = "D:\\yolov3.weights";

	//��coco.names�е�80������ת��Ϊvector��ʽ
	std::ifstream classNamesFile(classesFile.c_str());
	if (classNamesFile.is_open())
	{
		std::string className = "";
		// getline (istream&  is, string& str)
		//isΪ���룬��is�ж�ȡ��ȡ���ַ���������string���͵�str�У����û�ж����ַ�����false��ѭ������
		while (std::getline(classNamesFile, className)) {
			classes.push_back(className);
		}
	}
	else {
		std::cout << "can not open classNamesFile" << std::endl;
	}

	cv::dnn::Net net = cv::dnn::readNetFromDarknet(yolov3_model, weights);

	net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
	net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

	cv::Mat frame;

	while (1)
	{
		cap >> frame;

		if (frame.empty()) {
			std::cout << "frame is empty!!!" << std::endl;
			return ;
		}

		//����yolo��������
		cv::Mat blob;
		cv::dnn::blobFromImage(frame, blob, 1 / 255.0, cv::Size(inpWidth, inpHeight), cv::Scalar(0, 0, 0), true, false);

		//��������
		net.setInput(blob);

		//������������������
		std::vector<cv::Mat> outs;
		//ǰ�����ý��
		net.forward(outs, getOutputsNames(net));

		//�����Ǽ���ֵ���ƣ����Ƽ���
		postprocess(frame, outs);

		cv::imshow("frame", frame);
		if (cv::waitKey(10) == 27)
		{
			break;
		}
	}

}