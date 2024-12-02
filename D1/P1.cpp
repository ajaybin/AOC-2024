#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
  std::ifstream ifile("input.txt");
  std::string line;

  std::vector<int> col1;
  std::vector<int> col2;
  
  while(std::getline(ifile, line)) {
    std::size_t pos;
    int i{std::stoi(line, &pos)};
    col1.push_back(i);
    i = std::stoi(line.substr(pos));
    col2.push_back(i);
  }
  std::sort(col1.begin(), col1.end());
  std::sort(col2.begin(), col2.end());

  std::vector<int> diff(col1.size());
  std::transform(col1.cbegin(), col1.cend(), col2.cbegin(), diff.begin(), [](const int& c1, const int& c2){ return std::abs(c1 - c2); });

  std::cout << std::reduce(diff.begin(), diff.end()) << std::endl;
  return 0;
}