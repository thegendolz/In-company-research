#include "alphatree.h"
#include "filereader.h"
#include "dissimilarity.h"
#include <algorithm> 
#include <vector>
#include <iostream>
#include <time.h>

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

	clock_t step1 = clock();
	this->findAllDissimilarities(image_height, image_width, image);
	clock_t step2 = clock();
	printf("dissim: %.2fs\n", (double)(step2 - step1) / CLOCKS_PER_SEC);

	//printf("size: %d \n", dissimilarity.size());
	doAlphaStep(image_height, image_width, true);
}

void AlphaTree::finishTree(int image_height, int image_width) {
	while (!this->bottomReached) {
		printf("step %d \n", this->getDepth());
		/*printf("--------[Tree Depth: %d]--------\n", alphaLevel);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (j == 4) {
					printf("%d\n", findRoot(getPixel(i, j).parent)->id);
					//printf("%d\n", ap.getPixel(i, j).id);
				}
				else {
					printf("%d - ", findRoot(getPixel(i, j).parent)->id);
					//printf("%d - ", ap.getPixel(i, j).id);
				}
			}
		}*/
		doAlphaStep(image_height, image_width, false);
	}
}

int AlphaTree::getDepth() {
	return this->alphaLevel;
}

void AlphaTree::doAlphaStep(int image_height, int image_width, bool initialize) {
	clock_t step2 = clock();
	diss = dissimilarity.at(0);
	while (diss.distance >= 0 && diss.distance <= alphaLevel) {
		a = 0;
		pointer = findRoot(pixelObjArray[diss.n1][diss.m1].parent);
		b = a;
		a = 0;
		//Path compression inside FindRoot function
		Pixel* pointer2 = findRoot(pixelObjArray[diss.n][diss.m].parent);

		//Rank based search, always take shortest path
		if (pointer != pointer2) {
			if (b <= a) {
				pointer->parent = pointer2;
			}
			else {
				pointer2->parent = pointer;
			}
		}

		dissimilarity.erase(dissimilarity.begin());
		if(dissimilarity.size() > 0) diss = dissimilarity.at(0);
		else break;
	}


	if (dissimilarity.size() == 0) this->bottomReached = true;
	else this->bottomReached = false;
	alphaLevel++;
}

Pixel* AlphaTree::findRoot(Pixel *pixel) {
	isRoot = *pixel;
	a++;
	if (pixel == isRoot.parent) {
		return pixel;
	}
	else {
		pixel->parent = findRoot(isRoot.parent);
	}
}

void AlphaTree::findAllDissimilarities(int height, int width, std::vector<std::vector<int>> image) {
	for (int n = 0; n < height-1; n++) {
		for (int m = 0; m < width-1; m++) {
			this->setPixel(n, m, image[n][m]);
			//printf("%d - %d - %d - %d \n", n, m, this->calculateDissimilarity(image[n][m], image[n][m + 1]), this->calculateDissimilarity(image[n][m], image[n + 1][m]));
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
	this->setPixel(height -1, width - 1, image[height - 1][width - 1]);

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
	pointer = &pixelObjArray[n][m];
	pixelObjArray[n][m].parent = pointer;
	id += 1;
}

Pixel AlphaTree::getPixel(int height, int width) {
	return this->pixelObjArray[height][width];
}

int AlphaTree::getPixelValueAtAlphaLevel(int level, int height, int width) {
	return this->alphatreeLevels.at(level).getPixel(height, width);
}