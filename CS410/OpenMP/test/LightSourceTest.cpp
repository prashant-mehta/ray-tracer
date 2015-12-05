/*
 * LightSourceTest.cpp
 *
 *  Created on: Oct 31, 2015
 *      Author: prashantm
 */

#include <LightSource.h>
#include "gtest/gtest.h"

namespace {
  class LightSourceTest : public ::testing::Test {
  protected:
	  LightSource * testObj;
  };

  TEST_F(LightSourceTest, TestLightSource) {
	  testObj = new LightSource();

	  testObj->x_coordinate = 0.14;
	  testObj->y_coordinate = 0.85;
	  testObj->z_coordinate = 2.5;

	  testObj->SetR(testObj->ScalePixel(1,0,0.1));
	  testObj->SetG(testObj->ScalePixel(1,0,0.6));
	  testObj->SetB(testObj->ScalePixel(1,0,0.9));

	  ASSERT_EQ(testObj->isAmbient, false);

	  testObj->isAmbient = true;

	  ASSERT_FLOAT_EQ(testObj->x_coordinate, 0.14);
	  ASSERT_FLOAT_EQ(testObj->GetR(), 25);
	  ASSERT_FLOAT_EQ(testObj->GetG(), 153);
	  ASSERT_FLOAT_EQ(testObj->GetB(), 229);
	  ASSERT_EQ(testObj->isAmbient, true);
  }
}
