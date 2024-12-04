#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using myWheel = std::vector<std::string>;

int numCols;
int numRows;

bool validate_index(const int& row, const int& col) {
  bool is_valid = true;
  if (row < 0 || row >= numRows) is_valid = false;
  if (col < 0 || col >= numCols) is_valid = false;
  return is_valid;
}
void generate_axis(const int& row, const int& col, std::string& axis, std::vector<char>& v) {
    int idx;
    if (validate_index(row, col)) {
      idx = numCols*row + col;
      axis.push_back(v[idx]);
    }  else {
      axis.push_back('.');
    }  
}

void generate_wheel(int row, int col, myWheel& wheel, std::vector<char>& v) {
    int r;
    int c;
    std::string axis;

    r = row - 1;
    c = col - 1;
    generate_axis(r,c,axis,v);
    r = row;
    c = col;
    generate_axis(r,c,axis,v);
    r = row + 1;
    c = col + 1;
    generate_axis(r,c,axis,v);
    wheel.push_back(axis);

    axis = "";
    r = row - 1;
    c = col + 1;
    generate_axis(r,c,axis,v);
    r = row;
    c = col;
    generate_axis(r,c,axis,v);
    r = row + 1;
    c = col - 1;
    generate_axis(r,c,axis,v);
    wheel.push_back(axis);    
}

int main() {
  std::ifstream ifile("input.txt");
  std::string line;
  std::vector<char> v;


  while(std::getline(ifile, line)) {
    for(char& c : line) {
      v.push_back(c);
    }
  }
  numCols = line.size();
  numRows = v.size()/numCols;

  int sum{0};
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
        myWheel wheel;
        int index = (numCols * row) + col;
        if (v[index] == 'A') {
          generate_wheel(row, col, wheel, v);
          bool count_this{true};
          for (auto axis : wheel) {
              if (axis != "MAS" && axis != "SAM") {
                  count_this = false;
              }
          }
          if (count_this) {
            ++sum;
          }
        }
    }
  }
  std::cout << sum;

  return 0;
}