#ifndef PIXEL_H
#define PIXEL_H

#include "node.h"

class Pixel {
public:
	//Constructors
	Pixel(int y, int x);
	Pixel();

	//Functions
	Node getParent();
	void setParent(Node node);

	//Variables
private:
	int x;
	int y;
	Node parent;
};

#endif 
