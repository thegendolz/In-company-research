#include "filereader.h"
#include "pixel.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

FileReader::FileReader() {

	Mat img = imread("test_small.png", 1);

	if (!img.data) {
		//printf("%d \n", img[0][0])
		printf("Image not working");
		exit(1);
	}
	printf("Reading Image ... \n");
	this->imageHeight = img.rows;
	this->imageWidth = img.cols;

	printf("height: %d \n", this->imageHeight);
	printf("width: %d \n", this->imageWidth);

	std::vector<cv::Vec3b> pixels(img.rows * img.cols);
	cv::Mat m(img.rows, img.cols, CV_8UC3, &pixels[0]);
	img.copyTo(m);


	pixelObjArray = std::vector<std::vector<std::vector<double>>>(img.rows, std::vector<std::vector<double>>(img.cols, std::vector<double>(3)));

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			double b = (double)img.at<cv::Vec3b>(i, j)[0];
			double g = (double)img.at<cv::Vec3b>(i, j)[1];
			double r = (double)img.at<cv::Vec3b>(i, j)[2];
			std::vector<double> pixel = this->rgbtolab(r, g, b);
			this->pixelObjArray[i][j][0] = pixel[0];
			this->pixelObjArray[i][j][1] = pixel[1];
			this->pixelObjArray[i][j][2] = pixel[2];

		}
	}

	printf("--------[Image: %d]--------\n");
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (j == 15) {
				printf("%d\n", this->pixelObjArray[i][j][0]);
			}
			else {
				printf("%d - ", this->pixelObjArray[i][j][0]);
			}

		}
	}
}

std::vector<double> FileReader::rgbtolab(double r_, double g_, double b_) {
	double x, y, z;
	double r = (r_ / 255.0);
	double g = (g_ / 255.0);
	double b = (b_ / 255.0);



	if (r > 0.04045) r = pow((r + 0.055) / 1.055, 2.4); else r = r / 12.92;
	if (g > 0.04045) g = pow((g + 0.055) / 1.055, 2.4); else g = g / 12.92;
	if (b > 0.04045) b = pow((b + 0.055) / 1.055, 2.4); else b = b / 12.92;

	x = (r * 0.4124 + g * 0.3576 + b * 0.1805) / 0.95047;
	y = (r * 0.2126 + g * 0.7152 + b * 0.0722) / 1.00000;
	z = (r * 0.0193 + g * 0.1192 + b * 0.9505) / 1.08883;

	if (x > 0.008856) x = pow(x, 1.0 / 3.0); else x = (7.787 * x) + 16 / 116;
	if (y > 0.008856) y = pow(y, 1.0 / 3.0); else y = (7.787 * y) + 16 / 116;
	if (z > 0.008856) z = pow(z, 1.0 / 3.0); else z = (7.787 * z) + 16 / 116;
	double n_ = (116.0 * y) - 16;
	double p_ = 500.0 * (x - y);
	double s_ = 200.0 * (y - z);
	return std::vector<double>{(116.0 * y) - 16.0, (500.0 * (x - y)), (200.0 * (y - z))};

}

std::vector<int> FileReader::labtorgb(double l_, double a_, double b_) {
	int y = (l_ + 16.0) / 116.0,
		x =	a_ / 500.0 + y,
		z = y - b_ / 200.0,
		r, g, b;

	x = 0.95047 * ((x * x * x > 0.008856) ? x * x * x : (x - 16 / 116) / 7.787);
	y = 1.00000 * ((y * y * y > 0.008856) ? y * y * y : (y - 16 / 116) / 7.787);
	z = 1.08883 * ((z * z * z > 0.008856) ? z * z * z : (z - 16 / 116) / 7.787);

	r = x * 3.2406 + y * -1.5372 + z * -0.4986;
	g = x * -0.9689 + y * 1.8758 + z * 0.0415;
	b = x * 0.0557 + y * -0.2040 + z * 1.0570;

	r = (r > 0.0031308) ? (1.055 * pow(r, 1 / 2.4) - 0.055) : 12.92 * r;
	g = (g > 0.0031308) ? (1.055 * pow(g, 1 / 2.4) - 0.055) : 12.92 * g;
	b = (b > 0.0031308) ? (1.055 * pow(b, 1 / 2.4) - 0.055) : 12.92 * b;

	return std::vector<int>{ max(0, min(1, r)) * 255, max(0, min(1, g)) * 255, max(0, min(1, b)) * 255};
}

std::vector<std::vector<std::vector<double>>> FileReader::getPixelArray() {
	return this->pixelObjArray;
}

int FileReader::getImageHeight() {
	return this->imageHeight;
}

int FileReader::getImageWidth() {
	return this->imageWidth;
}