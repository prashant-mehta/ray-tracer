/*
 * WritePpm.cpp
 *
 *  Created on: Oct 11, 2015
 *      Author: prashantm
 */

#include <WritePpm.h>

WritePpm::WritePpm(const char *filename, int32_t uSize, int32_t vSize, const vector<Pixel>& pixel_colors) {
	// TODO Auto-generated constructor stub

	outputfile.open(filename);

	ofstream writet;

	writet.open("tValues.txt");

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

	for (int i = 0; i < vSize; i++) {
		for (int j = 0; j < uSize; j++) {
			outputfile << pixel_colors.at(i*uSize + j).GetR();
			outputfile << " ";
			outputfile << pixel_colors.at(i*uSize + j).GetG();
			outputfile << " ";
			outputfile << pixel_colors.at(i*uSize + j).GetB();
			outputfile << "\n";

			if (j >= 135 && j <= 175 && i >= 28 && i <= 69) {

			writet << pixel_colors.at(i*uSize + j).closest_polygon;
			writet << " ";

			}
		}
		writet << "\n";


	}

	outputfile.close();
	writet.close();
}

