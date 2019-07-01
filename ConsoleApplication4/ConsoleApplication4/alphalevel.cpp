#include "alphalevel.h"
#include <vector>

AlphaLevel::AlphaLevel() {

}

AlphaLevel::AlphaLevel(int level, int height, int width) {
	this->pixelObjArray = std::vector< std::vector<Pixel>>(height, std::vector < Pixel>(width));

}

void AlphaLevel::setPixel(int value, int height, int width) {
	this->pixelObjArray[height][width] = value;
}

int AlphaLevel::getPixel(int height, int width) {
	return this->pixelObjArray[height][width];
}