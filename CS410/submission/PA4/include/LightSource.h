/*
 * LightSource.h
 *
 *  Created on: Oct 31, 2015
 *      Author: prashantm
 */

#ifndef INCLUDE_LIGHTSOURCE_H_
#define INCLUDE_LIGHTSOURCE_H_

#include<Pixel.h>
#include<Vertex.h>

class LightSource : public Pixel, public Vertex {


public:
	bool isAmbient;
	LightSource(void);


};

#endif /* INCLUDE_LIGHTSOURCE_H_ */
