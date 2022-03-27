#include "EdgeDetector.h"
#include <iostream>
#include <string>
using namespace std;

// <Program.exe> <InputFilePath> <OutputFilePath> <method>
int main(int argc, char** argv) {

	// Read arguments
	string inputPath = string(argv[1]);
	string outputPath = string(argv[2]);
	string method = string(argv[3]);

	// Initialize image by OpenCV
	Mat srcImg = imread(inputPath, IMREAD_GRAYSCALE);
	Mat dstImg;

	// Check the source image is empty
	if (!srcImg.data) {
		cout << "Could not read image!" << endl;
		return 1;
	}

	// EdgeDetector object
	EdgeDetector* edgeDetector = new EdgeDetector();

	// Processing image
	if (method == "-sobel") {
		// Sobel
		if (edgeDetector->detectBySobel(srcImg, dstImg)) {
			imwrite(outputPath, dstImg);
		}
	}
	else if (method == "-prewitt") {
		// Prewitt
		if (edgeDetector->detectByPrewitt(srcImg, dstImg)) {
			imwrite(outputPath, dstImg);
		}
	}
	else if (method == "-laplace") {
		// Laplace
		if (edgeDetector->detectByLaplace(srcImg, dstImg)) {
			imwrite(outputPath, dstImg);
		}

	}
	else if (method == "-canny") {
		// Canny
		if (edgeDetector->detectByCanny(srcImg, dstImg)) {
			imwrite(outputPath, dstImg);
		}

	}
	else {
		cout << "Invalid method, please again!" << endl;
		delete edgeDetector;
		return 1;
	}
	delete edgeDetector;
	waitKey(0);
	return 0;
}