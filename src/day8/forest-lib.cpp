#include "forest-lib.hpp"

#include <algorithm>

namespace bu = boost::numeric::ublas;

template<typename I, typename V>
auto Scan(I start, I end, V visitor) {
  char max = *start;
  //std::cout << "max " << max << std::endl;
  auto it = start + 1;
  for (; it < end; ++it) {
    if (*it >= max) {
      return visitor(it - start, false);
    }
  }
  return visitor(it - start, true);
}
template<typename V>
auto ScanUp(const bu::matrix<char>& forest, int64_t row, int64_t col, V visitor) {
  return Scan((forest.begin2() + col).rbegin() + (static_cast<int64_t>(forest.size1()) - row - 1), (forest.begin2() + col).rend(), visitor);
}

template<typename V>
auto ScanDown(const bu::matrix<char>& forest, int64_t row, int64_t col, V visitor) {
  return Scan((forest.begin2() + col).begin() + row, (forest.begin2() + col).end(), visitor);
}

template<typename V>
auto ScanRight(const bu::matrix<char>& forest, int64_t row, int64_t col, V visitor) {
  return Scan((forest.begin1() + row).begin() + col, (forest.begin1() + row).end(), visitor);
}

template<typename V>
auto ScanLeft(const bu::matrix<char>& forest, int64_t row, int64_t col, V visitor) {
  return Scan((forest.begin1() + row).rbegin() + (static_cast<int64_t>(forest.size2()) - col - 1), (forest.begin1() + row).rend(), visitor);
}


int64_t CountVisibleTrees(const bu::matrix<char>& forest) {
  int64_t visible_trees = 0;
  auto is_visible = [](ptrdiff_t distance, bool at_edge) {
    return at_edge;
  };
  for (int64_t row = 1; row < forest.size1() - 1; ++row) {
    for (int64_t col = 1; col < forest.size2() - 1; ++col) {
      // Scan down a column to the target element
      if (ScanUp(forest, row, col, is_visible) || ScanDown(forest, row, col, is_visible) || ScanRight(forest, row, col, is_visible) || ScanLeft(forest, row, col, is_visible)) {
        ++visible_trees;
      }
    }
  }

  return visible_trees;
}

int64_t MaxScenicScore(const bu::matrix<char>& forest) {
  int64_t max_score = -1;
  for (int64_t row = 1; row < forest.size1() - 1; ++row) {
    for (int64_t col = 1; col < forest.size2() - 1; ++col) {

      auto trees_seen = [](ptrdiff_t distance, bool at_edge) {
        return static_cast<int64_t>(distance - (at_edge ? 1 : 0));
      };
      auto up = ScanUp(forest, row, col, trees_seen);
      auto down =  ScanDown(forest, row, col, trees_seen);
      auto left = ScanLeft(forest, row, col, trees_seen);
      auto right = ScanRight(forest, row, col, trees_seen);

      //std::cout << "(" << row << "," << col << ") up " << up << " down " << down << " left " << left << " right " << right << std::endl;
      max_score = std::max(max_score, up * down * left * right);
    }
  }

  return max_score;
}