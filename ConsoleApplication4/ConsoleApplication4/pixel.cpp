#include "pixel.h"
#include <iostream>

Pixel::Pixel() {

}

Pixel::Pixel(int y, int x, std::vector<double> value, int id) {
	this->y = y;
	this->x = x;
	this->value = value;
	this->id = id;
}