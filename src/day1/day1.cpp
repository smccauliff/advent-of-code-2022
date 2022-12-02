#include <aoc-2022.hpp>
#include <optional>
#include <boost/lexical_cast.hpp>
#include <set>
#include <iostream>

int main(int argc, char** argv) {

  auto lines = aoc2022::lib::GetLines(argv[1]);

  int64_t accumulator = 0;
  std::set<int64_t> top_n;
  const int n = 3;
  for (const auto& line : lines) {
    if (line.empty()) {
      if (top_n.size() < n) {
        top_n.insert(accumulator);
      } else {
        for (auto it = top_n.rbegin(); it != top_n.rend(); ++it) {
          if (accumulator > *it) {
            top_n.insert(accumulator);
            top_n.erase(top_n.begin());
            break;
          }
        }
      }
      accumulator = 0;
    } else {
      accumulator += boost::lexical_cast<int64_t>(line);
    }
  }

  auto max = *top_n.rbegin();
  std::cout << "MAX: " << max << std::endl;
  ALWAYS_ASSERT(max == 72478);
  accumulator = 0;
  for (auto it = top_n.rbegin(); it != top_n.rend(); ++it) {
    std::cout << *it << " ";
    accumulator += *it;
  }
  std::cout << std::endl;
  std::cout << accumulator << std::endl;
  ALWAYS_ASSERT(accumulator == 210367);

}
