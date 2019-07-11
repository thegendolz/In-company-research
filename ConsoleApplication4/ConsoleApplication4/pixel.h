#ifndef PIXEL_H
#define PIXEL_H

#include "node.h"



class Pixel {
	public:
		//Constructors
		Pixel(int y, int x, int value, int id);
		Pixel();
		Pixel *parent;
		short value;
		short id;
		short x;
		short y;
};

#endif 
