#include <armadillo>
#include <iterator>

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

// Doing this a proper template seems problematic.
arma::Mat<char>::const_row_iterator Increment(const arma::Mat<char>& m, arma::Mat<char>::const_row_iterator it, int x) {

  // Most of this complexity exists because -Wconversion and -Werror are on
  auto diff = static_cast<arma::uword>(x < 0 ? x : -x);
  auto col_diff = diff / m.n_cols;
  if (x < 0) {
    it.current_col -= col_diff;
  } else {
    it.current_col += col_diff;
  }

  auto row_diff = diff % m.n_cols;
  if (x < 0) {
    if (it.current_row - row_diff <= m.n_cols) {
      it.current_col
    }
  }

}

int64_t CountVisibleTrees(const arma::Mat<char> forest) {
  int64_t visible_trees = 0;
  for (uint64_t col = 1; col < forest.n_cols - 1; ++col) {
    for (uint64_t row = 1; row < forest.n_rows - 1; ++row) {
      if (Scan(forest.begin_col(col), forest.end_col(col) - (forest.n_rows - row))) {
        ++visible_trees;
      } else if (Scan(std::reverse_iterator(forest.end_col(col)), std::reverse_iterator(forest.begin_col(col) + row - 1))) {
        ++visible_trees;
      } else if (Scan(forest.begin_row(row), forest.end_row(row) - (forest.n_cols - col))) {
        ++visible_trees;
      } else if (Scan(std::reverse_iterator(forest.end_row(row)), std::reverse_iterator(forest.begin_row(row) + (col - 1)))) {
        ++visible_trees;
      }
    }
  }
  return visible_trees;
}