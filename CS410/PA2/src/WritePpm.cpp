/*
 * WritePpm.cpp
 *
 *  Created on: Oct 11, 2015
 *      Author: prashantm
 */

#include <WritePpm.h>

WritePpm::WritePpm(const char *filename, int32_t uSize, int32_t vSize, vector<Pixel> pixel_colors) {
	// TODO Auto-generated constructor stub

	outputfile.open(filename);

	outputfile << "P3\n";
	outputfile << uSize ;
	outputfile << " ";
	outputfile << vSize ;
	outputfile << " ";
	outputfile << "255" ;
	outputfile << "\n";


	// cout << << endl;

	if (pixel_colors.size() != uSize*vSize) {
		cout << "Number of pixels don't match with image size. Exiting the code now." << endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < uSize; i++) {
		for (int j = 0; j < vSize; j++) {
			outputfile << pixel_colors.at(i*vSize + j).GetR();
			outputfile << " ";
			outputfile << pixel_colors.at(i*vSize + j).GetG();
			outputfile << " ";
			outputfile << pixel_colors.at(i*vSize + j).GetB();
			outputfile << "\n";
		}


	}

	outputfile.close();
}

