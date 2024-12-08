#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <bitset>
#include <cmath>
using ulli_t = unsigned long long int;
using data_t = std::vector<std::pair<ulli_t, std::vector<ulli_t>>>;

bool can_eval(ulli_t& result, std::vector<ulli_t>& v) {
    std::bitset<64> b;
    ulli_t r{0};
    for (int i = 0; i < pow(2.0,v.size()-1); i++) {
        b = i;
        r = *v.cbegin();
        int j = 0;
        for (auto it = v.cbegin()+1; it != v.cend(); ++it) {
            if (b.test(j)) {
                r += *it;
            } else {
                r *= *it;
            }
            j++;
        }
        if (r == result) {
            return true;
        }
    }    
    return false;
}

int main() {
  std::ifstream ifile("input.txt");
  std::string line;
  std::string parts;
  bool flipflop{false};
  data_t data;
  std::vector<ulli_t> ele;
  ulli_t result;
  int linen{1};

  while(std::getline(ifile, line)) {
    std::stringstream ss{line};

    while(getline(ss, parts, ':')){
    // You now have separate entites here
        if (flipflop) {
            std::size_t pos;
            ele.clear();
            while (parts != "") {
                ulli_t i = std::stoull(parts, &pos);
                ele.push_back(i);
                parts = parts.substr(pos);
            }
        } else {
            if (ele.size() != 0) {
                data.push_back(std::make_pair(result, ele));
            }
            result = std::stoull(parts);
        }
        flipflop = !flipflop;
    }
    //std::cout << linen++ << std::endl;
  }
  data.push_back(std::make_pair(result, ele));
  ulli_t sum{0};
  for (auto d : data) {
    if (can_eval(d.first, d.second)) {
        sum += d.first;
    }
  }

  std::cout << sum << std::endl;

  return 0;
}