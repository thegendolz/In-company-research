// This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "alphatree.h"
#include <time.h>
#include "filereader.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	clock_t tStart = clock();

	//cv::Mat test = imread("test.jpg", 1);
	FileReader fileReader = FileReader();
	AlphaTree ap = AlphaTree();
	//ap.initialize(fileReader);

	//ap.finishTree(fileReader.getImageHeight(), fileReader.getImageWidth());

	//for (int depth = 0; depth < ap.getDepth(); depth++) {
	//	printf("--------[Tree Depth: %d]--------\n", depth);
		/*for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (j == 4) {
					printf("%d\n", ap.findRoot(ap.getPixel(i, j).parent)->id);
					//printf("%d\n", ap.getPixel(i, j).id);
				}
				else {
					printf("%d - ", ap.findRoot(ap.getPixel(i, j).parent)->id);
					//printf("%d - ", ap.getPixel(i, j).id);
				}
			}
		}*/
	//}

	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}
