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

	//fileReader.applyGaborFilter();
	AlphaTree ap = AlphaTree();
	ap.initialize(fileReader);
	ap.finishTree(fileReader.getImageHeight(), fileReader.getImageWidth());

	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}
