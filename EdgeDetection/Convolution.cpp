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

Mat Convolution::DoConvolution(const Mat& srcImg) {
	// Zero padding
	int kernelEdge = (int)sqrt(this->_kernel.size());
	int padding = kernelEdge / 2;
	Mat zeroPadding = GlobalProcess::createNZeroPadding(srcImg, padding);

	// Apply convolution
	int width = zeroPadding.rows,
		height = zeroPadding.cols;
	Mat dstImg(srcImg.rows, srcImg.cols, CV_32SC1);

	for (int i = padding; i < height - padding; i++) {
		for (int j = padding; j < width - padding; j++) {
			// Convolution
			int pixelValue = 0;
			for (int y = 0; y < kernelEdge; y++) {
				for (int x = 0; x < kernelEdge; x++) {
					pixelValue += int(zeroPadding.at<uchar>(i + y - padding, j + x - padding) * this->_kernel[y * kernelEdge + x]);
				}
			}
			dstImg.at<int>(i - padding, j - padding) = pixelValue;
		}
	}
	return dstImg;
}