#ifndef FILEREADER_H
#define FILEREADER_H

#include "node.h"
#include "pixel.h"
#include <vector>

class FileReader {
	public:
		//Constructors
		FileReader();

		//Functions
		int getImageHeight();
		int getImageWidth();
		std::vector<std::vector<int>> getPixelArray();

	private:
		//Variables
		int imageHeight;
		int imageWidth;
		std::vector<std::vector<int>> pixelObjArray;
};

#endif 
