#include <aoc-2022.hpp>
#include <boost/icl/interval.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/lexical_cast.hpp>
#include <regex>
#include <string>
#include <iostream>

using boost::lexical_cast;

using elf_interval = boost::icl::discrete_interval<int64_t>::type;

constexpr int64_t Size(const elf_interval& i) {
  // Assuming closed, dynamic interval
  return i.upper() - i.lower() + 1;
}

int main(int argc, char** argv) {
  try {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    std::regex re("(\\d+)-(\\d+),(\\d+)-(\\d+)");

    int64_t full_overlap_count = 0;
    int64_t partial_or_complete_overlap_count = 0;
    for (const auto& line : lines) {
      if (line.empty()) {
        break;
      }

      //std::cout << line << std::endl;

      std::smatch base_match;
      if (!std::regex_match(line, base_match, re)) {
        THROW("Failed to parse line \"", line, "\"");
      }

      ALWAYS_ASSERT(base_match.size() == 5);
      // interval_set uses dynamic intervals which can be a mix of closed or open intervals.
      auto interval_a = elf_interval::closed(lexical_cast<int64_t>(base_match[1]), lexical_cast<int64_t>(base_match[2]));
      auto interval_b = elf_interval::closed(lexical_cast<int64_t>(base_match[3]), lexical_cast<int64_t>(base_match[4]));

      //std::cout << interval_a << " " << interval_b << std::endl;

      boost::icl::interval_set<int64_t> iset;
      elf_interval* larger_interval = nullptr;
      elf_interval* smaller_interval = nullptr;
      if (Size(interval_a) < Size(interval_b)) {
        larger_interval = &interval_b;
        smaller_interval = &interval_a;
      } else {
        larger_interval = &interval_a;
        smaller_interval = &interval_b;
      }
      iset.add(*larger_interval).add(*smaller_interval);
      //std::cout << iset << std::endl;
      if (Size(*larger_interval) == iset.size()) {
        ++full_overlap_count;
        ++partial_or_complete_overlap_count;
      } else if (Size(*larger_interval) + Size(*smaller_interval) > iset.size()) {
        ++partial_or_complete_overlap_count;
      }
    }

    std::cout << "Full overlap count " << full_overlap_count << std::endl;
    std::cout << "Partial or full overlap count " << partial_or_complete_overlap_count << std::endl;

    ALWAYS_ASSERT(full_overlap_count == 542);
    ALWAYS_ASSERT(partial_or_complete_overlap_count == 900);
  } catch (const std::string& err) {
    std::cerr << err << std::endl;
    return 1;
  } catch (const std::exception& sx) {
    std::cerr << sx.what() << std::endl;
    return 1;
  } catch (...) {
    return 1;
  }

}


