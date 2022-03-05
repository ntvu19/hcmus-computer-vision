#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "GlobalProcess.h"
using namespace cv;
using namespace std;

class Convolution
{
private:
	vector<float> _kernel;
public:
	vector<float> GetKernel();
	void SetKernel(vector<float> kernel);

	/*
	* Apply convolution for the image functions using defined kernel
	* srcImg: input image
	* dstImg: output image
	* return:
	*		false: failed
	*		true: successed
	*/
	//vector<vector<int>> DoConvolution(const Mat& srcImg);
	Mat DoConvolution(const Mat& srcImg);
	Convolution();
	~Convolution();
};

