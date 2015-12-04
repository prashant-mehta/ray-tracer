/*
 * WritePpm.h
 *
 *  Created on: Oct 11, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_WRITEPPM_H_
#define INCLUDE_WRITEPPM_H_

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <Pixel.h>

using namespace std;

class WritePpm {

private:
	ofstream outputfile;

public:
	WritePpm(const char *filename, int32_t uSize, int32_t vSize, vector<Pixel> pixel_colors);
};

#endif /* INCLUDE_WRITEPPM_H_ */
