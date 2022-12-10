#include "forest-lib.hpp"

namespace bu = boost::numeric::ublas;

template<typename I>
bool Scan(I it, I end) {
  char max = *end;
  for (; it < end; ++it) {
    if (*it >= max) {
      return false;
    }
  }
  return true;
}


int64_t CountVisibleTrees(const bu::matrix<char>& forest) {
  int64_t visible_trees = 0;
  for (int64_t row = 1; row < forest.size1() - 1; ++row) {
    for (int64_t col = 1; col < forest.size2() - 1; ++col) {
      // Scan down a column to the target element
      if (Scan((forest.begin2() + col).begin(), (forest.begin2() + col).begin() + row)) {
        ++visible_trees;
      } else if (Scan((forest.begin2() + col).rbegin(), (forest.begin2() + col).rbegin() + (static_cast<int64_t>(forest.size1()) - row - 1))) {
        ++visible_trees;
      } else if (Scan((forest.begin1() + row).begin(), (forest.begin1() + row).begin() + col)) {
        ++visible_trees;
      } else if (Scan((forest.begin1() + row).rbegin(), (forest.begin1() + row).rbegin() + (static_cast<int64_t>(forest.size2()) - col - 1))) {
        ++visible_trees;
      }
    }
  }

  return visible_trees;
}