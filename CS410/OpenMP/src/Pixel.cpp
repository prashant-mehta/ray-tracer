/*
 * Pixel.cpp
 *
 *  Created on: Oct 11, 2015
 *      Author: prashantm
 */

#include <Pixel.h>

Pixel::Pixel() {
	// TODO Auto-generated constructor stub
	r = 0;
	b = 0;
	g = 0;
	rValue = 0;
	gValue = 0;
	bValue = 0;


	distance_closest_intersection = FLT_MAX;
	closest_polygon = UINT64_MAX;
	random_scaleU = 0;
	random_scaleV = 0;

}

// Scale pixel to range of 0 to 255
uint32_t Pixel::ScalePixel(float max, float min, float value) {
	return 255 * (value - min) / (max - min);
}

void Pixel::SetScaledPixels(float max, float min) {
	r = ScalePixel(max, min, rValue);
	g = ScalePixel(max, min, gValue);
	b = ScalePixel(max, min, bValue);
}
