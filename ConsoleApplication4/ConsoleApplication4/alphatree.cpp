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

	for (int i = 0; i < horizontalDissimilarity.size(); i++) {
		Dissimilarity dissimilarity = horizontalDissimilarity.at(i);
		int n = dissimilarity.getPixel().getY();
		int m = dissimilarity.getPixel().getX();
		int difference = dissimilarity.getDistance();
		if (difference == 0) {
			/*if (alphaLayer.getPixel(n, m) == -1 && alphaLayer.getPixel(n, m + 1) != -1) {
				dissimilarity.getPixel().setParent(this->getPixel(n, m + 1).getParent(), this->getPixel(n, m + 1).getId());
				alphaLayer.setPixel(this->getPixel(n, m + 1).getId(), n, m);
			}
			else*/
			if (alphaLayer.getPixel(n, m) != -1 && alphaLayer.getPixel(n, m + 1) == -1) {
				pixelObjArray[n][m+1].setParent(&dissimilarity.getPixel(), alphaLayer.getPixel(n, m));
				alphaLayer.setPixel(alphaLayer.getPixel(n, m), n, m + 1);
			}
			else {
				dissimilarity.getPixel().setParent(&dissimilarity.getPixel(), id);
				alphaLayer.setPixel(id, n, m);
				pixelObjArray[n][m + 1].setParent(&dissimilarity.getPixel(), id);
				alphaLayer.setPixel(id, n, m+1);
				id++;
			}
		}
		else if (alphaLayer.getPixel(n, m) == -1) {
				//printf("n: %d, m: %d \n", n, m);
				dissimilarity.getPixel().setParent(&dissimilarity.getPixel(), id);
				alphaLayer.setPixel(id, n, m);
				id++;
		}
	}

	alphatreeLevels.push_back(alphaLayer);

	/*for (int i = 0; i < verticalDissimilarity.size(); i++) {

	}*/

	alphaLevel = 1;
}

void AlphaTree::findAllDissimilarities(int height, int width, std::vector<std::vector<int>> image) {
	for (int n = 0; n < height; n++) {
		for (int m = 0; m < width; m++) {
			Pixel pixel = Pixel(n, m, image[n][m]);
			this->setPixel(pixel, n, m);
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