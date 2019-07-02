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

	/*for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 4) {
				printf("%d \n", ap.getPixel(j, i).node_id);
			}
			else {
				printf("%d", ap.getPixel(j, i).node_id);
			}
		}
	}*/

	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
}
