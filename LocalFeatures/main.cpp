#include "LocalFeature.h"
#include <iostream>
#include <string>
using namespace std;

// <Program.exe> <InputFilePath> <OutputFilePath> <method>
int main(int argc, char** argv) {

	// Read arguments
	string inputPath = string(argv[1]);
	string outputPath = string(argv[2]);
	string method = string(argv[3]);

	// Initialize image using OpenCV
	Mat srcImg = imread(inputPath, IMREAD_COLOR);
	Mat dstImg;

	// Check the source image is empty
	if (!srcImg.data) {
		cout << "Could not read image!" << endl;
		return 1;
	}

	// LocalFeature object
	LocalFeature* localFeature = new LocalFeature();

	// Processing image
	if (method == "-harris") {
		Mat harrisImg = localFeature->detectHarris(srcImg);
		if (harrisImg.data) {
			imwrite(outputPath, harrisImg);
		}
		else {
			cout << "Could not detect the local feature of this image" << endl;
			return 1;
		}
	}
	else if (method == "-blob") {
		Mat blobImg = localFeature->detectBlob(srcImg);
		if (blobImg.data) {
			imwrite(outputPath, blobImg);
		}
		else {
			cout << "Could not detect the local feature of this image" << endl;
			return 1;
		}
	}
	else if (method == "-dog") {
		Mat dogImg = localFeature->detectDOG(srcImg);
		if (dogImg.data) {
			imwrite(outputPath, dogImg);
		}
		else {
			cout << "Could not detect the local feature of this image" << endl;
			return 1;
		}
	}
	else if (string(argv[4]) == "-sift") {
		string inputPath1 = string(argv[1]);
		string inputPath2 = string(argv[2]);
		string outputPath = string(argv[3]);
		Mat srcImg1 = imread(inputPath1, IMREAD_COLOR);
		Mat srcImg2 = imread(inputPath2, IMREAD_COLOR);
		Mat dstImg = localFeature->matchBySIFT(srcImg1, srcImg2);
		if (dstImg.data) {
			imwrite(outputPath, dstImg);
		}
		else {
			cout << "Could not detect the local feature of this image" << endl;
			return 1;
		}
	}
	else {
		cout << "Invalid method, please again!" << endl;
		delete localFeature;
		return 1;
	}

	delete localFeature;
	waitKey(0);
	return 0;
}