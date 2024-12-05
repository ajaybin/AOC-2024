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
  ifile1.close();

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
  ifile2.close();

  int sum{0};
  for (auto vec : v) {
    bool is_ord = std::is_sorted(vec.cbegin(), vec.cend(),[&m](const int&a, const int&b)
      {
        return std::find(m[a].cbegin(), m[a].cend(), b) != m[a].cend();
      });
    if (is_ord) {
    } else {
        std::sort(vec.begin(), vec.end(), 
          [&m](const int& a, const int& b)
          {
            return (std::find(m[a].cbegin(), m[a].cend(), b) != m[a].cend());
          });
        sum += vec[vec.size()/2];
    }
  }

  std::cout << sum << std::endl;
  return 0;
}