/*
 * TransformationMatricesTest.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: prashantm
 */

#include <TransformationMatrices.h>

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace {
  class TransformationMatricesTest : public ::testing::Test {
  protected:
	  TransformationMatrices *testObj;
  };
  TEST_F(TransformationMatricesTest, TestUnitTransformationMatrix) {
	  testObj = new TransformationMatrices();
	  float *unit_matrix = testObj->GetUnitTransformationMatrix();

	  for (int i = 0; i < 4; i++){
		  for (int j = 0; j < 4; j++){
			  if (i == j)
				  ASSERT_FLOAT_EQ(unit_matrix[i*4+j], 1);
			  else
				  ASSERT_FLOAT_EQ(unit_matrix[i*4+j], 0);
		  }
	  }

	  delete(testObj);
  }

  TEST_F(TransformationMatricesTest, TestScaleMatrix) {
	  testObj = new TransformationMatrices();

	  float scaling_factor[4] = {-11.8756, 0.0312, 8, 1};

  	  float *scaling_matrix = testObj->ScaleMatrix(scaling_factor[0], scaling_factor[1], scaling_factor[2]);

  	  for (int i = 0; i < 4; i++){
  		  for (int j = 0; j < 4; j++){
  			  if (i == j)
  				  ASSERT_FLOAT_EQ(scaling_matrix[i*4 + j], scaling_factor[i]);
  			  else
  				  ASSERT_FLOAT_EQ(scaling_matrix[i*4 + j], 0);
  		  }
  	  }

  	delete(testObj);
    }

  TEST_F(TransformationMatricesTest, TestTranslateMatrix) {

	  testObj = new TransformationMatrices();
	  float translate_factor[4] = {-11.8756, -0.0312, -941.4512, 1};

  	  float *translation_matrix = testObj->TranslationMatrix(translate_factor[0], translate_factor[1], translate_factor[2]);

  	  for (int i = 0; i < 4; i++){
  		  for (int j = 0; j < 4; j++){
  			  if (j == 3)
  				  ASSERT_FLOAT_EQ(translation_matrix[i*4 + j], translate_factor[i]);
  			  else if(i == j)
  				  ASSERT_FLOAT_EQ(translation_matrix[i*4 + j], 1);
  			  else
  				  ASSERT_FLOAT_EQ(translation_matrix[i*4 + j], 0);
  		  }
  	  }

  	  delete(testObj);

    }

  TEST_F(TransformationMatricesTest, TestPrintMatrix) {


	  testObj = new TransformationMatrices();

	  float *unit_matrix = testObj->GetUnitTransformationMatrix();

	  testObj->PrintTransformationMatrix(unit_matrix);
  }

  TEST_F(TransformationMatricesTest, TestTranslateMatrixAgain) {

	  testObj = new TransformationMatrices();
	  float translate_factor[4] = {11, 0.675710312, -941.4512, 1};

  	  float *translation_matrix = testObj->TranslationMatrix(translate_factor[0], translate_factor[1], translate_factor[2]);

  	  for (int i = 0; i < 4; i++){
  		  for (int j = 0; j < 4; j++){
  			  if (j == 3)
  				  ASSERT_FLOAT_EQ(translation_matrix[i*4 + j], translate_factor[i]);
  			  else if(i == j)
  				  ASSERT_FLOAT_EQ(translation_matrix[i*4 + j], 1);
  			  else
  				  ASSERT_FLOAT_EQ(translation_matrix[i*4 + j], 0);
  		  }
  	  }

  	  delete(testObj);
    }

  TEST_F(TransformationMatricesTest, TestRotationAcrossZ) {

	  testObj = new TransformationMatrices();
	  float rotation_angle = 15.0154;

	  float rotation_factor[4] = {0.965856225, -0.259078658, 0.259078658, 0.965856225};

  	  float *rotation_matrix = testObj->RotationMatrixAcrossZ(rotation_angle);

  	  for (int i = 0; i < 4; i++){
  		  for (int j = 0; j < 4; j++){
  			  if (i == 0 && j == 0)
  				  ASSERT_FLOAT_EQ(rotation_matrix[i*4 + j], rotation_factor[0]);
  			  else if (i == 0 && j == 1)
  				  ASSERT_FLOAT_EQ(rotation_matrix[i*4 + j], rotation_factor[1]);
  			  else if (i == 1 && j == 0)
  				  ASSERT_FLOAT_EQ(rotation_matrix[i*4 + j], rotation_factor[2]);
  			  else if (i == 1 && j == 1)
  			  	  ASSERT_FLOAT_EQ(rotation_matrix[i*4 + j], rotation_factor[3]);
  			  else if(i == j)
  				  ASSERT_FLOAT_EQ(rotation_matrix[i*4 + j], 1);
  			  else
  				  ASSERT_FLOAT_EQ(rotation_matrix[i*4 + j], 0);
  		  }
  	  }
  	  delete(testObj);
    }

}
