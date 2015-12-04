/*
 * ParseMaterialsTest.cpp
 *
 *  Created on: Oct 31, 2015
 *      Author: prashantm
 */

#include <ParseMaterials.h>

#include<Face.h>
#include <vector>
#include<ParsePly.h>

#include "gtest/gtest.h"

namespace {
  class ParseMaterialsTest : public ::testing::Test {
  protected:
	  ParseMaterials * testObj;
  };
/*
  TEST_F(ParseMaterialsTest, TestParsedLight) {

	  vector<Face> f;
	  testObj = new ParseMaterials("input/airplane_materials.txt",  f, 0);

	  ASSERT_EQ(testObj->light_sources.at(0).isAmbient, true);

	  ASSERT_FLOAT_EQ(testObj->light_sources.at(0).rValue, 1.0);
	  ASSERT_FLOAT_EQ(testObj->light_sources.at(0).gValue, 1);
	  ASSERT_FLOAT_EQ(testObj->light_sources.at(0).bValue, 1);
  }

  TEST_F(ParseMaterialsTest, TestParsedLight2) {

	  vector<Face> f;
	  testObj = new ParseMaterials("input/airplane_materials.txt",  f, 0);

	  ASSERT_EQ(testObj->light_sources.at(1).isAmbient, false);

	  ASSERT_FLOAT_EQ(testObj->light_sources.at(1).rValue, 0);
	  ASSERT_FLOAT_EQ(testObj->light_sources.at(1).gValue, 0.1);
	  ASSERT_FLOAT_EQ(testObj->light_sources.at(1).bValue, 1);

	  ASSERT_FLOAT_EQ(testObj->light_sources.at(1).x_coordinate, 100);
	  ASSERT_FLOAT_EQ(testObj->light_sources.at(1).y_coordinate, 5);
	  ASSERT_FLOAT_EQ(testObj->light_sources.at(1).z_coordinate, 8);

  }
*/
  TEST_F(ParseMaterialsTest, TestFaceProperties) {

	  ParsePly *parse_ply;

	parse_ply = new ParsePly("airplane.ply");
	// Get faces and convert them into triangles
	parse_ply->ParseAllVertices("vertices.txt");
	parse_ply->ParseFaces("faces.txt");
	  vector<Face> f = parse_ply->GetParsedFaces();


	  testObj = new ParseMaterials("input/airplane_materials.txt",  f, 0);

	  ASSERT_FLOAT_EQ(f.at(619).getSpecularReflectance(),0);
	  ASSERT_FLOAT_EQ(f.at(619).getShininessExponent(),1);
	  ASSERT_FLOAT_EQ(f.at(1203).getDiffuseReflectance()[0],0);
	  ASSERT_FLOAT_EQ(f.at(1203).getDiffuseReflectance()[1],0);
	  ASSERT_FLOAT_EQ(f.at(1203).getDiffuseReflectance()[2],1);


	  ASSERT_FLOAT_EQ(f.at(2450).getDiffuseReflectance()[0],1);
	  ASSERT_FLOAT_EQ(f.at(2450).getDiffuseReflectance()[1],1);
	  ASSERT_FLOAT_EQ(f.at(2450).getDiffuseReflectance()[2],0);

  }

}
