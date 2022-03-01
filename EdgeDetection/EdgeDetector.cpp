#include "EdgeDetector.h"
#include "Convolution.h"

EdgeDetector::EdgeDetector() {
	// Constructor

}

EdgeDetector::~EdgeDetector() {
	// Deconstructor

}

// Sobel
int EdgeDetector::detectBySobel(const Mat& srcImg, Mat& dstImg) {
	// Zero-padding
	int width = srcImg.rows,
		height = srcImg.cols;
	Mat zeroPaddingImg(width + 2, height + 2, CV_8UC1, Scalar(0, 0, 0));
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			zeroPaddingImg.at<uchar>(i + 1, j + 1) = srcImg.at<uchar>(i, j);
		}
	}
	
	Convolution* convolution = new Convolution();
	// X-direction
	Mat xDerivateImg(width, height, CV_8UC1, Scalar(0, 0, 0));
	vector<float> xSobelKernel = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	convolution->SetKernel(xSobelKernel);
	convolution->DoConvolution(zeroPaddingImg, xDerivateImg);
	//imshow("X-direction", xDerivateImg);

	// Y-direction
	Mat yDerivateImg(width, height, CV_8UC1, Scalar(0, 0, 0));
	vector<float> ySobelKernel = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	convolution->SetKernel(ySobelKernel);
	convolution->DoConvolution(zeroPaddingImg, yDerivateImg);
	//imshow("Y-direction", yDerivateImg);

	// Final image (result)
	float threshold = 25;
	dstImg = Mat(width, height, CV_8UC1);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			float gx = xDerivateImg.at<uchar>(i, j);
			float gy = yDerivateImg.at<uchar>(i, j);
			float gValue = sqrt(gx * gx + gy * gy);
			if (gValue <= threshold) {
				dstImg.at<uchar>(i, j) = 0;
			}
			else {
				dstImg.at<uchar>(i, j) = 255;
			}
		}
	}
	delete convolution;
	return 1;
}

int EdgeDetector::detectByPrewitt(const Mat& srcImg, Mat& dstImg) {
	// Prewitt

}

int EdgeDetector::detectByLaplace(const Mat& srcImg, Mat& dstImg) {
	// Laplace

}

int EdgeDetector::detectByCanny(const Mat& srcImg, Mat& dstImg) {
	// Canny

}