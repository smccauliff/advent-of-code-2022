#include <aoc-2022.hpp>
#include <boost/lexical_cast.hpp>

 enum class OpCode {
  kNoop,
  kAddx,
};
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
      v.push_back(CpuState{opc, op_number++, opc == OpCode::kNoop ? static_cast<int64_t>(0) : boost::lexical_cast<int64_t>(line.data() + 6, line.size() - 6), 1});
      if (opc == OpCode::kAddx) {
        v.push_back(*v.rbegin());
      }
    }

    int64_t last_op_number = -1;
    for (auto& cpu_state : v) {
      if (cpu_state.op_number == last_op_number) {
        
      }
    }
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