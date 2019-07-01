#include "filereader.h"

FileReader::FileReader() {

	pixelObjArray = { {0, 1, 1, 1, 6},
		{12, 1, 1, 26, 6},
		{0, 1, 9, 1, 6},
		{0, 1, 12, 1, 6},
		{0, 1, 1, 1, 6} };

}

std::vector<std::vector<int>> FileReader::getPixelArray() {
	return this->pixelObjArray;
}

void FileReader::createPixelArray() {
	for (int m = 0; m < getImageHeight(); m++) {
		for (int n = 0; n < getImageWidth(); n++) {

		}
	}
}

int FileReader::getImageHeight() {
	return this->imageHeight;
}

int FileReader::getImageWidth() {
	return this->imageWidth;
}