#include <aoc-2022.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <numeric>
#include <regex>

struct Dir;
struct Dir {
  int64_t recursive_size = 0;
  int64_t internal_size = 0;
  std::map<std::string, std::unique_ptr<Dir>> dirs;
  std::map<std::string, int64_t> files;
  Dir* parent;

  Dir(Dir* parent) : parent{parent} {}

  bool IsRoot() const {
    return parent == nullptr;
  }
};

template<typename F>
void DFS(Dir* dir,F visit_function) {

  for (auto& d : dir->dirs) {
    DFS(d.second.get(), visit_function);
  }
 return visit_function(dir);
}

int main(int argc, char** argv) {
  try {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    if (lines.rbegin()->empty()) {
      lines.pop_back();
    }

    Dir root{nullptr};
    Dir* pwd = &root;
    std::regex cd_regex{"cd (\\S+)"};
    std::regex dir_regex{"dir (\\S+)"};
    std::regex file_regex("(\\d+) (\\S+)");
    for (const auto& line : lines) {
      std::smatch m;
      if (std::regex_search(line, m, cd_regex)) {
        if (m[1] == "/") {
          pwd = &root;
        } else if (m[1] == "..") {
          if (pwd->parent == nullptr) {
            THROW("Attempt to cd .. past root.");
          }
          pwd = pwd->parent;
        } else {
          //Actually this is possible, but we aren't given a spec for cd returning an error
          if (pwd->dirs.find(m[1]) == pwd->dirs.end()) {
            THROW("Can't cd into directory ", m[1]);
          }
          pwd = pwd->dirs.find(m[1])->second.get();
        }
      } else if (line.starts_with("$ ls")) {
        // OK
      } else if (std::regex_search(line, m, dir_regex)) {
        auto [it, ok] = pwd->dirs.try_emplace(m[1], new Dir(pwd));
        if (!ok) {
          THROW("Failed to emplace directory ", m[1]);
        }
      } else if (std::regex_match(line, m, file_regex)) {
        auto [it, ok] = pwd->files.emplace(m[2], boost::lexical_cast<int64_t>(m[1]));
        if (!ok) {
          THROW("Failed to emplace file ", m[2]);
        }
      } else {
        THROW("Bad line ", line);
      }
    }

    DFS(&root, [](Dir* d) {
      d->internal_size = std::accumulate(d->files.begin(), d->files.end(), static_cast<int64_t>(0), [](int64_t init, const auto& p) {
        return init + p.second;
      });
      d->recursive_size = std::accumulate(d->dirs.begin(), d->dirs.end(), d->internal_size, [](int64_t init, const auto& p) {
        return init + p.second->recursive_size;
      });
    });


    int64_t count = 0;
    DFS(&root, [&count](const Dir* d) {
      if (d->recursive_size < 100'000) {
        count += d->recursive_size;
      }
    });
    std::cout << count << std::endl;

    const int64_t target_size = 30000000-(70000000-root.recursive_size);
    int64_t closest_size = std::numeric_limits<int64_t>::max();
    std::string closest_dir_name;
    DFS(&root, [&closest_size, &closest_dir_name, target_size] (const Dir* d) {
      if (closest_size > d->recursive_size && d->recursive_size >= target_size) {
        closest_size = d->recursive_size;
        if (d->IsRoot()) {
          closest_dir_name = "/";
        } else {
          for (auto it = d->parent->dirs.begin(); it != d->parent->dirs.end(); ++it) {
            if (it->second.get() == d) {
              closest_dir_name = it->first;
              break;
            }
          }
        }
      }
    });
    std::cout << closest_dir_name << " " << closest_size << std::endl;
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
