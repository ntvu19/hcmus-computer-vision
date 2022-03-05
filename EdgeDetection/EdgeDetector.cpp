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
	int width = srcImg.rows,
		height = srcImg.cols;
	Convolution* convolution = new Convolution();

	// X-direction
	vector<float> xSobelKernel = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	convolution->SetKernel(xSobelKernel);
	Mat xDerivateImg = convolution->DoConvolution(srcImg);
	//imshow("X-direction", xDerivateImg);

	// Y-direction
	vector<float> ySobelKernel = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	convolution->SetKernel(ySobelKernel);
	Mat yDerivateImg = convolution->DoConvolution(srcImg);
	//imshow("Y-direction", yDerivateImg);

	// Final image (result)
	dstImg = srcImg.clone();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int gx = xDerivateImg.at<int>(i, j);
			int gy = yDerivateImg.at<int>(i, j);
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
	int width = srcImg.rows,
		height = srcImg.cols;
	Convolution* convolution = new Convolution();

	// X-direction
	vector<float> xPrewittKernel = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
	convolution->SetKernel(xPrewittKernel);
	Mat xDerivateImg = convolution->DoConvolution(srcImg);
	//imshow("X-direction", xDerivateImg);

	// Y-direction
	vector<float> yPrewittKernel = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };
	convolution->SetKernel(yPrewittKernel);
	Mat yDerivateImg = convolution->DoConvolution(srcImg);
	//imshow("Y-direction", yDerivateImg);

	// Final image (result)
	dstImg = srcImg.clone();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int gx = xDerivateImg.at<int>(i, j);
			int gy = yDerivateImg.at<int>(i, j);
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
	int width = srcImg.rows,
		height = srcImg.cols;
	Convolution* convolution = new Convolution();

	vector<float> LaplacelKernel = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };
	convolution->SetKernel(LaplacelKernel);
	Mat DerivateImg = convolution->DoConvolution(srcImg);

	// Final image (result)
	dstImg = srcImg.clone();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			float gValue = DerivateImg.at<int>(i, j) * 2;
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
	int width = srcImg.rows,
		height = srcImg.cols;
	Convolution* convolution = new Convolution();

	// Step 1: Gaussian Blur
	// The below filter is the gaussian filter matrix with sigma = 1.4 => Matrix * (1 / 159)
	vector<float> gaussianFilter = { 0.01257862, 0.02515723 ,0.03144654 ,0.02515723 ,0.01257862 ,0.02515723 ,0.05660377 ,0.0754717  ,0.05660377 ,0.02515723,0.03144654 ,0.0754717  ,0.09433962 ,0.0754717  ,0.03144654,0.02515723 ,0.05660377 ,0.0754717  ,0.05660377 ,0.02515723,0.01257862 ,0.02515723 ,0.03144654 ,0.02515723 ,0.01257862 };
	convolution->SetKernel(gaussianFilter);
	Mat bluredImg = convolution->DoConvolution(srcImg);
	bluredImg.convertTo(bluredImg, CV_8UC1);

	// Step 2: Computing gradients and the directions of gradient
	// * Gradients
	// X-direction
	vector<float> xCannyKernel = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	convolution->SetKernel(xCannyKernel);
	Mat xDerivateImg = convolution->DoConvolution(bluredImg);
	//imshow("X-direction", xDerivateImg);

	// Y-direction
	vector<float> yCannyKernel = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	convolution->SetKernel(yCannyKernel);
	Mat yDerivateImg = convolution->DoConvolution(bluredImg);
	//imshow("Y-direction", yDerivateImg);

	vector<vector<float>> gValue, dValue;
	gValue.assign(width, vector<float>(height, 0));
	dValue.assign(width, vector<float>(height, 0));

	// * Directions of the gradient
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int x = xDerivateImg.at<int>(i, j);
			int y = yDerivateImg.at<int>(i, j);
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

	// Step 3: Non-maximum Suppression
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
			int gx = xDerivateImg.at<int>(i, j);
			int gy = yDerivateImg.at<int>(i, j);
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