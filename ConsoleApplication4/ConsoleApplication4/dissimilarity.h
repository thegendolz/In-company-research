#ifndef DISSIMILARITY_H
#define DISSIMILARITY_H

#include "pixel.h"
#include "dissimilarity.h"

class Dissimilarity {
	public:
		//Constructors
		Dissimilarity();
		Dissimilarity(Pixel pixel, int amount);

		//Functions
		Pixel getPixel();
		int getDistance();

	private:
		//Variables
		Pixel pixel;
		int distance;
		int amount;
};

#endif 
