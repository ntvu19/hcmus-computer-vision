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
	vector<vector<int>> xDerivateImg;
	vector<float> xSobelKernel = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	convolution->SetKernel(xSobelKernel);
	xDerivateImg = convolution->DoConvolution(zeroPaddingImg);
	//imshow("X-direction", xDerivateImg);

	// Y-direction
	vector<vector<int>> yDerivateImg;
	vector<float> ySobelKernel = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	convolution->SetKernel(ySobelKernel);
	yDerivateImg = convolution->DoConvolution(zeroPaddingImg);
	//imshow("Y-direction", yDerivateImg);

	// Final image (result)
	dstImg = srcImg.clone();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int gx = xDerivateImg[i][j];
			int gy = yDerivateImg[i][j];
			int gValue = sqrt(gx * gx + gy * gy);
			gValue = (gValue > 255) ? 255 : gValue;
			gValue = (gValue < 0) ? 0 : gValue;
			dstImg.at<uchar>(i, j) = gValue;
		}
	}
	delete convolution;
	return 1;
}

// Prewitt
int EdgeDetector::detectByPrewitt(const Mat& srcImg, Mat& dstImg) {
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
	vector<vector<int>> xDerivateImg;
	vector<float> xPrewittKernel = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
	convolution->SetKernel(xPrewittKernel);
	xDerivateImg = convolution->DoConvolution(zeroPaddingImg);
	//imshow("X-direction", xDerivateImg);

	// Y-direction
	vector<vector<int>> yDerivateImg;
	vector<float> yPrewittKernel = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };
	convolution->SetKernel(yPrewittKernel);
	yDerivateImg = convolution->DoConvolution(zeroPaddingImg);
	//imshow("Y-direction", yDerivateImg);

	// Final image (result)
	dstImg = srcImg.clone();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int gx = xDerivateImg[i][j];
			int gy = yDerivateImg[i][j];
			int gValue = sqrt(gx * gx + gy * gy);
			gValue = (gValue > 255) ? 255 : gValue;
			gValue = (gValue < 0) ? 0 : gValue;
			dstImg.at<uchar>(i, j) = gValue;
		}
	}
	delete convolution;
	return 1;
}

//Laplace
int EdgeDetector::detectByLaplace(const Mat& srcImg, Mat& dstImg) {
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

	vector<vector<int>> DerivateImg;
	vector<float> LaplacelKernel = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };
	convolution->SetKernel(LaplacelKernel);
	DerivateImg = convolution->DoConvolution(zeroPaddingImg);

	// Final image (result)
	dstImg = srcImg.clone();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			float gValue = DerivateImg[i][j] * 2;
			gValue = (gValue > 255) ? 255 : gValue;
			gValue = (gValue < 0) ? 0 : gValue;
			dstImg.at<uchar>(i, j) = gValue;
		}
	}
	delete convolution;
	return 1;
}

//Canny
int EdgeDetector::detectByCanny(const Mat& srcImg, Mat& dstImg) {
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
	vector<vector<int>> xDerivateImg;
	vector<float> xCannyKernel = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	convolution->SetKernel(xCannyKernel);
	xDerivateImg = convolution->DoConvolution(zeroPaddingImg);
	//imshow("X-direction", xDerivateImg);

	// Y-direction
	vector<vector<int>> yDerivateImg;
	vector<float> yCannyKernel = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	convolution->SetKernel(yCannyKernel);
	yDerivateImg = convolution->DoConvolution(zeroPaddingImg);
	//imshow("Y-direction", yDerivateImg);

	vector<vector<float>> gValue, dValue;
	gValue.assign(width, vector<float>(height, 0));
	dValue.assign(width, vector<float>(height, 0));

	// step-1: Cal Gradient and the direction of gradient
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int x = xDerivateImg[i][j];
			int y = yDerivateImg[i][j];
			gValue[i][j] = sqrt(x * x + y * y);
			dValue[i][j] = (atan(static_cast<float>(y) / x) * 180) / 3.14;
			if (dValue[i][j] <= 22.5 || dValue[i][j] >= 157.5) {
				dValue[i][j] = 0;
			}
			else
				if (dValue[i][j] > 22.5 && dValue[i][j] < 67.5) {
					dValue[i][j] = 45;
				}
				else
					if (dValue[i][j] >= 67.5 && dValue[i][j] < 112.5) {
						dValue[i][j] = 90;
					}
					else
						if (dValue[i][j] > 122.5 && dValue[i][j] < 157.5) {
							dValue[i][j] = 135;
						}

		}
	}

	// step-2: Non-maximum Suppression
	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
			float angle = dValue[i][j];
			if (angle == 0 && gValue[i][j] < max(gValue[i + 1][j], gValue[i - 1][j])) {
				gValue[i][j] = 0;
			}
			if (angle == 45 && gValue[i][j] < max(gValue[i + 1][j + 1], gValue[i - 1][j - 1])) {
				gValue[i][j] = 0;
			}
			if (angle == 90 && gValue[i][j] < max(gValue[i][j + 1], gValue[i][j - 1])) {
				gValue[i][j] = 0;
			}
			if (angle == 135 && gValue[i][j] < max(gValue[i + 1][j - 1], gValue[i - 1][j + 1])) {
				gValue[i][j] = 0;
			}

		}
	}


	// Final image (result)
	dstImg = srcImg.clone();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int gx = xDerivateImg[i][j];
			int gy = yDerivateImg[i][j];
			// calculate gradient
			int g = gValue[i][j];
			g = (g > 255) ? 255 : g;
			g = (g < 0) ? 0 : g;
			dstImg.at<uchar>(i, j) = g;
		}
	}

	delete convolution;
	return 1;
}