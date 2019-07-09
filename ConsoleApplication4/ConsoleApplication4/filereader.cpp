#include "filereader.h"
#include "pixel.h"

FileReader::FileReader() {

	pixelObjArray = {{0 , 1 , 0 , 0 , 1 },
				     {12, 1 , 0 , 0, 1 },
				     {0 , 1 , 1 , 1 , 1},
					 {0 , 1 , 12, 0 , 0},
					 {0 , 1 , 1 , 1 , 0}};

	this->imageHeight = 5;
	this->imageWidth = 5;
	/*this->imageHeight = 1000;
	this->imageWidth = 1000; 
	
	pixelObjArray = std::vector<std::vector<int>>(imageHeight, std::vector <int>(imageWidth));


	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			int random = rand() % 255;
			//printf("%d \n", random);
			pixelObjArray[i][j] = random;
		}
	}*/
}

std::vector<std::vector<int>> FileReader::getPixelArray() {
	return this->pixelObjArray;
}

/*void FileReader::createPixelArray() {
	for (int m = 0; m < getImageHeight(); m++) {
		for (int n = 0; n < getImageWidth(); n++) {
			Pixel p = { p.id = 1, p.value = 1, p.x = n, p.y = m };
			pixelObjArray[m][n] = p;
		}
	}
}*/

int FileReader::getImageHeight() {
	return this->imageHeight;
}

int FileReader::getImageWidth() {
	return this->imageWidth;
}