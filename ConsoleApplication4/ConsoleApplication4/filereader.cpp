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

	/*pixelObjArray = {{0 , 1 , 0 , 0, 1 },
				     {12, 1 , 0 , 0, 1 },
				     {0 , 1 , 1 , 1 , 1},
					 {0 , 1 , 12, 0 , 0},
					 {0 , 1 , 1 , 1 , 0}};

	this->imageHeight = 5;
	this->imageWidth = 5;*/
	/*this->imageHeight = 500;
	this->imageWidth = 500; 
	
	pixelObjArray = std::vector<std::vector<int>>(imageHeight, std::vector <int>(imageWidth));

	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			int random = rand() % 255;
			//printf("%d \n", random);
			pixelObjArray[i][j] = random;
		}
	}*/

	
	Mat img = imread("test.png", 0);

	if (!img.data) {
		//printf("%d \n", img[0][0])
		printf("Image not working");
		exit(1);
	}

	printf("Reading Image ... \n");
	//img.data;
	//namedWindow("image", WINDOW_NORMAL);
	//imshow("image", img);
	//waitKey(0);

	this->imageHeight = img.rows;
	this->imageWidth = img.cols;

	printf("height: %d \n", this->imageHeight);
	printf("width: %d \n", this->imageWidth);

	std::vector<uchar> array;
	if (img.isContinuous()) {
		array.assign((uchar*)img.datastart, (uchar*)img.dataend);
	}
	else {
		for (int i = 0; i < img.rows; ++i) {
			array.insert(array.end(), img.ptr<uchar>(i), img.ptr<uchar>(i) + img.cols);
		}
	}

	for (int i = 0; i < this->imageHeight; i++) {
		for (int j = 0; j < 20; j++) {
			if (j == 19) {
				printf("%d\n", array.at(i+j));
				//printf("%d\n", ap.getPixel(i, j).id);
			}
			else {
				printf("%d - ", array.at(i + j));
				
			}
		}
	}
	//printf("%d", array.at(0));
	
}

std::vector<std::vector<int>> FileReader::getPixelArray() {
	return this->pixelObjArray;
}

int FileReader::getImageHeight() {
	return this->imageHeight;
}

int FileReader::getImageWidth() {
	return this->imageWidth;
}