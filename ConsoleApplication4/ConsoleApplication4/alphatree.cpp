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

	AlphaLevel alphaLayer = AlphaLevel(alphaLevel, image_height, image_width);
	alphaLayer.setEmptyLayer(image_height, image_width);

	this->findAllDissimilarities(image_height, image_width, image);

	//printf("1");
	for (int i = 0; i < horizontalDissimilarity.size(); i++) {
		Dissimilarity dissimilarity = horizontalDissimilarity.at(i);
		int n = dissimilarity.getPixel().getY();
		int m = dissimilarity.getPixel().getX();
		int difference = dissimilarity.getDistance();
		if (difference == 0) {
			if (pixelObjArray[n][m].getParent() != 0 && pixelObjArray[n][m+1].getParent() == 0) {
				pixelObjArray[n][m+1].setParent(pixelObjArray[n][m].getParent());
				Pixel *p = pixelObjArray[n][m + 1].getParent();
				//printf("yayeet");
				//alphaLayer.setPixel(alphaLayer.getPixel(n, m), n, m + 1);
			}
			else {
				Pixel *ptr = &pixelObjArray[n][m];
				pixelObjArray[n][m].setParent(ptr);
				//alphaLayer.setPixel(id, n, m);
				pixelObjArray[n][m + 1].setParent(ptr);
				//alphaLayer.setPixel(id, n, m+1);
			}
		}
		else if (pixelObjArray[n][m].getParent() == 0) {
			Pixel *ptr = &pixelObjArray[n][m];
			//printf("n: %d, m: %d \n", n, m);
			pixelObjArray[n][m].setParent(ptr);
			//alphaLayer.setPixel(id, n, m);
			id++;
		}
	}
	//printf("2");

	for (int i = 0; i < verticalDissimilarity.size(); i++) {
		Dissimilarity dissimilarity = verticalDissimilarity.at(i);
		int n = dissimilarity.getPixel().getY();
		int m = dissimilarity.getPixel().getX();
		int difference = dissimilarity.getDistance();

		if (difference == 0) {
			//Pixel pixel = *dissimilarity.getPixel().getParent();
			Pixel * pixel = findRoot(pixelObjArray[n + 1][m].getParent());

			pixel->setParent(pixelObjArray[n][m].getParent());
		}
	}

	//Loop through object

	for (int n = 0; n < image_height; n++) {
		for (int m = 0; m < image_width; m++) {
			//Pixel* pixel = this->getPixel(m, n).getParent();
			//Pixel pix = *pixel;
			alphaLayer.setPixel(findRoot(this->getPixel(n, m).getParent())->getId(), n, m);
			//printf("test 123");
		}
	}

	alphatreeLevels.push_back(alphaLayer);
	alphaLevel = 1;
}

Pixel* AlphaTree::findRoot(Pixel *pixel) {
	Pixel isRoot = *pixel;
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