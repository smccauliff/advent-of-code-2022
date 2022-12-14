#include <gtest/gtest.h>
#include "forest-lib.hpp"
#include <iostream>
#include <sstream>
#include <boost/numeric/ublas/io.hpp>

using boost::numeric::ublas::matrix;

// This is dummy test so we can run all the tests from clion
class ScanTest : public ::testing::Test {
 public:
  static matrix<char> Parse(const char *init) {
    std::stringstream ss(init);
    matrix<char> m;
    ss >> m;
    assert(ss.good());
    return m;
  }
  virtual ~ScanTest() = default;
};

TEST_F(ScanTest, TopDownScan) {
  auto init = "[3,3]((0, 1, 2), (6, 4, 5), (6, 7, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(1, CountVisibleTrees(m0));
}

TEST_F(ScanTest, BottomUpScan) {
  auto init = "[3,3]((0, 4, 2), (6, 4, 5), (6, 3, 8))";
  matrix<char> m0 = Parse(init);
  ASSERT_EQ(1, CountVisibleTrees(m0));
}


TEST_F(ScanTest, LeftRightScan) {
 auto init =  "[3,3]((0, 4, 2), (3, 4, 5), (6, 6, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(1, CountVisibleTrees(m0));
}

TEST_F(ScanTest, RightLeftScan) {
 auto init =  "[3,3]((0, 4, 2), (8, 4, 2), (6, 7, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(1, CountVisibleTrees(m0));
}

TEST_F(ScanTest, NothingFound) {
  auto init = "[3,3]((0, 4, 2),(5, 4, 6),(6, 7, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(0, CountVisibleTrees(m0));
}

TEST_F(ScanTest, BoxedInSceneicScore) {
  auto init = "[3,3]((0, 4, 2),(5, 4, 6),(6, 7, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(1, MaxScenicScore(m0));
}

TEST_F(ScanTest,UpSceneicScore) {
  auto init = "[3,3]((0, 2, 2),(5, 4, 6),(6, 7, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(2, MaxScenicScore(m0));
}

TEST_F(ScanTest, DownSceneicScore) {
  auto init = "[3,3]((0, 5, 2),(5, 4, 6),(6, 0, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(2, MaxScenicScore(m0));
}


TEST_F(ScanTest, LeftSceneicScore) {
  auto init = "[3,3]((0, 5, 2),(5, 4, 0),(6, 9, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(2, MaxScenicScore(m0));
}

TEST_F(ScanTest, RightSceneicScore) {
  auto init = "[3,3]((0, 5, 2),(0, 4, 6),(6, 9, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(2, MaxScenicScore(m0));
}

TEST_F(ScanTest, MulipleRowsBlockedInMiddle) {
   auto init = "[4,3]((0, 5, 2),(8, 5, 6),(8, 4, 7), (6, 9, 8))";

  matrix<char> m0 = Parse(init);
  ASSERT_EQ(2, MaxScenicScore(m0));
}