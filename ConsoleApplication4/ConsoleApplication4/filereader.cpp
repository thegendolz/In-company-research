#include "filereader.h"
#include "pixel.h"

FileReader::FileReader() {

	pixelObjArray = {{0, 1, 1, 1, 6},
		{12, 1, 1, 26, 6},
		{0, 1, 9, 1, 6},
		{0, 1, 12, 1, 6},
		{0, 1, 1, 1, 6}};
	this->imageHeight = 5;
	this->imageWidth = 5;
}

std::vector<std::vector<int>> FileReader::getPixelArray() {
	return this->pixelObjArray;
}

void FileReader::createPixelArray() {
	for (int n = 0; n < getImageHeight(); n++) {
		for (int m = 0; m < getImageWidth(); m++) {
			Pixel p = Pixel(m,n,-1);
		}
	}
}

int FileReader::getImageHeight() {
	return this->imageHeight;
}

int FileReader::getImageWidth() {
	return this->imageWidth;
}