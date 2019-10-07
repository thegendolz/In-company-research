#include "alphatree.h"
#include "filereader.h"
#include "dissimilarity.h"
#include <algorithm> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <time.h>
#include <map>  
#include <unordered_map>  

using namespace cv;
using namespace std;
typedef map<int, int>::iterator mi;

AlphaTree::AlphaTree(){
	alphaLevel = 0;
	id = 0;
}

void AlphaTree::initialize(FileReader fileReader)
{
	int image_height = fileReader.getImageHeight();
	int image_width = fileReader.getImageWidth();

	std::vector<std::vector<std::vector<double>>> image = fileReader.getPixelArray();

	recognizer = Recognizer(fileReader);

	this->pixelObjArray = std::vector<std::vector<Pixel>>(image_height, std::vector <Pixel>(image_width));

	clock_t step1 = clock();
	this->findAllDissimilarities(image_height, image_width, image);
	clock_t step2 = clock();
	printf("dissim: %.2fs\n", (double)(step2 - step1) / CLOCKS_PER_SEC);

	printf("size: %d \n", dissimilarity.size());
	doAlphaStep(image_height, image_width, true);
}

void AlphaTree::finishTree(int image_height, int image_width) {
	while (!this->bottomReached) {
		//printf("step %d \n", this->getDepth());
		printf("--------[Tree Depth: %d]--------\n", alphaLevel);
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
	findTrafficSigns(image_height, image_width);
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

void AlphaTree::findTrafficSigns(int height, int width) {
	//#########################################
	//#	This part is for finding the clusters #
	//#########################################
	//CounterMap counts;
	std::unordered_map<int, int> occurrences;
	for (int n = 0; n < height; n++) {
		for (int m = 0; m < width; m++) {
			++occurrences[this->findRoot(getPixel(n, m).parent)->id];
		}
	}
	occurrences;


	/*	for (const auto &x : occurrences) {
		if (x.second > 20) {
			int a = x.first;
			a;
			*/
	idConnection.clear();
	std::vector<std::vector<Pixel>> vector;
	for (int n = 0; n < height; n++) {
		for (int m = 0; m < width; m++) {
			if (occurrences.at(this->findRoot(getPixel(n, m).parent)->id) > 200) {
				//This part finds all the clusters and pushes them to an Array containing all pixel objects for each cluster (Found by ID), this will make it easier to find the traffic signs
				int id = this->resetAndFindId(this->findRoot(getPixel(n, m).parent)->id);
				//printf("idconnection3: %d", idConnection.size());

				if (id == vector.size()) {
					vector.push_back(std::vector<Pixel>());
				}
				vector[id].push_back(this->pixelObjArray[n][m]);
			}
		}
	}
	printf("# Cluster: %d \n", vector.size());
	//Once the clusters are made, the positions of all the pixels have to be determined within the cluster
	std::vector<std::vector<int>> cluster;
	for (int i = 0; i < vector.size(); i++) {
		//printf("# Cluster: %d \n", vector[i].size());
		int lowX = -1, lowY = -1, highX = -1, highY = -1;
		for (int j = 0; j < vector[i].size(); j++) {
			if (vector[i][j].x < lowX || lowX == -1) lowX = vector[i][j].x;
			if (vector[i][j].y < lowY || lowY == -1) lowY = vector[i][j].y;
			if (vector[i][j].x > highX || highX == -1) highX = vector[i][j].x;
			if (vector[i][j].y > highY || highY == -1) highY = vector[i][j].y;
		}

		//+1 since array starts from 0 - X
		int diffX = (highX - lowX)+1;
		int diffY = (highY - lowY)+1;
		int diff = diffX < diffY ? diffY : diffX;

		//std::vector<std::vector<std::vector<double>>>(img.rows, std::vector<std::vector<double>>(img.cols, std::vector <double>(3)));

		cluster = std::vector<std::vector<int>>(diff, std::vector<int>(diff));
		for (int j = 0; j < vector[i].size(); j++) {
			cluster[vector[i][j].y - lowY][vector[i][j].x - lowX] = 255;
		}

		bool isTriangle = recognizer.isTriangle(diff, cluster);
		//isTriangle = false;

		if (isTriangle) {
			int amountOfRed = 0;
			int amountOfWhite = 0;
			std::vector<std::vector<std::vector<int>>> clusterColor = std::vector<std::vector<std::vector<int>>>(diff, std::vector<std::vector<int>>(diff, std::vector<int>(3)));
			for (int j = 0; j < vector[i].size(); j++) {
				std::vector<int> colorRGB = labtorgb(vector[i][j].value[0], vector[i][j].value[1], vector[i][j].value[2]);
				colorRGB;
				if (
						
						colorRGB[0] <= 255 && colorRGB[0] >= 64 &&
						colorRGB[1] <= 64 && colorRGB[1] >= 0 &&
						colorRGB[2] <= 64 && colorRGB[2] >= 0
							
					) {
					amountOfRed++;
				}

				if (

					colorRGB[0] <= 255 && colorRGB[0] >= 100 &&
					colorRGB[1] <= 255 && colorRGB[1] >= 100 &&
					colorRGB[2] <= 255 && colorRGB[2] >= 100

					) {
					amountOfWhite++;
				}
			}

			double percentageRed;
			if(amountOfRed != 0) percentageRed = (double)amountOfRed / (double)vector[i].size();
			else percentageRed = 0.0;

			double percentageWhite;
			if (amountOfRed != 0) percentageWhite = (double)amountOfWhite / (double)vector[i].size();
			else percentageWhite = 0.0;

			printf("PercentageRed: %lf, PercentageWhite: %lf \n", percentageRed, percentageWhite);

			if (percentageRed <= 0.5 && percentageRed >= 0.2 && percentageWhite >= 0.2 && percentageWhite <= 0.6) {
				printf("DAMES EN HEREN WE HEBBEN EEN TRAFFIC SIGN WHHOEEOEOEOEOOEE");
					
				cv::Mat image(diff, diff, CV_8UC3, Scalar(0, 0, 0));
				for (int n = 0; n < diff; n++) {
					image.at<Vec3b>(Point(vector[i][n].x - lowX, vector[i][n].y - lowY)) = cv::Vec3b(0, 0, 0);
				}

				for (int j = 0; j < vector[i].size(); ++j) {
					std::vector<int> colorRGB = labtorgb(vector[i][j].value[0], vector[i][j].value[1], vector[i][j].value[2]);
					//Other way around since Opencv uses BGR instead of RGB
					image.at<Vec3b>(Point(vector[i][j].x - lowX, vector[i][j].y - lowY)) = cv::Vec3b(colorRGB[2], colorRGB[1], colorRGB[0]);
				}
				//Mat bigger(512, 512, CV_8UC3, Scalar(0,0,0));
				//cv::resize(image, bigger, bigger.size(), 0, 0, INTER_NEAREST);
				//cv::resizeWindow("Display frame", 600, 600);
				cv::imshow("test", image);
				cv::waitKey(0);
			}
		}		
	}
	//Recognize color
}

int AlphaTree::resetAndFindId(int current_id) {
	current_id;
	for (int i = 0; i < idConnection.size(); i++) {
		if (idConnection[i][1] == current_id) {
			return idConnection[i][0];
		}
	}
	idConnection.push_back(std::vector<int>({ (int) idConnection.size(), current_id }));
	idConnection;
	return idConnection.at(idConnection.size() - 1).at(0);
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

	return floor(sqrt(l + a + b));
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

std::vector<int> AlphaTree::labtorgb(double l_, double a_, double b_) {
	double y = (l_ + 16.0) / 116.0,
		x = a_ / 500.0 + y,
		z = y - b_ / 200.0,
		r, g, b;

	x = 0.95047 * ((x * x * x > 0.008856) ? x * x * x : (x - 16 / 116) / 7.787);
	y = 1.00000 * ((y * y * y > 0.008856) ? y * y * y : (y - 16 / 116) / 7.787);
	z = 1.08883 * ((z * z * z > 0.008856) ? z * z * z : (z - 16 / 116) / 7.787);

	r = x * 3.2406 + y * -1.5372 + z * -0.4986;
	g = x * -0.9689 + y * 1.8758 + z * 0.0415;
	b = x * 0.0557 + y * -0.2040 + z * 1.0570;

	r = (r > 0.0031308) ? (1.055 * pow(r, 1 / 2.4) - 0.055) : 12.92 * r;
	g = (g > 0.0031308) ? (1.055 * pow(g, 1 / 2.4) - 0.055) : 12.92 * g;
	b = (b > 0.0031308) ? (1.055 * pow(b, 1 / 2.4) - 0.055) : 12.92 * b;

	return std::vector<int>{ (int) floor(max(0.0, min(1.0, r)) * 255.0), (int) floor(max(0.0, min(1.0, g)) * 255.0), (int) floor(max(0.0, min(1.0, b)) * 255.0)};
}