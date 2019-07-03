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

		//In order to speed up the process only the id's are saved for each alpha level
		//While the alphatree object keeps track of the Pixel objects, but these pixel objects are only created once for the initial process
		//This function gets the current Pixel Object
		Pixel getPixel(int height, int width);
		//This function gets the id of a pixel at a certain alphalevel
		int getPixelValueAtAlphaLevel(int level, int height, int width);
		void findAllDissimilarities(int height, int width, std::vector<std::vector<int>> image);

	private:
		//Variables
		int alphaLevel;
		int id;
		std::vector<int> test;
		std::vector<Dissimilarity> horizontalDissimilarity;
		std::vector<Dissimilarity> verticalDissimilarity;
		std::vector<std::vector<Pixel>> pixelObjArray;
		std::vector<AlphaLevel> alphatreeLevels;
};
#endif 
