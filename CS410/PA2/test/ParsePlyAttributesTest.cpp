/*
 * ParsePlyAttributes_test.cpp
 *
 *  Created on: Sep 12, 2015
 *      Author: prashantm
 */

#include <ParsePlyAttributes.h>

#include <iostream>
#include <string>
#include "gtest/gtest.h"

using namespace std;

namespace {
  class ParsePlyAttributesTest : public ::testing::Test {
  protected:
	  ParsePlyAttributes *testObj;
  };
  TEST_F(ParsePlyAttributesTest, ParsePly) {

	  testObj = new ParsePlyAttributes();

	  testObj->SetNumberOfVertices(123456);

	  testObj->SetNumberOfFaces(789452);

	  ASSERT_EQ(testObj->GetNumberOfVertices(), 123456);
	  ASSERT_NE(testObj->GetNumberOfVertices(), 1236);
	  ASSERT_EQ(testObj->GetNumberOfFaces(), 789452);
  }


}
