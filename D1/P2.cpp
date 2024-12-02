#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
int main() {
  std::ifstream ifile("input.txt");
  std::string line;

  std::vector<int> col1;
  std::map<int, int> m;
  
  while(std::getline(ifile, line)) {
    std::size_t pos;
    int i{std::stoi(line, &pos)};
    col1.push_back(i);
    i = std::stoi(line.substr(pos));
    m[i]++;
  }

  int s{0};
  std::for_each(col1.begin(), col1.end(), [&m, &s](const int& n) {m.contains(n) ? s += m[n] * n : s+=0;});
  std::cout << s;
  return 0;
}