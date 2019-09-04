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

/*Pixel * Pixel::getParent() {
	return this->parent;
}

int Pixel::getId() {
	return this->id;
}

void Pixel::setParent(Pixel *pixel)
{
	this->parent = pixel;
}

int Pixel::getY() {
	return this->y;
}

int Pixel::getX() {
	return this->x;
}

int Pixel::getValue() {
	return this->value;
}

int Pixel::getColor() {
	return 0;
}*/
