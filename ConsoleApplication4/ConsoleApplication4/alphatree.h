#ifndef ALPHATREE_H
#define ALPHATREE_H

#include "pixel.h"
#include "alphalevel.h"
#include "filereader.h"

class AlphaTree {
	public:
		//Constructors
		AlphaTree();

		//Functions
		void initialize(FileReader fileReader);
		int calculateDissimilarity(int position_1, int position_2);
		void setAlphaStep();
		void setPixel(Pixel pixel, int height, int width);
		Pixel getPixel(int height, int width);

private:
		//Variables
		int alphaLevel;
		std::vector<Dissimilarity> horizontalDissimilarity;
		std::vector<Dissimilarity> verticalDissimilarity;
		std::vector<std::vector<Pixel>> pixelObjArray;
};
#endif 
