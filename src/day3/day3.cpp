#include <aoc-2022.hpp>
#include <string>
#include <iostream>
#include <utility>
#include <unordered_set>
#include <optional>

constexpr std::pair<std::string_view, std::string_view> ToSacs(std::string_view src) {
  auto split_at = src.size() / 2;
  return std::make_pair(src.substr(0, split_at), src.substr(split_at));
}

static char SingleIntersect(std::string_view a, std::string_view b) {
  std::unordered_set<char> a_set;
  a_set.insert(a.begin(), a.end());
  std::optional<char> found;
  for (char x : b) {
    if (a_set.contains(x)) {
      if (found && found.value() != x) {
        THROW("Found duplicate intersections in ", a, " ", b, " of ", found.value(), " and ", x);
      } else if (!found) {
        found = x;
      }
    }
  }
  return found.value();
}

static char SingleIntersect(std::vector<std::unordered_set<char>> sets) {
  if (sets.size() < 2) {
    THROW("Invalid number of sets ", sets.size());
  }

  auto it = sets.begin();
  auto possible_unqiue = *it;
  ++it;
  while (it != sets.end()) {
    const auto& s = *it;
    auto unique_it = possible_unqiue.begin();
    while (unique_it != possible_unqiue.end()) {
      auto u = *unique_it;
      ++unique_it;
      if (!s.contains(u)) {
        possible_unqiue.erase(u);
      }
    }
    ++it;
  }

  if (possible_unqiue.size() != 1) {
    THROW("Failed to find unique ");
  }
  return *possible_unqiue.begin();
}

constexpr int64_t Score(char x) {
  if (x >= 'a') {
    // lowercase
    return x - 'a' + 1;
  } else {
    // uppercase
    return x - 'A' + 27;
  }
}


int main(int argc, char** argv) {
  try {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    int64_t accumulator = 0;
    std::vector<std::unordered_set<char>> elf_group;
    int64_t line_count = 0;
    int64_t badge_accumulator = 0;
    for (const auto& line : lines) {
      if (line.empty()) {
        break;
      }
      if (line.size() % 2 != 0) {
        THROW("Invalid line ", line);
      }

      auto sacs = ToSacs(line);
      auto intersection = SingleIntersect(sacs.first, sacs.second);
      accumulator += Score(intersection);
      elf_group.emplace_back(line.begin(), line.end());
      ++line_count;
      if (line_count % 3 == 0) {
        auto badge = SingleIntersect(elf_group);
        badge_accumulator += Score(badge);
        elf_group.clear();
      }
    }

    std::cout << accumulator << std::endl;
    std::cout << badge_accumulator << std::endl;
    ALWAYS_ASSERT(accumulator == 7727);
    ALWAYS_ASSERT(badge_accumulator == 2609);
  } catch (const std::string& err) {
    std::cerr << err << std::endl;
    return 1;
  } catch (...) {
    return 1;
  }
}