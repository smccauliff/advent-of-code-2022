#pragma once

#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

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

  template<typename F>
  int CatchAndReport(F f) {
    try {
      f();
      return 0;
    }  catch (const std::string& err) {
      std::cerr << err << std::endl;
      return 1;
    } catch (const std::exception& sx) {
      std::cerr << sx.what() << std::endl;
      return 1;
    } catch (...) {
      return 1;
    }
  }
}

#define THROW(...)  \
  {                   \
    std::stringstream err; \
    aoc2022::lib::Log(err, __FILE_NAME__, ":", __LINE__, " ", __VA_ARGS__); \
    throw (err.str()); \
  }



