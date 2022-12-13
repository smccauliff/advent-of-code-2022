#include <aoc-2022.hpp>
#include <boost/lexical_cast.hpp>
#include <set>

struct Position {
  int64_t row;
  int64_t col;

  Position() : row{0}, col{0} {}
  Position(int64_t r, int64_t c) : row{r}, col{c} {}
  Position(const Position&) = default;
  Position& operator=(const Position&) = default;

  bool IsAdjacent(const Position& pos) {
    return std::abs(pos.row - this->row) <= 1 && std::abs(pos.col - this->col) <= 1;
  }

  Position ApplyMove(char direction) {
    switch (direction) {
      case 'U': return Position(row + 1, col);
      case 'D': return Position(row - 1, col);
      case 'L': return Position(row, col - 1);
      case 'R': return Position(row, col + 1);
    }
    THROW("Invalid move ", direction);
  }

};

int operator<=>(const Position& a, const Position& b) {
    if (a.row != b.row) {
      return static_cast<int>(a.row - b.row);
    }
    return static_cast<int>(a.col - b.col);
}

std::ostream& operator<<(std::ostream& out, const Position& pos) {
  out << pos.row << "," << pos.col;
  return out;
}

int main(int argc, char** argv) {
  try {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    if (lines.rbegin()->empty()) {
      lines.pop_back();
    }

    std::set<Position> visited;

    Position head;
    Position tail;

    visited.insert(tail);
    for (const auto& line : lines) {
      char direction = line[0];
      auto magnitude = boost::lexical_cast<int64_t>(line.data() + 2, line.size() - 2);
      for (int64_t i = 0; i < magnitude; i++) {
        head = head.ApplyMove(direction);
        if (head.IsAdjacent(tail)) {
          continue;
        }
        //std::cout << head << " " << tail << std::endl;
        if (tail.row < head.row) {
          ++tail.row;
        } else if (tail.row > head.row){
          --tail.row;
        }
        if (tail.col < head.col) {
          ++tail.col;
        } else if (tail.col > head.col) {
          --tail.col;
        }
        visited.insert(tail);
      }
    }
    std::cout << visited.size() << std::endl;
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