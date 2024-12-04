#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main() {
  using namespace std::literals;
  const std::regex exp_regex("(mul\\(\\d{1,3},\\d{1,3}\\))|(don't\\(\\))|(do\\(\\))");
  const std::regex num_regex("\\d{1,3}");
  std::ifstream ifile("input.txt"s);
  std::string line;
  bool on{true};
  int sum{0};
  while(std::getline(ifile, line)) {
    for (std::smatch sm; std::regex_search(line, sm, exp_regex); line = sm.suffix()) {
      std::string exp = sm.str();
      if (exp == "do()"s) {
        on = true;
      } else if (exp == "don't()"s) {
        on = false;
      } else {
        if (on) {
          int product{1};
          for (std::smatch num_match; std::regex_search(exp, num_match, num_regex); exp = num_match.suffix()) {
            std::string num = num_match.str();
            product *= std::stoi(num);
          }
          sum += product;
        }
      }
    }
  }
  std::cout << sum << std::endl;

  return 0;
}
