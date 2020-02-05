#ifndef FILEREADER_H
#define FILEREADER_H

#include "node.h"
#include "pixel.h"
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class FileReader {
	public:
		//Constructors
		FileReader();

		//Functions
		int getImageHeight();
		int getImageWidth();
		std::vector<std::vector<std::vector<double>>> getPixelArray();
		static std::vector<double> rgbtolab(double r, double g, double b);
		static std::vector<int> labtorgb(double l_, double a_, double b_);
		Mat applyGaborFilter(Mat img);
		void gaborFiltering(Mat img);
	private:
		//Variables
		int imageHeight;
		int imageWidth;
		std::vector<std::vector<std::vector<double>>> pixelObjArray;
};

#endif 
