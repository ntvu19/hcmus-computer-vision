#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class EdgeDetector
{
public:
	/*
	 * Edge detector class for image
	 * srcImg: input image
	 * dstImg: output image
	 * return:
	 *		0: failed
	 *		1: successed
	*/
	int detectBySobel(const Mat& srcImg, Mat& dstImg);
	int detectByPrewitt(const Mat& srcImg, Mat& dstImg);
	int detectByLaplace(const Mat& srcImg, Mat& dstImg);
	int detectByCanny(const Mat& srcImg, Mat& dstImg);
	EdgeDetector();
	~EdgeDetector();
};