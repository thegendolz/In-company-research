#ifndef DISSIMILARITY_H
#define DISSIMILARITY_H

#include "pixel.h"
#include "dissimilarity.h"

class Dissimilarity {
	public:
		//Constructors
		Dissimilarity();
		Dissimilarity(int n, int m, int n1, int m1, int amount);

		short n, m, n1, m1;
		short distance;
		short amount;
};

#endif 
