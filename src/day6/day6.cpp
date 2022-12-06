#include <aoc-2022.hpp>
#include <string>
#include <iostream>
#include <boost/intrusive/slist.hpp>
#include <boost/intrusive/set.hpp>

namespace bi = boost::intrusive;

struct SeenChar : public bi::set_base_hook<bi::link_mode<bi::auto_unlink>>, public bi::slist_base_hook<> {
  char c;

  SeenChar(char c) : c{c} {}
};

bool operator<(const SeenChar& a, const SeenChar& b) {
  return a.c < b.c;
}

bool operator==(const SeenChar& a, const SeenChar& b) {
  return a.c == b.c;
}

struct SeenCharDeleter {
  void operator()(SeenChar* s) {
    delete s;
  }
};

using SeenSet = bi::set<SeenChar, bi::constant_time_size<false>>;
// Can't use constant time size with auto-unlink
using SeenList = bi::slist<SeenChar, bi::cache_last<true>>;

struct Seen {
  SeenSet seen_set;
  SeenList seen_list;

  ~Seen() {
    //Only need to delete from one.
    seen_list.clear_and_dispose(SeenCharDeleter());
  }
};

static uint64_t LocateStartPattern(const std::string& line, const uint64_t n) {
  Seen seen;
  for (uint64_t i = 0; i < line.size(); i++) {
    auto* next_char = new SeenChar{line[i]};

    auto has_it = seen.seen_set.find(*next_char);
    if (has_it != seen.seen_set.end()) {
      while (true) {
        char current = seen.seen_list.front().c;
        seen.seen_list.pop_front_and_dispose(SeenCharDeleter());
        if (current == next_char->c) {
          break;
        }
      }
    }

    seen.seen_set.insert(*next_char);
    seen.seen_list.push_back(*next_char);

    if (seen.seen_list.size() == n) {
      return i + 1;
    }
  }

  if (seen.seen_list.size() == n) {
    return line.size();
  }

  THROW("Bad line ", line);
}

int main(int argc, char** argv) {
  return aoc2022::lib::CatchAndReport([argv]() {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    if (lines.rbegin()->empty()) {
      lines.pop_back();
    }

    for (const auto& line : lines) {
      auto packet_start_pos = LocateStartPattern(line, 4);
      std::cout << packet_start_pos << std::endl;
      auto message_start_pos = LocateStartPattern(line, 14);
      std::cout << message_start_pos << std::endl;
      ALWAYS_ASSERT(packet_start_pos == 1262);
      ALWAYS_ASSERT(message_start_pos == 3444);
    }
  });
}