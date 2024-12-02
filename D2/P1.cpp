#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

bool isSafe(std::vector<int> vec) {
    std::adjacent_difference(vec.begin(), vec.end(), vec.begin());
    bool is_positive = vec[1] > 0;
    bool is_zero = vec[1] == 0;
    bool success = true;
    if (!is_zero) {
      for(int i = 1; i < vec.size(); ++i) {
        if (std::abs(vec[i]) < 1 || std::abs(vec[i]) > 3) {
            success = false;
        }
        if ((vec[i] > 0) != is_positive || vec[i] == 0) {
            success = false;
        }
      }
    } else {
        success = false;
    }
    return success;
}

int main() {
  std::ifstream ifile("input.txt");
  std::string line;
  int num_safe{0};

  while(std::getline(ifile, line)) {
    std::size_t pos;
    std::vector<int> v;
    int i{0};

    while(line != "") {
      i = std::stoi(line, &pos);
      v.push_back(i);
      line = line.substr(pos);
    }
    if (isSafe(v)) {
        num_safe += 1;
    }
  }
  std::cout << num_safe << std::endl;
  return 0;
}