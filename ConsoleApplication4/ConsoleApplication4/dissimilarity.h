#ifndef DISSIMILARITY_H
#define DISSIMILARITY_H

#include "pixel.h"
#include "dissimilarity.h"

class Dissimilarity {
	public:
		//Constructors
		Dissimilarity();
		Dissimilarity(Pixel pixel, Pixel pixel2, int amount);

		Pixel pixel;
		Pixel pixel2;
		short distance;
		short amount;
};

#endif 
