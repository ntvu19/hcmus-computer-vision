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

void Convolution::SetKernel(vector<float> kernel) {
	this->_kernel.assign(kernel.begin(), kernel.end());
}

int Convolution::DoConvolution(const Mat& srcImg, Mat& dstImg) {
	// Apply convolution

}