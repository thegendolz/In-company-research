#include "alphatree.h"
#include "filereader.h"
#include "dissimilarity.h"
#include <vector>

AlphaTree::AlphaTree(){
	alphaLevel = 0;
	id = 0;
}

void AlphaTree::initialize(FileReader fileReader)
{
	int image_height = fileReader.getImageHeight();
	int image_width = fileReader.getImageWidth();

	std::vector<std::vector<int>> image = fileReader.getPixelArray();

	this->pixelObjArray = std::vector<std::vector<Pixel>>(image_height, std::vector < Pixel>(image_width));

	AlphaLevel alphaLayer = AlphaLevel(alphaLevel, image_height, image_width);
	alphaLayer.setEmptyLayer(image_height, image_width);
	
	this->findAllDissimilarities(image_height, image_width, image);

	for (int i = 0; i < horizontalDissimilarity.size(); i++) {
		Dissimilarity dissimilarity = horizontalDissimilarity.at(i);
		int n = dissimilarity.pixel.y;
		int m = dissimilarity.pixel.x;
		int difference = dissimilarity.amount;
		if (difference == 0) {
			if (alphaLayer.getPixel(n, m) == -1 && alphaLayer.getPixel(n, m + 1) != -1) {
				dissimilarity.pixel.node_id = this->getPixel(n, m + 1).node_id;
			}
			else if (alphaLayer.getPixel(n, m) != -1 && alphaLayer.getPixel(n, m + 1) == -1) {
				pixelObjArray[n][m+1].node_id = dissimilarity.pixel.node_id;
			}
			else {
				dissimilarity.pixel.node_id = id;
				pixelObjArray[n][m+1].node_id = id;
				id += 1;
			}
		}
		else{
			if (dissimilarity.pixel.node_id == -1) {
				dissimilarity.pixel.node_id = id;
				id += 1;
			}

		}
	}

	/*for (int i = 0; i < verticalDissimilarity.size(); i++) {

	}*/

	alphaLevel = 1;
}

void AlphaTree::findAllDissimilarities(int height, int width, std::vector<std::vector<int>> image) {
	for (int n = 0; n < height; n++) {
		for (int m = 0; m < width; m++) {
			struct Pixel pixel = { pixel.y = n, pixel.x = m, pixel.value = image[m][n] };
			this->setPixel(pixel, n, m);
			if (n == height - 1 && m == width - 1) {
				verticalDissimilarity.push_back(Dissimilarity{ pixel, -1 });
				horizontalDissimilarity.push_back(Dissimilarity{ pixel, -1 });
			}
			else if (m == width - 1) {
				horizontalDissimilarity.push_back(Dissimilarity{ pixel, -1 });
				verticalDissimilarity.push_back(Dissimilarity{ pixel, this->calculateDissimilarity(image[n][m], image[n + 1][m]) });

			}
			else if (n == height - 1) {
				verticalDissimilarity.push_back(Dissimilarity{ pixel, -1 });
				horizontalDissimilarity.push_back(Dissimilarity{ pixel, this->calculateDissimilarity(image[n][m], image[n][m + 1]) });
			}
			else {
				horizontalDissimilarity.push_back(Dissimilarity{ pixel, this->calculateDissimilarity(image[n][m], image[n][m + 1]) });
				verticalDissimilarity.push_back(Dissimilarity{ pixel, this->calculateDissimilarity(image[n][m], image[n + 1][m]) });
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