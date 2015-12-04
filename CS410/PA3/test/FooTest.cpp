/*
 * FooTest.cpp
 *
 *  Created on: Sep 19, 2015
 *      Author: prashantm
 */


#include "gtest/gtest.h"
#include "Foo.h"
namespace {
  class FooTest : public ::testing::Test {
  protected:
    Foo foo;
  };
  TEST_F(FooTest, Foo) {
    ASSERT_TRUE(foo.foo());
  }
}
