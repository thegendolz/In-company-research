#ifndef ALPHATREE_H
#define ALPHATREE_H

#include "pixel.h"
#include "alphalevel.h"
#include "filereader.h"
#include <vector>
#include "dissimilarity.h"

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
		void findAllDissimilarities(int height, int width, std::vector<std::vector<int>> image);

private:
		//Variables
		int alphaLevel;
		int id;
		std::vector<int> test;
		std::vector<Dissimilarity> horizontalDissimilarity;
		std::vector<Dissimilarity> verticalDissimilarity;
		std::vector<std::vector<Pixel>> pixelObjArray;
};
#endif 
