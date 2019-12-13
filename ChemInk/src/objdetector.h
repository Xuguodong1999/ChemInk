#pragma once

#include <QImage>
#include <opencv2/dnn.hpp>
#include <vector>

class ObjDetector {
public:
	ObjDetector();
	void setThreshHold(float _confThreshold, float _nmsThreshold);
	void load(const char* weights, const char* cfg);
	//  ��img��Ԥ����������indices������indices������boxes��confidences��classIds��ý��
	//  ����ͼ��Ԥ���Ƕ��̵߳ģ�����ֹ���̵߳��õ���ͼ��Ԥ�⣬����ͼ����һ��һ����
	void predictSingle(const QImage& img);

	std::vector<int> classIds;
	std::vector<float> confidences;
	std::vector<cv::Rect> boxes;
	std::vector<int> indices;
private:
	cv::dnn::Net net;
	std::vector<cv::String> outBlobNames;
	void nonMaximumSuppression(const cv::Mat& frame, const std::vector<cv::Mat>& outs);
	int outdim;
	float confThreshold;
	float nmsThreshold;
};
