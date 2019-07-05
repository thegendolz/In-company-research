#include "alphatree.h"
#include "filereader.h"
#include "dissimilarity.h"
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

	this->findAllDissimilarities(image_height, image_width, image);

	doAlphaStep(image_height, image_width);
}

void AlphaTree::finishTree(int image_height, int image_width) {
	while (!isBottomReached(image_height, image_width)) {
		//printf("4 \n");
	//for (int i = 0; i < 30; i++) {
		doAlphaStep(image_height, image_width);
	}
	//}
}

bool AlphaTree::isBottomReached(int image_height, int image_width) {
	AlphaLevel ap = alphatreeLevels.at(alphatreeLevels.size()-1);
	int value = ap.getPixel(0, 0);
	for (int n = 0; n < image_height; n++) {
		for (int m = 0; m < image_width; m++) {
			if (ap.getPixel(n, m) != value) {
				return false;
			}
		}
	}
	return true;
}

int AlphaTree::getDepth() {
	return this->alphaLevel;
}

void AlphaTree::doAlphaStep(int image_height, int image_width) {
	AlphaLevel alphaLayer = AlphaLevel(alphaLevel, image_height, image_width);
	alphaLayer.setEmptyLayer(image_height, image_width);

	for (int i = 0; i < horizontalDissimilarity.size(); i++) {
		Dissimilarity dissimilarity = horizontalDissimilarity.at(i);
		int n = dissimilarity.getPixel().getY();
		int m = dissimilarity.getPixel().getX();
		int difference = dissimilarity.getDistance();
		if (difference <= alphaLevel && difference >= 0) {
			if (pixelObjArray[n][m].getParent() != 0 && (pixelObjArray[n][m + 1].getParent() == 0 || pixelObjArray[n][m + 1].getParent() != 0)) {
				pixelObjArray[n][m + 1].setParent(pixelObjArray[n][m].getParent());
	
			}
			else {
				Pixel *ptr = &pixelObjArray[n][m];
				pixelObjArray[n][m].setParent(ptr);
				pixelObjArray[n][m + 1].setParent(ptr);
			}
		}
		else if (pixelObjArray[n][m].getParent() == 0) {
			Pixel *ptr = &pixelObjArray[n][m];
			pixelObjArray[n][m].setParent(ptr);
			id++;
		}
	}
	
	for (int i = 0; i < verticalDissimilarity.size(); i++) {
		Dissimilarity dissimilarity = verticalDissimilarity.at(i);
		int n = dissimilarity.getPixel().getY();
		int m = dissimilarity.getPixel().getX();
		int difference = dissimilarity.getDistance();

		if (difference <= alphaLevel && difference >= 0) {
			//printf("%d, %d, %d \n", pixelObjArray[n][m].getParent(), n, m);
			Pixel * pixel = findRoot(pixelObjArray[n + 1][m].getParent());
			Pixel pix = *pixel;
			if (pixel != findRoot(pixelObjArray[n][m].getParent())) {
				pixel->setParent(pixelObjArray[n][m].getParent());
			}
		}
	}

	//Loop through object

	for (int n = 0; n < image_height; n++) {
		for (int m = 0; m < image_width; m++) {
			alphaLayer.setPixel(findRoot(this->getPixel(n, m).getParent())->getId(), n, m);
		}
	}

	alphatreeLevels.push_back(alphaLayer);
	alphaLevel++;
}

Pixel* AlphaTree::findRoot(Pixel *pixel) {
	isRoot = *pixel;

	if (pixel == isRoot.getParent()) {
		return pixel;
	}
	else {
		findRoot(isRoot.getParent());
	}
}

void AlphaTree::findAllDissimilarities(int height, int width, std::vector<std::vector<int>> image) {
	for (int n = 0; n < height; n++) {
		for (int m = 0; m < width; m++) {
			Pixel pixel = Pixel(n, m, image[n][m], id);
			this->setPixel(pixel, n, m);
			id += 1;
			if (n == height - 1 && m == width - 1) {
				verticalDissimilarity.push_back(Dissimilarity(pixel, -1));
				horizontalDissimilarity.push_back(Dissimilarity(pixel, -1));
			}
			else if (m == width - 1) {
				horizontalDissimilarity.push_back(Dissimilarity(pixel, -1));
				verticalDissimilarity.push_back(Dissimilarity(pixel, this->calculateDissimilarity(image[n][m], image[n + 1][m])));

			}
			else if (n == height - 1) {
				verticalDissimilarity.push_back(Dissimilarity(pixel, -1));
				horizontalDissimilarity.push_back(Dissimilarity(pixel, this->calculateDissimilarity(image[n][m], image[n][m + 1])));
			}
			else {
				horizontalDissimilarity.push_back(Dissimilarity(pixel, this->calculateDissimilarity(image[n][m], image[n][m + 1])));
				verticalDissimilarity.push_back(Dissimilarity(pixel, this->calculateDissimilarity(image[n][m], image[n + 1][m])));
			}
		}
	}
}

void AlphaTree::setAlphaStep() {
	//AlphaLevel ap = AlphaLevel(alphaLevel, image_height, image_width);
}

int AlphaTree::calculateDissimilarity(int position_1, int position_2) {
	return abs(position_1 - position_2);
}

void AlphaTree::setPixel(Pixel pixel, int height, int width) {
	this->pixelObjArray[height][width] = pixel;
}

Pixel AlphaTree::getPixel(int height, int width) {
	return this->pixelObjArray[height][width];
}

int AlphaTree::getPixelValueAtAlphaLevel(int level, int height, int width) {
	return this->alphatreeLevels.at(level).getPixel(height, width);
}