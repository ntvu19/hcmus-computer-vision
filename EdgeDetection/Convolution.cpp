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

Mat Convolution::createZeroPadding(const Mat& srcImg, int paddingValue) {
	int width = srcImg.cols,
		height = srcImg.rows;
	Mat zeroPadding(height + paddingValue * 2, width + paddingValue * 2, CV_8UC1, Scalar(0, 0, 0));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			zeroPadding.at<uchar>(i + paddingValue, j + paddingValue) = srcImg.at<uchar>(i, j);
		}
	}
	return zeroPadding;
}

Mat Convolution::DoConvolution(const Mat& srcImg) {
	// Zero padding
	int kernelEdge = (int)sqrt(this->_kernel.size());
	int padding = kernelEdge / 2;
	Mat zeroPadding = this->createZeroPadding(srcImg, padding);
	// Apply convolution
	int height = zeroPadding.rows,
		width = zeroPadding.cols;
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