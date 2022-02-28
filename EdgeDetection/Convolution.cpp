#include "Convolution.h"

Convolution::Convolution() {
	// Constructor

}

Convolution::~Convolution() {
	// Destructor

}

vector<float> Convolution::GetKernel() {
	return this->_kernel;
}

void SetKernel(vector<float> kernel, int kWidth, int kHeight) {
	
}

int Convolution::DoConvolution(const Mat& srcImg, Mat& dstImg) {
	// Apply convolution

}