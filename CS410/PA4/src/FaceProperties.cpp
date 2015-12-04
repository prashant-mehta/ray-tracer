/*
 * FaceProperties.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: prashantm
 */

#include "FaceProperties.h"

FaceProperties::FaceProperties(void) {
	// TODO Auto-generated constructor stub

	diffuse_reflectance = new float[3];
	diffuse_reflectance[0]=diffuse_reflectance[1]=diffuse_reflectance[2]=0.5;
	specular_reflectance = 0.0;
	shininess_exponent = 1;

}

void FaceProperties::setDiffuseReflectance(float kr, float kg, float kb) {
	diffuse_reflectance[0] = kr;
	diffuse_reflectance[1] = kg;
	diffuse_reflectance[2] = kb;
}

void FaceProperties::setSpecularReflectance(float ks) {

	specular_reflectance = ks;
}

void FaceProperties::setShininessExponent(float alpha) {
	shininess_exponent = alpha;
}
