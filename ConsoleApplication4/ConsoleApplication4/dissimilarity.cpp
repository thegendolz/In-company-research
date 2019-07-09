#include "dissimilarity.h"


Dissimilarity::Dissimilarity() {

}

Dissimilarity::Dissimilarity(int n, int m, int n1, int m1, int amount) {
	this->n = n;
	this->m = m;
	this->n1 = n1;
	this->m1 = m1;
	this->distance = amount;
}

/*Pixel Dissimilarity::getPixel() {
	return this->pixel;
}

int Dissimilarity::getDistance() {
	return this->distance;
}*/