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
		Pixel* findRoot(Pixel *pixel);
		void setPixel(Pixel pixel, int height, int image_width);
		void doAlphaStep(int image_height, int image_width, bool initialize);
		void finishTree(int image_height, int image_width);
		int getDepth();
		bool isBottomReached(int image_height, int image_width);
		void testing();

		//In order to speed up the process only the id's are saved for each alpha level
		//While the alphatree object keeps track of the Pixel objects, but these pixel objects are only created once for the initial process
		//This function gets the current Pixel Object
		Pixel getPixel(int height, int width);
		//This function gets the id of a pixel at a certain alphalevel
		int getPixelValueAtAlphaLevel(int level, int image_height, int image_width);
		void findAllDissimilarities(int image_height, int image_width, std::vector<std::vector<int>> image);

	private:
		//Variables
		int alphaLevel;
		int id;
		int depth;
		int counter;
		bool bottomReached;
		Dissimilarity diss;
		AlphaLevel ap;
		Pixel* pointer;
		Pixel pixl;
		Pixel isRoot;
		//Pixel pixel;
		std::vector<int> test;
		std::vector<Dissimilarity> dissimilarity;
		//std::vector<Dissimilarity> verticalDissimilarity;
		std::vector<std::vector<Pixel>> pixelObjArray;
		std::vector<AlphaLevel> alphatreeLevels;
};
#endif 
