#pragma once

#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>

#define ALWAYS_ASSERT(EXPR) \
  {                         \
    if (!(EXPR)) {          \
      std::abort();\
    } \
  }


namespace aoc2022::lib {
  std::vector<std::string> GetLines(std::string_view input_file_name);

  template<typename ...Args>
  void Log(std::stringstream& out, Args && ...args) {
    (out << ... << args);
  }
}

#define THROW(...)  \
  {                   \
    std::stringstream err; \
    aoc2022::lib::Log(err, __FILE_NAME__, __LINE__, __VA_ARGS__); \
    throw (err.str()); \
  }



