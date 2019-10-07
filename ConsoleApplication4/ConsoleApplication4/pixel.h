#ifndef PIXEL_H
#define PIXEL_H

#include "node.h"
#include <vector>



class Pixel {
	public:
		//Constructors
		Pixel(int y, int x, std::vector<double> value, int id);
		Pixel();
		Pixel *parent;
		std::vector<double> value;
		int id;
		short x;
		short y;
};

#endif 
