#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>
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
	Mat matchBySIFT(const Mat& srcImg1, const Mat& srcImg2);
	LocalFeature();
	~LocalFeature();
};

