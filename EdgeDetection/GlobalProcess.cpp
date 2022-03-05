#include "GlobalProcess.h"

GlobalProcess::GlobalProcess() {
	// Constructor

}

GlobalProcess::~GlobalProcess() {
	// Destructor

}

Mat GlobalProcess::createNZeroPadding(const Mat& srcImg, int paddingValue) {
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
