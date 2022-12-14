#include <aoc-2022.hpp>
#include "forest-lib.hpp"
#include <boost/numeric/ublas/matrix.hpp>

namespace bu = boost::numeric::ublas;

int main(int argc, char** argv) {
  try {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    if (lines.rbegin()->empty()) {
      lines.pop_back();
    }

    bu::matrix<char> forest(lines.size(), lines.begin()->size());
    for (uint64_t row = 0; row < lines.size(); ++row) {
      const auto& line = lines[row];
      for (uint64_t col = 0; col < line.size(); ++col) {
        forest(row, col) = line[col];
      }
    }

    auto visible_trees = CountVisibleTrees(forest);
    visible_trees += forest.size1() * 2 + forest.size2() * 2 - 4;
    std::cout << visible_trees << std::endl;

    auto sceneic_score = MaxScenicScore(forest);
    std::cout << sceneic_score << std::endl;

    ALWAYS_ASSERT(visible_trees == 1698);
    ALWAYS_ASSERT(sceneic_score == 672280);
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