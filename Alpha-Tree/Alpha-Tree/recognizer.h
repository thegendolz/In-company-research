#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include "pixel.h"
#include "alphalevel.h"
#include "filereader.h"
#include <vector>
#include "dissimilarity.h"

class Recognizer{
public:
	//Constructors
	Recognizer();
	Recognizer(FileReader fileReader);

	//Functions
	bool isTriangle(int sizeOfTriangle, std::vector<std::vector<int>> cluster);
	bool isRed(int sizeOfTriangle, std::vector<std::vector<std::vector<int>>> cluster);
private:
	//Variables
	bool triangle;
	bool red;
};
#endif 
