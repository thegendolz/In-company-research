#include "alphalevel.h"
#include <vector>
#include <cstdio>

AlphaLevel::AlphaLevel() {

}

AlphaLevel::AlphaLevel(int level, int height, int width) {
	this->pixelObjArray = std::vector< std::vector<int>>(height, std::vector < int>(width));

}

void AlphaLevel::setPixel(int value, int height, int width) {
	this->pixelObjArray[height][width] = value;
}

int AlphaLevel::getPixel(int height, int width) {
	return this->pixelObjArray[height][width];
}

void AlphaLevel::setEmptyLayer(int height, int width) {
	for (int n = 0; n < height; n++) {
		for (int m = 0; m < width; m++) {
			this->pixelObjArray[n][m] = -1;
		}
	}
}