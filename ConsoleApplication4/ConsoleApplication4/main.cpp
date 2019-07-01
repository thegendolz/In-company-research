// This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "alphatree.h"
#include <time.h>
#include "filereader.h"

int main(int argc, char *argv[])
{
	clock_t tStart = clock();
	FileReader fileReader = FileReader();
	AlphaTree ap = AlphaTree();
	ap.initialize(fileReader);


	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}
