/*
 * FaceProperties.h
 *
 *  Created on: Oct 30, 2015
 *      Author: prashantm
 */

#ifndef FACEPROPERTIES_H_
#define FACEPROPERTIES_H_

using namespace std;

class FaceProperties {
private:
	float *diffuse_reflectance; // 3 terms of Lambertian reflectance matrix
	float specular_reflectance; // k
	float shininess_exponent; // alpha

public:
	FaceProperties(void);

	float * getDiffuseReflectance(void) const { return diffuse_reflectance;}

	float getSpecularReflectance(void) const {
		return specular_reflectance;
	}
	float getShininessExponent(void) const {
		return shininess_exponent;
	}

	void setDiffuseReflectance(float kr, float kg, float kb);

	void setSpecularReflectance(float ks);
	void setShininessExponent(float alpha);


};

#endif /* FACEPROPERTIES_H_ */
