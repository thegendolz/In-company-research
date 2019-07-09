#include "alphatree.h"
#include "filereader.h"
#include "dissimilarity.h"
#include <algorithm> 
#include <vector>
#include <iostream>

AlphaTree::AlphaTree(){
	alphaLevel = 0;
	id = 0;
}

void AlphaTree::initialize(FileReader fileReader)
{
	int image_height = fileReader.getImageHeight();
	int image_width = fileReader.getImageWidth();

	std::vector<std::vector<int>> image = fileReader.getPixelArray();

	this->pixelObjArray = std::vector<std::vector<Pixel>>(image_height, std::vector <Pixel>(image_width));

	//testing();

	this->findAllDissimilarities(image_height, image_width, image);

	//printf("size: %d, %d", horizontalDissimilarity.size(), verticalDissimilarity.size());
	doAlphaStep(image_height, image_width, true);
}

void AlphaTree::testing() {
	
	for (int m = 0; m < 1000; m++) {
		for (int n = 0; n < 1000; n++) {
			Pixel p = Pixel(1, 1, 1, 1);
			pixelObjArray[m][n] = p;
		}
	}
	
}

void AlphaTree::finishTree(int image_height, int image_width) {
	//printf("test");
	//int i = 0;
	//while (!this->bottomReached) {
	//for (int j = 0; j < 100; j++) {
	//	printf("step %d \n", this->getDepth());
	//	doAlphaStep(image_height, image_width, false);
	//	i++;
	//}
	//}
}

int AlphaTree::getDepth() {
	return this->alphaLevel;
}

void AlphaTree::doAlphaStep(int image_height, int image_width, bool initialize) {
	ap = AlphaLevel(alphaLevel, image_height, image_width);
	ap.setEmptyLayer(image_height, image_width);
	dissimilarity;
	diss = dissimilarity.at(0);

	while (diss.distance <= alphaLevel && diss.distance >= 0) {
		diss = dissimilarity.at(0);
		int n = diss.n;
		int m = diss.m;
		int n1 = diss.n1;
		int m1 = diss.m1;
		int difference = diss.distance;

		if (pixelObjArray[n][m].parent != nullptr && pixelObjArray[n1][m1].parent != nullptr) {
			pointer = findRoot(pixelObjArray[n][m].parent);
			//Pixel* pointer2 = findRoot(pixelObjArray[n1][m1].parent)
			pointer->parent = findRoot(pixelObjArray[n1][m1].parent);
		}
		else if(pixelObjArray[n][m].parent != nullptr && pixelObjArray[n1][m1].parent == nullptr){
			pixelObjArray[n1][m1].parent = pixelObjArray[n][m].parent;
		}else {
			pointer = &pixelObjArray[n][m];
			pixelObjArray[n][m].parent = pointer;
			pixelObjArray[n1][m1].parent = pointer;
		}

		dissimilarity.erase(dissimilarity.begin());
	}

	if (initialize) {
		for (int i = 0; i < dissimilarity.size(); i++) {
			Dissimilarity dissim = dissimilarity.at(i);
			if (pixelObjArray[dissim.n][dissim.m].parent == 0) {

				pointer = &pixelObjArray[dissim.n][dissim.m];
				pixelObjArray[dissim.n][dissim.m].parent = pointer;
				id++;
			}
		}
	}

	//Loop through object

	for (int n = 0; n < image_height; n++) {
		for (int m = 0; m < image_width; m++) {
			ap.setPixel(findRoot(this->getPixel(n, m).parent)->id, n, m);
		}
	}

	alphatreeLevels.push_back(ap);
	if (dissimilarity.size() == 0) this->bottomReached = true;
	else this->bottomReached = false;

	//printf(this->bottomReached ? "true" : "false");
	alphaLevel++;
}

Pixel* AlphaTree::findRoot(Pixel *pixel) {
	isRoot = *pixel;

	if (pixel == isRoot.parent) {
		return pixel;
	}
	else {
		findRoot(isRoot.parent);
	}
}

void AlphaTree::findAllDissimilarities(int height, int width, std::vector<std::vector<int>> image) {
	for (int n = 0; n < height-1; n++) {
		for (int m = 0; m < width-1; m++) {
			this->setPixel(n, m, image[n][m]);
			dissimilarity.push_back(Dissimilarity(n, m, n, m + 1, this->calculateDissimilarity(image[n][m], image[n][m + 1])));
			dissimilarity.push_back(Dissimilarity(n, m, n + 1, m, this->calculateDissimilarity(image[n][m], image[n + 1][m])));
		}
	}

	for (int m=0; m < width-1; m++) {
		this->setPixel(height-1, m, image[height-1][m]);
		dissimilarity.push_back(Dissimilarity(height-1, m, height-1, m + 1, this->calculateDissimilarity(image[height-1][m], image[height-1][m + 1])));
	}
	for (int n=0; n < height-1; n++) {
		this->setPixel(n, width-1, image[n][width-1]);
		dissimilarity.push_back(Dissimilarity(n, width-1, n + 1, width-1, this->calculateDissimilarity(image[n][width-1], image[n+1][width-1])));
	}
	std::sort(dissimilarity.begin(), dissimilarity.end(), [](const Dissimilarity& lhs, const Dissimilarity& rhs)
	{
		return lhs.distance < rhs.distance;
	});
}

void AlphaTree::setAlphaStep() {
	//AlphaLevel ap = AlphaLevel(alphaLevel, image_height, image_width);
}

int AlphaTree::calculateDissimilarity(int position_1, int position_2) {
	return abs(position_1 - position_2);
}

void AlphaTree::setPixel(int n, int m, int value) {
	this->pixelObjArray[n][m] = Pixel(n, m, value, id);
	id += 1;
}

Pixel AlphaTree::getPixel(int height, int width) {
	return this->pixelObjArray[height][width];
}

int AlphaTree::getPixelValueAtAlphaLevel(int level, int height, int width) {
	return this->alphatreeLevels.at(level).getPixel(height, width);
}