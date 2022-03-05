#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

class GlobalProcess
{
public:
	static Mat createNZeroPadding(const Mat& srcImg, int paddingValue);
	GlobalProcess();
	~GlobalProcess();
};
