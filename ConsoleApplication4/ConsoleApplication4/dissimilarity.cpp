#include "dissimilarity.h"


Dissimilarity::Dissimilarity() {

}

Dissimilarity::Dissimilarity(Pixel pixel, int amount) {
	this->pixel = pixel;
	this->amount = amount;
}

Pixel Dissimilarity::getPixel() {
	return this->pixel;
}

int Dissimilarity::getDistance() {
	return this->distance;
}