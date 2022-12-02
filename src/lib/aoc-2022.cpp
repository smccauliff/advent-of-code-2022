#include <aoc-2022.hpp>

#include <fstream>

std::vector<std::string> aoc2022::lib::GetLines(std::string_view file_name) {

  std::ifstream in;
  in.open(std::string(file_name), std::ios::binary | std::ios::in);
  if (!in.good()) {
    THROW("Failed to open ", file_name);
  }

  std::vector<std::string> v;

  while (!in.eof() && in.good()) {
    std::string line;
    std::getline(in, line);
    v.emplace_back(std::move(line));
  }

  if (in.bad()) {
    THROW("file stream in bad state");
  }

  return v;
}
