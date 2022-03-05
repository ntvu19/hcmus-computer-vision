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

vector<vector<int>> Convolution::DoConvolution(const Mat& srcImg) {
	// Apply convolution
	int width = srcImg.rows,
		height = srcImg.cols;
	vector<vector<int>> dstImg;
	dstImg.resize(width);
	for (int i = 0; i < dstImg.size(); i++) {
		dstImg[i].resize(height);
	}


	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
			// Convolution
			int pixelValue = 0;
			for (int y = 0; y < 3; y++) {
				for (int x = 0; x < 3; x++) {
					pixelValue += int(srcImg.at<uchar>(i + y - 1, j + x - 1) * this->_kernel[y * 3 + x]);
				}
			}
			dstImg[i - 1][j - 1] = pixelValue;
		}
	}
	return dstImg;
}