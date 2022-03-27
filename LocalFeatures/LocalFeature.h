#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

class LocalFeature
{
public:
	/*
	* Local feature class for image
	* srcImg: input image
	* dstImg: output image
	* return:
	*		0: failed
	*		1: successed
	*/
	Mat detectHarris(const Mat& srcImg);
	Mat detectBlob(const Mat& srcImg);
	Mat detectDOG(const Mat& srcImg);
	double matchBySIFT(const Mat& img1, const Mat& img2, int detector);
	LocalFeature();
	~LocalFeature();
};

