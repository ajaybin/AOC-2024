#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <cmath>
using ulli_t = unsigned long long int;
using data_t = std::vector<std::pair<ulli_t, std::vector<ulli_t>>>;

ulli_t concat(ulli_t msb, ulli_t lsb) {
    return msb*pow(10,std::to_string(lsb).size()) + lsb;
}

void generate_tristate(std::vector<int>& tri, int iter_num, int N) {
    for (int i = 0; i < N; ++i) {
        tri.push_back((iter_num/static_cast<int>(pow(3.0,i)))%3);
    }
}

bool can_eval(ulli_t& result, std::vector<ulli_t> v) {
    ulli_t r{0};
    for (int i = 0; i < pow(3.0,v.size()-1); i++) {
        std::vector<int> b;
        generate_tristate(b,i,v.size()-1);
        r = *v.cbegin();
        int j = 0;
        for (auto it = v.cbegin()+1; it != v.cend(); ++it) {
            if (b[j] == 0) {
                r += *it;
            } else if (b[j] == 1) {
                r *= *it;
            } else if (b[j] == 2) {
                r = concat(r, *it);
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