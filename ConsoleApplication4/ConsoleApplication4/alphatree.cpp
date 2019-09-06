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

	std::vector<std::vector<std::vector<double>>> image = fileReader.getPixelArray();

	this->pixelObjArray = std::vector<std::vector<Pixel>>(image_height, std::vector <Pixel>(image_width));

	clock_t step1 = clock();
	this->findAllDissimilarities(image_height, image_width, image);
	clock_t step2 = clock();
	//printf("dissim: %.2fs\n", (double)(step2 - step1) / CLOCKS_PER_SEC);

	//printf("size: %d \n", dissimilarity.size());
	doAlphaStep(image_height, image_width, true);
}

void AlphaTree::finishTree(int image_height, int image_width) {
	while (!this->bottomReached) {
		//printf("step %d \n", this->getDepth());
		printf("--------[Tree Depth: %d]--------\n", alphaLevel);
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				if (j == 15) {
					printf("%d\n", findRoot(getPixel(i, j).parent)->id);
					//printf("%d\n", ap.getPixel(i, j).id);
				}
				else {
					printf("%d - ", findRoot(getPixel(i, j).parent)->id);
					//printf("%d - ", ap.getPixel(i, j).id);
				}
			}
		}
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

	//findTrafficSigns(image_height, image_width);

	if (dissimilarity.size() == 0) this->bottomReached = true;
	else this->bottomReached = false;
	alphaLevel++;
}

void AlphaTree::findTrafficSigns(int height, int width) {
	//#########################################
	//#	This part is for finding the clusters #
	//#########################################
	idConnection.clear();
	printf("TEST 1");
	std::vector<std::vector<Pixel>> vector;
	for (int n = 0; n < height; n++) {
		for (int m = 0; m < width; m++) {
			//This part finds all the clusters and pushes them to an Array containing all pixel objects for each cluster (Found by ID), this will make it easier to find the traffic signs
			int id = this->resetAndFindId(this->pixelObjArray[n][m].id);
			//printf("idconnection3: %d", idConnection.size());
			if(id == vector.size()){
				vector.push_back(std::vector<Pixel>());
			}
			vector[id].push_back(this->pixelObjArray[n][m]);
		}
	}
	printf("TEST CLUSTER: %d", vector.size());
	//Once the clusters are made, the positions of all the pixels have to be determined within the cluster
	std::vector<std::vector<int>> cluster;
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i].size() > 5) {
			printf("TEST 0.5");
			int lowX = -1, lowY = -1, highX = -1, highY = -1;
			for (int j = 0; j < vector[i].size(); j++) {
				if (vector[i][j].x < lowX || lowX == -1) lowX = vector[i][j].x;
				if (vector[i][j].y < lowY || lowY == -1) lowY = vector[i][j].y;
			}

			int diffX = highX - lowX;
			int diffY = highY - lowY;

			//std::vector<std::vector<std::vector<double>>>(img.rows, std::vector<std::vector<double>>(img.cols, std::vector <double>(3)));

			cluster = std::vector<std::vector<int>>(diffY, std::vector<int>(diffX));
			printf("TEST 2");
			for (int j = 0; j < vector[i].size(); j++) {
				cluster[vector[i].at(j).y - lowY][vector[i].at(j).x - lowX] = vector[i].at(j).value[0];
			}

			//Here is the cluster with the correct objects, now check if it is a traffic sign
			printf("TEST 3");
			//##############################################
			//#	This part is for finding the traffic signs #
			//##############################################

			printf("--------[Clusters]--------\n");
			for (int i = 0; i < cluster.size(); i++) {
				for (int j = 0; j < cluster[i].size(); j++) {
					if (j == cluster[i].size()-1) {
						printf("%d\n", cluster[i][j]);
						//printf("%d\n", ap.getPixel(i, j).id);
					}
					else {
						printf("%d - ", cluster[i][j]);
						//printf("%d - ", ap.getPixel(i, j).id);
					}
				}
			}

		}
	}

	//Recognize shape



	//Recognize color
}

int AlphaTree::resetAndFindId(int current_id) {
	for (int i = 0; i < idConnection.size(); i++) {
		if (idConnection.at(i)[1] == current_id) {
			return idConnection.at(i)[0];
		}
	}
	std::vector<int> arr = std::vector<int>(2);
	arr.push_back(idConnection.size());
	arr.push_back(current_id);
	idConnection.push_back(arr);
	return idConnection.at(idConnection.size() - 1).at(0);
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

void AlphaTree::findAllDissimilarities(int height, int width, std::vector<std::vector<std::vector<double>>> image) {
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

int AlphaTree::calculateDissimilarity(std::vector<double> position_1, std::vector<double> position_2) {
	double l = pow(position_2[0] - position_1[0], 2);
	double a = pow(position_2[1] - position_1[1], 2);
	double b = pow(position_2[2] - position_1[2], 2);

	return sqrt(l + a + b);

	//return abs(position_1 - position_2);
}

void AlphaTree::setPixel(int n, int m, std::vector<double> lab) {
	this->pixelObjArray[n][m] = Pixel(n, m, lab, id);
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