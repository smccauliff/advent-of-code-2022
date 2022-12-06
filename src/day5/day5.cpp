#include <aoc-2022.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include <regex>

using boost::lexical_cast;

struct Move {
  uint64_t src;
  uint64_t dest;
  uint64_t count;

  Move(uint64_t s, uint64_t d, uint64_t c) : src{s},  dest{d}, count{c} {}
};

constexpr uint64_t StackIndexToCharIndex(uint64_t stack_index) {
    return 1 + stack_index * 4;
};

struct CargoStacks {
  std::vector<std::string> stacks;

  void ApplyMove(const Move& m, bool bulk_move = false) {
    if (m.src == m.dest) {
      THROW("Src and dest are equal. ", m.src);
    }
    auto& dest = stacks[m.dest];
    auto& src = stacks[m.src];
    for (int64_t i = 0; i < m.count; ++i) {
      dest.push_back(src.back());
      src.pop_back();
    }
    if (bulk_move) {
      int64_t original_size = static_cast<int64_t>(dest.size() - m.count);
      std::reverse(dest.begin() + original_size, dest.end());
    }
  }

  void ReverseAll() {
    std::for_each(stacks.begin(), stacks.end(), [](std::string& s) {
      std::reverse(s.begin(), s.end());
    });
  }


};


CargoStacks ParseCargoStacks(std::vector<std::string>::const_iterator start, std::vector<std::string>::const_iterator end) {

  //Find the character positions that label the boxes
  // end->begin() is the first character in the line that end points to
  const auto stack_count = std::count_if(end->begin(), end->end(), [](auto c) {
    return c >= '0' && c <= '9';
  });


  CargoStacks rv;
  rv.stacks.resize(static_cast<size_t>(stack_count), "");
  auto it = start;
  while (it != end) {
    for (uint64_t stack_index = 0; StackIndexToCharIndex(stack_index) < it->size() && stack_index < stack_count; ++stack_index)  {
      const auto char_index = StackIndexToCharIndex(stack_index);
      if ((*it)[char_index] != ' ') {
        rv.stacks[stack_index].push_back((*it)[char_index]);
      }
    }
    ++it;
  }

  rv.ReverseAll();
  return rv;
}


std::vector<Move> ParseMoves(std::vector<std::string>::const_iterator start, std::vector<std::string>::const_iterator end) {
  std::vector<Move> moves;
  auto it = start;
  std::regex re{"move (\\d+) from (\\d+) to (\\d+)"};
  while (it != end && !it->empty()) {
    std::smatch smatch;
    if (!std::regex_match(*it, smatch, re)) {
      THROW("Bad line ", *it);
    }
    moves.emplace_back(boost::lexical_cast<uint64_t>(smatch[2]) - 1, boost::lexical_cast<uint64_t>(smatch[3]) - 1, boost::lexical_cast<uint64_t>(smatch[1]));
    ++it;
  }
  return moves;
}

int main(int argc, char** argv) {
   try {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    if (lines.rbegin()->empty()) {
      lines.pop_back();
    }

    auto it = lines.cbegin();
    while (it != lines.end() && it->find_first_of('[') != std::string::npos) {
      ++it;
    }

    auto cargo_stacks = ParseCargoStacks(lines.cbegin(), it);
    auto cargo_stacks_2 = cargo_stacks;
    auto moves = ParseMoves(it + 2, lines.end());
    for (const auto& m : moves) {
      cargo_stacks.ApplyMove(m);
    }
    std::string single_move_top_stack;
    for (const auto& stack : cargo_stacks.stacks) {
      single_move_top_stack.push_back(stack.back());
    }
    ALWAYS_ASSERT(single_move_top_stack == "QNNTGTPFN");
    std::cout << "single move: " << single_move_top_stack << std::endl;

    for (const auto& m : moves) {
      cargo_stacks_2.ApplyMove(m, true);
    }
    std::string bulk_move_top_stack;
    for (const auto& stack : cargo_stacks_2.stacks) {
      bulk_move_top_stack.push_back(stack.back());
    }
    std::cout << "bulk move: " << bulk_move_top_stack << std::endl;
    ALWAYS_ASSERT(bulk_move_top_stack == "GGNPJBTTR");
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