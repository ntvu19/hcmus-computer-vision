#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
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
	*		0: failed
	*		1: successed
	*/
	int DoConvolution(Mat& srcImg, Mat& dstImg);
	Convolution();
	~Convolution();
};

