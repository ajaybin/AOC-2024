#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main() {
  using namespace std::literals;
  const std::regex exp_regex("mul\\(\\d{1,3},\\d{1,3}\\)");
  const std::regex num_regex("\\d{1,3}");
  std::ifstream ifile("input.txt"s);
  std::string line;
  int sum{0};
  while(std::getline(ifile, line)) {
    for (std::smatch sm; std::regex_search(line, sm, exp_regex);) {
      std::string exp = sm.str();
      int product{1};
      for (std::smatch num_match; std::regex_search(exp, num_match, num_regex);) {
        std::string num = num_match.str();
        product *= std::stoi(num);
        exp = num_match.suffix();
      }
      sum += product;
      line = sm.suffix();
    }
  }
  std::cout << sum << std::endl;

  return 0;
}