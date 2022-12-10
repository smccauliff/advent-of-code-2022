#include <aoc-2022.hpp>
#include "forest-lib.hpp"
#include <armadillo>

int main(int argc, char** argv) {
  try {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    if (lines.rbegin()->empty()) {
      lines.pop_back();
    }

    arma::Mat<char> forest(lines.size(), lines.begin()->size());
    for (uint64_t row = 0; row < lines.size(); ++row) {
      const auto& line = lines[row];
      for (uint64_t col = 0; col < line.size(); ++col) {
        forest(row, col) = line[col];
      }
    }

    auto visible_trees = CountVisibleTrees(forest);
    visible_trees += forest.n_rows * 2 + forest.n_cols * 2 - 4;
    std::cout << visible_trees << std::endl;
  } catch (const std::string& err) {
    std::cerr << err << std::endl;
    return 1;
  } catch (const std::exception& sx) {
    std::cerr << sx.what() << std::endl;
    return 1;
  } catch (...) {
    return 1;
  }

  return 0;
}