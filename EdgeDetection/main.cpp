#include "Convolution.h"
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
	Mat srcImg = imread(inputPath, IMREAD_COLOR);
	Mat dstImg;

	// Check the source image is empty
	if (!srcImg.data) {
		cout << "Could not read image!" << endl;
		return 1;
	}

	// EdgeDetector object
	EdgeDetector *edgeDetector = new EdgeDetector();

	// Processing image
	if (method == "-sobel") {
		// Sobel

	}
	else if (method == "-prewitt") {
		// Prewitt

	}
	else if (method == "-laplace") {
		// Laplace

	}
	else if (method == "-canny") {
		// Canny

	}
	else {
		cout << "Invalid method, please again!" << endl;
		delete edgeDetector;
		return 1;
	}


	// Show image
	//imshow("Image", dstImg);

	// Save image
	//imwrite(outputPath, dstImg);
	waitKey(0);
	delete edgeDetector;
	return 0;
}