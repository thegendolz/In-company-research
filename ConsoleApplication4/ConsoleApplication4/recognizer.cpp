#include "recognizer.h"
#include "filereader.h"
#include "dissimilarity.h"
#include <algorithm> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <time.h>

using namespace cv;

Recognizer::Recognizer() {

}

Recognizer::Recognizer(FileReader fileReader) {

}

bool Recognizer::isTriangle(int sizeOfTriangle, std::vector<std::vector<int>> cluster) {
	//Now that we have the clusters, perform Decision tree for correct traffic sign
	// Is is a triangle? What colors? 

	cv::Mat image(sizeOfTriangle, sizeOfTriangle, CV_64FC1);
	for (int i = 0; i < image.rows; ++i)
		for (int j = 0; j < image.cols; ++j)
			image.at<double>(i, j) = (double)cluster[i][j];

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;

	cv::Mat tempImage(sizeOfTriangle, sizeOfTriangle, CV_8UC1);
	image.convertTo(tempImage, CV_8UC1, 1.0 / 255.0);
	cv::findContours(tempImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, Point(0, 0));

	contours.size();
	for (int i = 0; i < contours.size(); i++)
	{

		cv::Mat approx;
		cv::approxPolyDP(contours[i], approx, 20, true);
		int a = approx.checkVector(2);
		//printf("approx van triangle: %d", a);
		//Checks if the contour is a Triangle
		//  && (cluster[floor(cluster.size()/2)][floor(cluster[0].size() / 2)] == 0)
		if (approx.checkVector(2) == 3) {
			/*Mat bigger(512, 512, CV_8UC1);
			cv::resize(image, bigger, bigger.size(), 0, 0, INTER_NEAREST);
			cv::resizeWindow("Display frame", 600, 600);
			cv::imshow("test", bigger);
			cv::waitKey(0);*/
			return true;
		}
	}
	//return false;
}

bool Recognizer::isRed(int sizeOfTriangle, std::vector<std::vector<std::vector<int>>> cluster) {
	return true;
}