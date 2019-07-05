#include "filereader.h"
#include "pixel.h"

FileReader::FileReader() {

	pixelObjArray = {{0 , 1 , 0 , 0 , 1 },
				     {12, 1 , 0 , 0, 1 },
				     {0 , 1 , 1 , 1 , 1},
					 {0 , 1 , 255, 0 , 0},
					 {0 , 1 , 1 , 1 , 0}};

	this->imageHeight = 5;
	this->imageWidth = 5;
	/*pixelObjArray = std::vector<std::vector<int>>(imageHeight, std::vector <int>(imageWidth));

	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			int random = rand() % 255;
			pixelObjArray[i][j] = random;
		}
	}*/
}

std::vector<std::vector<int>> FileReader::getPixelArray() {
	return this->pixelObjArray;
}

void FileReader::createPixelArray() {
	for (int m = 0; m < getImageHeight(); m++) {
		for (int n = 0; n < getImageWidth(); n++) {
			Pixel p = Pixel(m,n,-1,-1);
		}
	}
}

int FileReader::getImageHeight() {
	return this->imageHeight;
}

int FileReader::getImageWidth() {
	return this->imageWidth;
}