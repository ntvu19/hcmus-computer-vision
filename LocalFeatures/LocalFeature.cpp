#include "LocalFeature.h"

LocalFeature::LocalFeature() {
	// Contructor

}

LocalFeature::~LocalFeature() {
	// Destructor

}

Mat LocalFeature::detectHarris(const Mat& srcImg) {
	// Convert to grayscale image
	Mat grayscaleImg;
	cvtColor(srcImg, grayscaleImg, COLOR_BGR2GRAY);

	// Initialize matrix
	double k = 0.04;
	int threshold = 96;
	int height = srcImg.rows,
		width = srcImg.cols;
	Mat featureMap;
	Mat gradientX, gradientY, x2y2, xy, mtrace;
	Mat gradientX2, gradientY2, gradientXY, gradientX2Gaussian, gradientY2Gaussian, gradientXYGaussian;
	
	// Compute X and Y derivative of image using Sobel function
	Sobel(grayscaleImg, gradientX, CV_32FC1, 1, 0, 3);
	Sobel(grayscaleImg, gradientY, CV_32FC1, 0, 1, 3);

	// Calculating other three images in M
	pow(gradientX, 2.0, gradientX2);
	pow(gradientY, 2.0, gradientY2);
	multiply(gradientX, gradientY, gradientXY);

	// Apply gaussian matrix with sigma = 1.5
	GaussianBlur(gradientX2, gradientX2Gaussian, Size(7, 7), 1.5, 0.0);
	GaussianBlur(gradientY2, gradientY2Gaussian, Size(7, 7), 0.0, 1.5);
	GaussianBlur(gradientXY, gradientXYGaussian, Size(7, 7), 1.5, 1.5);

	// Compute R = det(M) - k(traceM)^2
	multiply(gradientX2Gaussian, gradientY2Gaussian, x2y2);
	multiply(gradientXYGaussian, gradientXYGaussian, xy);
	pow(gradientX2Gaussian + gradientY2Gaussian, 2.0, mtrace);
	featureMap = (x2y2 - xy) - k * mtrace;

	Mat dstNorm, dstImg = srcImg.clone();
	normalize(featureMap, dstNorm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((int)dstNorm.at<float>(i, j) > threshold) {
				circle(dstImg, Point(j, i), 2, Scalar(0, 0, 255));
			}
		}
	}
	return dstImg;
}

Mat LocalFeature::detectBlob(const Mat& srcImg) {
	// KeyPoint structure
	struct KeyPoint {
		int x, y;
		double radius;
	};

	// LoG calculate function
	auto LoG = [](const Mat& srcImg, int size, double sigma) {
		Mat dstImg, grayImg;
		GaussianBlur(srcImg, dstImg, Size(size, size), sigma);
		cvtColor(dstImg, grayImg, COLOR_BGR2GRAY);
		Laplacian(grayImg, dstImg, CV_16S, 3);
		dstImg = dstImg.mul(sigma * sigma);
		threshold(dstImg, dstImg, 100, 255, 0);
		convertScaleAbs(dstImg, dstImg);
		return dstImg;
	};

	int height = srcImg.rows,
		width = srcImg.cols;
	vector<KeyPoint> keyPoints;
	Mat LoG_Image[5];
	for (int i = 0; i < 5; i++) {
		LoG_Image[i] = LoG(srcImg, 2 * i + 1, pow(2, i));
	}

	// Find the keypoints
	for (int a = 1; a < 4; a++) {
		for (int i = 0; i < height - 2; i++) {
			for (int j = 0; j < width - 2; j++) {
				// Clone the 3x3 region of the LoG_Image(s)
				Mat region[3];
				for (int p = 0; p < 3; p++) {
					region[p] = Mat(LoG_Image[a + p - 1], Rect(j, i, 3, 3));
				}

				// Max/Min (in 26 neighbors)
				double min0, max0, min1, max1, min2, max2;
				minMaxIdx(region[0], &min0, &max0);
				minMaxIdx(region[1], &min1, &max1);
				minMaxIdx(region[2], &min2, &max2);
				double pixelValue = region[1].at<double>(1, 1);

				if (pixelValue == min1) {
					if (min1 < min0 && min1 < min2) {
						KeyPoint kp;
						kp.x = j + 1;
						kp.y = i + 1;
						kp.radius = pow(2, a) * sqrt(2);
						keyPoints.push_back(kp);
					}
				}
				else if (pixelValue == max1) {
					if (max1 > max0 && max1 > max2) {
						KeyPoint kp;
						kp.x = j + 1;
						kp.y = i + 1;
						kp.radius = pow(2, a) * sqrt(2);
						keyPoints.push_back(kp);
					}
				}
			}
		}
	}

	// Retain the keypoint with the largest radius in the same coordinate
	for (int i = 0; i < keyPoints.size() - 1; i++) {
		for (int j = 1; j < keyPoints.size(); j++) {
			if ((keyPoints[i].x == keyPoints[j].x) && (keyPoints[i].y == keyPoints[j].y)) {
				keyPoints[i].radius > keyPoints[j].radius ?
					keyPoints.erase(keyPoints.begin() + j) : keyPoints.erase(keyPoints.begin() + i);
			}
		}
	}

	// Draw the circle
	Mat dstImg;
	cvtColor(srcImg, dstImg, COLOR_BGR2GRAY);
	cvtColor(dstImg, dstImg, COLOR_GRAY2BGR);
	for (int i = 0; i < keyPoints.size(); i++) {
		circle(dstImg, Point(keyPoints[i].x, keyPoints[i].y), keyPoints[i].radius, Scalar(0, 0, 255), 2);
	}
	return dstImg;
}

Mat LocalFeature::detectDOG(const Mat& srcImg) {
	// Wrong
	Mat g1, g2, result;
	GaussianBlur(srcImg, g1, Size(5, 5), 0.6);
	GaussianBlur(srcImg, g2, Size(5, 5), 4.2);
	result = g1 - g2;
	return result;
}

double LocalFeature::matchBySIFT(const Mat& img1, const Mat& img2, int detector) {

}