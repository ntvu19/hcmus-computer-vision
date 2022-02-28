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
	int _kernelWidth;
	int _kernalHeight;
public:
	vector<float> GetKernel();
	void SetKernel(vector<float> kernel, int kWidth, int kHeight);

	/*
	* Apply convolution for the image functions using defined kernel
	* srcImg: input image
	* dstImg: output image
	* return:
	*		false: failed
	*		true: successed
	*/
	int DoConvolution(const Mat& srcImg, Mat& dstImg);
	Convolution();
	~Convolution();
};

