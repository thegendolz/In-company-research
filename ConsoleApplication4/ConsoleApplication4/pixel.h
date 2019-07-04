#ifndef PIXEL_H
#define PIXEL_H

#include "node.h"



class Pixel {
	public:
		//Constructors
		Pixel(int y, int x, int value, int id);
		Pixel();

		//Functions
		Pixel * getParent();
		void setParent(Pixel *pixel);
		int getY();
		int getX();
		int getValue();
		int getColor();
		int getId();


		//Variables
	private:
		Pixel *parent;
		int x;
		int y;
		int value;
		int id;
};

#endif 
