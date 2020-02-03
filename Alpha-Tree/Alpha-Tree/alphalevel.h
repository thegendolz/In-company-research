#ifndef ALPHALEVEL_H
#define ALPHALEVEL_H

#include "pixel.h"
#include <vector>

class AlphaLevel {
	public:
		//Constructors
		AlphaLevel(int level, int height, int width);
		AlphaLevel();

		//Functions
		void setPixel(int amount, int height, int width);
		int getPixel(int height, int width);
		void setEmptyLayer(int height, int width);

	private:
		//Variables
		//This contains the array with the pixels
		//In order to increase the speed of the alpha tree, each level the Id's of the Node's is saved and not the entire Pixel object
		//The Alpha tree object keeps track of the Pixel objects
		std::vector<std::vector<int>> pixelObjArray;
};

#endif 
