#include <aoc-2022.hpp>
#include <optional>
#include <string_view>
#include <iostream>

const char kOpponentRock = 'A';
const char kOpponentPaper = 'B';
const char kOpponentScissors = 'C';
const char kMyRock = 'X';
const char kMyPaper = 'Y';
const char kMyScissors = 'Z';
[[maybe_unused]] const char kChoiceLoose = 'X';
const char kChoiceDraw = 'Y';
const char kChoiceWin = 'Z';

constexpr int64_t WinScore(const char opponent_move, const char my_move) {
  if (opponent_move + (kMyRock - kOpponentRock) == my_move ) {
    return 3;
  }
  if (opponent_move == kOpponentRock) {
    return my_move == kMyPaper ? 6 : 0;
  } else if (opponent_move == kOpponentPaper) {
    return my_move == kMyScissors ? 6 : 0;
  } else if (opponent_move == kOpponentScissors) {
    return my_move == kMyRock ? 6 : 0;
  } else {
    ALWAYS_ASSERT(false);
    return false;
  }
}

constexpr int64_t ScoreForMyChoice(const char mine) {
  return mine == kMyRock ? 1 : (mine == kMyPaper ? 2 : 3);
}

constexpr int64_t ScoreWinLooseDraw(const char opponent, const char mine) {
  int8_t choice = opponent - kOpponentRock;
  int8_t select = mine == kChoiceDraw ? 0 : (mine == kChoiceWin ?  1 : -1);
  choice += select;
  choice %= 3;
  if (choice < 0) {
    choice = 3 + choice;
  }
  choice += kMyRock;

  int64_t score = ScoreForMyChoice(static_cast<const char>(choice));
  return score + WinScore(opponent, static_cast<const char>(choice));
}

constexpr int64_t Score(const char opponent, const char mine) {
  if (opponent < kOpponentRock || opponent > kOpponentScissors) {
    THROW("bad opponent input ", opponent);
  }
  if (mine < kMyRock || mine > kMyScissors) {
    THROW("bad input for me ", mine);
  }

  int64_t score = ScoreForMyChoice(mine);
  score += WinScore(opponent, mine);
  return score;
}

int main(int argc, char** argv) {
//  for (char opponent = kOpponentRock; opponent <= kOpponentScissors; opponent++) {
//    for (char wld = kChoiceLoose; wld <= kChoiceWin; wld++) {
//      std::cout << ScoreWinLooseDraw(opponent, wld) << std::endl;
//    }
//  }

  try {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    int64_t accumulator = 0;
    int64_t win_lose_draw_accumultor = 0;
    for (const auto& line : lines) {
      // I still can't use c++-20 range and split
      if (line.size() == 0) {
        break;
      } else if (line.size() != 3) {
        THROW("Invalid line ", line);
      }
      const char opponent = line[0];
      const char mine = line[2];
      accumulator += Score(opponent, mine);
      win_lose_draw_accumultor += ScoreWinLooseDraw(opponent, mine);
    }

    std::cout << "score: " << accumulator << std::endl;
    std::cout << "win/loose/draw : " << win_lose_draw_accumultor << std::endl;
    ALWAYS_ASSERT(accumulator == 8392);
    ALWAYS_ASSERT(win_lose_draw_accumultor == 10116);
  } catch (const std::string& err) {
    std::cerr << err << std::endl;
    return 1;
  } catch (...) {
    return 1;
  }
}