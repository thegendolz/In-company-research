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
	while (!this->bottomReached) {
	//for (int j = 0; j < 100; j++) {
	//	printf("step %d \n", this->getDepth());
		doAlphaStep(image_height, image_width, false);
	//	i++;
	}
	//}
}

bool AlphaTree::isBottomReached(int image_height, int image_width) {
	/*ap = alphatreeLevels.at(alphatreeLevels.size()-1);
	int value = ap.getPixel(0, 0);
	for (int n = 0; n < image_height; n++) {
		for (int m = 0; m < image_width; m++) {
			if (ap.getPixel(n, m) != value) {
				return false;
			}
		}
	}*/
	return true;
}

int AlphaTree::getDepth() {
	return this->alphaLevel;
}

void AlphaTree::doAlphaStep(int image_height, int image_width, bool initialize) {
	ap = AlphaLevel(alphaLevel, image_height, image_width);
	ap.setEmptyLayer(image_height, image_width);
	horizontalDissimilarity.size();
	diss = horizontalDissimilarity.at(0);

	while (diss.distance <= alphaLevel && diss.distance >= -1) {
		diss = horizontalDissimilarity.at(0);
		int n = diss.pixel.y;
		int m = diss.pixel.x;
		int difference = diss.distance;

		if (pixelObjArray[n][m].parent != 0 && (pixelObjArray[n][m + 1].parent == 0 || pixelObjArray[n][m + 1].parent != 0)) {
			pixelObjArray[n][m + 1].parent = pixelObjArray[n][m].parent;
		}
		else {
			pointer = &pixelObjArray[n][m];
			pixelObjArray[n][m].parent = pointer;
			pixelObjArray[n][m + 1].parent = pointer;
		}

		horizontalDissimilarity.erase(horizontalDissimilarity.begin());
	}

	/*for (int i = 0; i < horizontalDissimilarity.size(); i++) {
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
	}*/

	if (initialize) {
		for (int i = 0; i < horizontalDissimilarity.size(); i++) {
			Dissimilarity dissim = horizontalDissimilarity.at(i);
			if (dissim.pixel.parent == 0) {
				pointer = &pixelObjArray[dissim.pixel.y][dissim.pixel.x];
				pixelObjArray[dissim.pixel.y][dissim.pixel.x].parent = pointer;
				id++;
			}
		}
	}

	diss = verticalDissimilarity.at(0);
	while (diss.distance <= alphaLevel) {
		diss = verticalDissimilarity.at(0);
		int n = diss.pixel.y;
		int m = diss.pixel.x;
		int difference = diss.distance;

		if (difference <= alphaLevel && difference >= 0) {
			//printf("%d, %d, %d \n", pixelObjArray[n][m].getParent(), n, m);
			counter = 0;
		    pointer = findRoot(pixelObjArray[n + 1][m].parent);
			//pixl = *pointer;
			if (pointer != findRoot(pixelObjArray[n][m].parent)) {
				pointer->parent = pixelObjArray[n][m].parent;
			}
		}
		verticalDissimilarity.erase(verticalDissimilarity.begin());
	}

	//Loop through object

	for (int n = 0; n < image_height; n++) {
		for (int m = 0; m < image_width; m++) {
			ap.setPixel(findRoot(this->getPixel(n, m).parent)->id, n, m);
		}
	}

	alphatreeLevels.push_back(ap);
	//printf("ja joh");
	if (verticalDissimilarity.size() == 0 && horizontalDissimilarity.size() == 0) this->bottomReached = true;
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
			if(this->pixelObjArray[n][m] == 0)
			Pixel pixel = Pixel(n, m, image[n][m], id);
			this->setPixel(pixel, n, m);
			id += 1;

			Dissimilarity diss = Dissimilarity(pixel, pixel2, this->calculateDissimilarity())
		    dissimilarity.push_back()
			/*if (n == height - 1 && m == width - 1) {
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
			}*/
		}
	}
	//horizontalDissimilarity

		std::sort(horizontalDissimilarity.begin(), horizontalDissimilarity.end(), [](const Dissimilarity& lhs, const Dissimilarity& rhs)
		{
			return lhs.distance < rhs.distance;
		});

		std::sort(verticalDissimilarity.begin(), verticalDissimilarity.end(), [](const Dissimilarity& lhs, const Dissimilarity& rhs)
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

void AlphaTree::setPixel(Pixel pixel, int height, int width) {
	this->pixelObjArray[height][width] = pixel;
}

Pixel AlphaTree::getPixel(int height, int width) {
	return this->pixelObjArray[height][width];
}

int AlphaTree::getPixelValueAtAlphaLevel(int level, int height, int width) {
	return this->alphatreeLevels.at(level).getPixel(height, width);
}