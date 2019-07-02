#ifndef PIXEL_H
#define PIXEL_H

#include "node.h"

struct Pixel{
	int x;
	int y;
	int value;
	int node_id;
};


/*class Pixel {
public:
	//Constructors
	Pixel(int y, int x, int value);
	Pixel();

	//Functions
	Node getParent();
	void setParent(Node node);
	int getY();
	int getX();
	int getValue();
	int getColor();

	//Variables
private:
	int x;
	int y;
	int value;
	Node parent;
};*/

#endif 
