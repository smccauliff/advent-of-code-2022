#include <gtest/gtest.h>
#include "forest-lib.hpp"
#include <armadillo>
#include <iostream>

// This is dummy test so we can run all the tests from clion
class ScanTest : public ::testing::Test {
 public:
  virtual ~ScanTest() = default;
};

TEST_F(ScanTest, TopDownScan) {
  arma::Mat<char> m0 = {{0, 1, 2},
                        {6, 4, 5},
                        {6, 7, 8}
                       };
  ASSERT_EQ(1, CountVisibleTrees(m0));
}

TEST_F(ScanTest, BottomUpScan) {
  arma::Mat<char> m0 = {{0, 4, 2},
                        {6, 4, 5},
                        {6, 3, 8}
                       };
  ASSERT_EQ(1, CountVisibleTrees(m0));
}

TEST_F(ScanTest, LeftRightScan) {
  arma::Mat<char> m0 = {{0, 4, 2},
                        {3, 4, 5},
                        {6, 6, 8}
                       };
  ASSERT_EQ(1, CountVisibleTrees(m0));
}

TEST_F(ScanTest, NothingFound) {
  arma::Mat<char> m0 = {{0, 4, 2},
                        {5, 4, 6},
                        {6, 7, 8}
                       };
  ASSERT_EQ(0, CountVisibleTrees(m0));
}