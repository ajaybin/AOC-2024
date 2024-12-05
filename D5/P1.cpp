#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <sstream>

int main() {
  std::ifstream ifile1("input1.txt");
  std::ifstream ifile2("input2.txt");
  std::string line;
  std::map<int, std::vector<int>> m;

  
  while(std::getline(ifile1, line)) {
    std::size_t pos;
    int c1 = std::stoi(line, &pos);
    int c2 = std::stoi(line.substr(pos+1));
    m[c1].push_back(c2);
  }

  std::vector<std::vector<int>> v;
  while (std::getline(ifile2, line)) {
    std::vector<int> lv;
    std::stringstream ss(line);

    while(ss.good()) {
        std::string num;
        std::getline(ss, num, ',');
        lv.push_back(std::stoi(num));
    }

    v.push_back(lv);
  }

  int sum{0};
  for (auto vec : v) {
    bool is_ord = true;
    for (int i = 0; i < vec.size()-1; ++i) {
        auto ele = vec[i];
        if (m.contains(ele)) {
            std::vector<int> order_v = m[ele];
            for (int j = i+1; j < vec.size(); ++j) {
                if (std::find(order_v.cbegin(), order_v.cend(), vec[j]) == order_v.cend()){
                    is_ord = false;
                }
            }
        } else {
            is_ord = false;
            break;
        }
    }
    if (is_ord) {
        sum += vec[vec.size()/2];
    } else {
    }
  }

  std::cout << sum << std::endl;

  ifile1.close();
  ifile2.close();
  return 0;
}