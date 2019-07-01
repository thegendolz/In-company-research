#include "pixel.h"

Pixel::Pixel() {

}

Pixel::Pixel(int y, int x) {
	this->x = x;
	this->y = y;
}

Node Pixel::getParent() {
	return this->parent;
}

void Pixel::setParent(Node node)
{
	this->parent = node;
}
