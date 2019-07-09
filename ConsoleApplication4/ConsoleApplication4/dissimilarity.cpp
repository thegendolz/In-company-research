#include "dissimilarity.h"


Dissimilarity::Dissimilarity() {

}

Dissimilarity::Dissimilarity(Pixel pixel, Pixel pixel2, int amount) {
	this->pixel = pixel;
	this->pixel2 = pixel2;
	this->distance = amount;
}

/*Pixel Dissimilarity::getPixel() {
	return this->pixel;
}

int Dissimilarity::getDistance() {
	return this->distance;
}*/