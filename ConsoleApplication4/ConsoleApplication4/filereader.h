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
		std::vector<std::vector<std::vector<double>>> getPixelArray();
		std::vector<double> rgbtolab(double r, double g, double b);
		std::vector<int> labtorgb(double l_, double a_, double b_);
	private:
		//Variables
		int imageHeight;
		int imageWidth;
		std::vector<std::vector<std::vector<double>>> pixelObjArray;
};

#endif 
