#ifndef ALPHATREE_H
#define ALPHATREE_H

#include "pixel.h"
#include "alphalevel.h"
#include "filereader.h"
#include <vector>
#include "dissimilarity.h"
#include "recognizer.h"

class AlphaTree {
	public:
		//Constructors
		AlphaTree();

		//Functions
		void initialize(FileReader fileReader);
		int calculateDissimilarity(std::vector<double> position_1, std::vector<double> position_2);
		void setAlphaStep();
		Pixel* findRoot(Pixel *pixel);
		void setPixel(int n, int m, std::vector<double> value);
		void doAlphaStep(int image_height, int image_width, bool initialize);
		void finishTree(int image_height, int image_width);
		int getDepth();
		void findTrafficSigns(int height, int width);
		Pixel getPixel(int height, int width);
		int resetAndFindId(int current_id);
		//This function gets the id of a pixel at a certain alphalevel
		int getPixelValueAtAlphaLevel(int level, int image_height, int image_width);
		void findAllDissimilarities(int image_height, int image_width, std::vector<std::vector<std::vector<double>>> image);

	private:
		//Variables
		int alphaLevel;
		int id;
		int depth;
		int counter;
		int a;
		int b;
		Recognizer recognizer;
		bool bottomReached;
		Dissimilarity diss;
		AlphaLevel ap;
		Pixel* pointer;
		Pixel pixl;
		Pixel isRoot;
		std::vector<Dissimilarity> dissimilarity;
		std::vector<std::vector<Pixel>> pixelObjArray;
		std::vector<AlphaLevel> alphatreeLevels;
		std::vector<std::vector<int>> idConnection;
		//FileReader fileReader;
};
#endif 
