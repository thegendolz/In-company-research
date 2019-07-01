#include "alphatree.h";
#include "filereader.h"
#include "dissimilarity.h"

AlphaTree::AlphaTree(){
	alphaLevel = 0;
}

void AlphaTree::initialize(FileReader fileReader)
{
	int image_height = fileReader.getImageHeight();
	int image_width = fileReader.getImageWidth();

	std::vector<std::vector<int>> image = fileReader.getPixelArray();

	this->pixelObjArray = std::vector< std::vector<Pixel>>(image_height, std::vector < Pixel>(image_width));

	AlphaLevel al = AlphaLevel(alphaLevel, image_height, image_width);

	for (int n = 0; n < image_height; n++) {
		for (int m = 0; m < image_width; m++) {
			Pixel pixel = Pixel(n, m);
			this->setPixel(pixel, n, m);
			if (n == image_height - 1 && m == image_width - 1) {
				verticalDissimilarity.push_back(Dissimilarity(pixel, -1));
				horizontalDissimilarity.push_back(Dissimilarity(pixel, -1));
			}
			else if (m == image_width - 1) {
				horizontalDissimilarity.push_back(Dissimilarity(pixel, -1));
				verticalDissimilarity.push_back(Dissimilarity(pixel, this->calculateDissimilarity(image[n][m], image[n + 1][m])));

			}
			else if (n == image_height - 1) {
				verticalDissimilarity.push_back(Dissimilarity(pixel, -1));
				horizontalDissimilarity.push_back(Dissimilarity(pixel, this->calculateDissimilarity(image[n][m], image[n][m + 1])));
			}
			else {
				horizontalDissimilarity.push_back(Dissimilarity(pixel, this->calculateDissimilarity(image[n][m], image[n][m + 1])));
				verticalDissimilarity.push_back(Dissimilarity(pixel, this->calculateDissimilarity(image[n][m], image[n + 1][m])));
			}
		}
	}

	for (int i = 0; i < horizontalDissimilarity.size(); i++) {
		//n = horizontalDissimilarity.at(i).getPixel().
		//if()
	}

	for (int i = 0; i < verticalDissimilarity.size(); i++) {

	}

	alphaLevel = 1;
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