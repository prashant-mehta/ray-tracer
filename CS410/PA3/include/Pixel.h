/*
 * Pixel.h
 *
 *  Created on: Oct 11, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_PIXEL_H_
#define INCLUDE_PIXEL_H_

#include <stdint.h>
#include <float.h>

using namespace std;

class Pixel {
private:
	uint32_t r, g, b;

public:
	float rValue, gValue, bValue;
	float distance_closest_intersection;
	Pixel();

	void SetR(uint32_t value) {
		r = value;
	}

	void SetG(uint32_t value) {
		g = value;
	}

	void SetB(uint32_t value) {
		b = value;
	}

	uint32_t GetR(void) {
		return r;
	}

	uint32_t GetG(void) {
		return g;
	}

	uint32_t GetB(void) {
		return b;
	}

	uint32_t ScalePixel(float max, float min, float value);

	void SetScaledPixels(float max, float min);

};

#endif /* INCLUDE_PIXEL_H_ */