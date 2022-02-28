#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

class EdgeDetector
{
public:
	/*
	 * Edge detector class for image
	 * srcImg: input image
	 * dstImg: output image
	 * method:
	 *		1: Sobel
	 *		2: Prewitt
	 *		3: Laplace
	 *		4: Canny
	 * return:
	 *		false: failed
	 *		true: successed
	*/
	int DetectEdge(const Mat& srcImg, Mat& dstImg, int method);
	EdgeDetector();
	~EdgeDetector();
};

