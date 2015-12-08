/*
 * VertexTest.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: prashantm
 */

#include <string>
#include "gtest/gtest.h"
#include "Vertex.h"

using namespace std;

namespace {
  class VertexTest : public ::testing::Test {
  protected:
    Vertex *v1;
  };
  TEST_F(VertexTest, Vertex) {
	  v1 = new Vertex(12.0, -15.1234, 0.123, "0.145 8.945");
    ASSERT_FLOAT_EQ(v1->x_coordinate, 12.0);
	  ASSERT_FLOAT_EQ(v1->y_coordinate, -15.1234);
	  ASSERT_FLOAT_EQ(v1->z_coordinate, 0.123);
	  ASSERT_STREQ("0.145 8.945", v1->properties);
  }

}
