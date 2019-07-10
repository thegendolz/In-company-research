#include "filereader.h"
#include "pixel.h"

FileReader::FileReader() {

	/*pixelObjArray = {{0 , 1 , 0 , 0, 1 },
				     {12, 1 , 0 , 0, 1 },
				     {0 , 1 , 1 , 1 , 1},
					 {0 , 1 , 12, 0 , 0},
					 {0 , 1 , 1 , 1 , 0}};

	this->imageHeight = 5;
	this->imageWidth = 5;*/
	this->imageHeight = 500;
	this->imageWidth = 500; 
	
	pixelObjArray = std::vector<std::vector<int>>(imageHeight, std::vector <int>(imageWidth));

	for (int i = 0; i < imageHeight; i++) {
		for (int j = 0; j < imageWidth; j++) {
			int random = rand() % 255;
			//printf("%d \n", random);
			pixelObjArray[i][j] = random;
		}
	}
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