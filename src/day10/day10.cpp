#include <aoc-2022.hpp>
#include <boost/lexical_cast.hpp>

enum class OpCode {
  kNoop,
  kAddx,
};
std::ostream& operator<<(std::ostream& out, OpCode op_code) {
  switch (op_code) {
    case OpCode::kAddx: out << "addx"; break;
    case OpCode::kNoop: out << "noop"; break;
  }
  return out;
}
struct CpuState {
  OpCode op;
  int64_t op_number;
  int64_t operand;
  int64_t register_value;
};

int main(int argc, char** argv) {
  try {
    auto lines = aoc2022::lib::GetLines(argv[1]);

    if (lines.rbegin()->empty()) {
      lines.pop_back();
    }

    std::vector<CpuState> v;
    int64_t op_number = 0;
    for (const auto& line : lines) {
      OpCode opc = line.starts_with("addx") ? OpCode::kAddx : OpCode::kNoop;
      v.push_back(CpuState{opc, ++op_number, opc == OpCode::kNoop ? static_cast<int64_t>(0) : boost::lexical_cast<int64_t>(line.data() + 5, line.size() - 5), 1});
      if (opc == OpCode::kAddx) {
        v.push_back(*v.rbegin());
      }
    }

    int64_t last_op_number = -1;
    int64_t register_value = 1;
    for (auto& cpu_state : v) {
      if (cpu_state.op_number == last_op_number && cpu_state.op == OpCode::kAddx) {
        cpu_state.register_value = register_value + cpu_state.operand;
        register_value = cpu_state.register_value;
      } else {
        cpu_state.register_value = register_value;
      }
      last_op_number = cpu_state.op_number;
    }

    for (uint64_t i = 0; i < 10; i++) {
      std::cout << i << " " << v[i].op << " " << v[i].operand << " " << v[i].register_value << " " << v[i].op_number << std::endl;
    }
    std::vector<size_t> interesting_indices = {20, 60, 100, 140, 180, 220 };
    int64_t signal_strength = 0;
    for (auto i : interesting_indices) {
     // std::cout << i << " " << v[i - 2].register_value << std::endl;
      signal_strength += v[i - 2].register_value * static_cast<int64_t>(i);
    }
    std::cout << signal_strength << std::endl;
    const int64_t display_count = 240;
    // The first two values will always be on because initial value is 1, noop does nothing and addx takes 2 cycles
    // to compute
    std::stringstream result;
    result << "#";
    for (int64_t display_index = 1; display_index < display_count; ++display_index) {
      //register value -1 would seem to be correct according to the specification, but...
      int64_t sprite_x_position = v[static_cast<uint64_t>(display_index - 1)].register_value;
//      std::cout << display_index << " " << sprite_position << std::endl;
      int64_t display_x_position = display_index % 40;
      if (display_x_position == 0) {
        result << std::endl;
      }
      if (std::abs(sprite_x_position - display_x_position) <= 1) {
        result << '#';
      } else {
        result << ' ';
      }
    }

    result << std::endl;
    std::cout << result.str();
    std::cout << "-----------------------------" << std::endl;
    std::string expected = R"delimiter(##..##..##..##..##..##..##..##..##..##..
###...###...###...###...###...###...###.
####....####....####....####....####....
#####.....#####.....#####.....#####.....
######......######......######......####
#######.......#######.......#######.....
)delimiter";
    std::cout << expected;
    assert(result.str() == expected);
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