#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using myWheel = std::vector<std::string>;

int numCols;
int numRows;

bool validate_index(int row, int col) {
  bool is_valid = true;
  if (row < 0 || row >= numRows) is_valid = false;
  if (col < 0 || col >= numCols) is_valid = false;
  return is_valid;
}
// (row i, col j) index = i*numCols + j      
// E  : (i,j) (i  ,j+1) (i  ,j+2) (i  ,j+3) 
// SE : (i,j) (i+1,j+1) (i+2,j+2) (i+3,j+3)
// S  : (i,j) (i+1,j  ) (i+2,j  ) (i+3,j  )
// SW : (i,j) (i+1,j-1) (i+2,j-2) (i+3,j-3)
// W  : (i,j) (i  ,j-1) (i  ,j-2) (i  ,j-3)
// NW : (i,j) (i-1,j-1) (i-2,j-2) (i-3,j-3)
// N  : (i,j) (i-1,j  ) (i-2,j  ) (i-3,j  )
// NE : (i,j) (i-1,j+1) (i-2,j+2) (i-3,j+3)
// C  : center dot

void generate_wheel(int row, int col, myWheel& wheel, std::vector<char>& v) {
    int idx{0};

    for (int r_changer = -1; r_changer < 2; ++r_changer) {
        for (int c_changer = -1; c_changer < 2; ++c_changer) {
            std::string axis;
            axis.push_back('X');
            for (int i = 1; i < 4; ++i) {
                int r = row + i*r_changer;
                int c = col + i*c_changer;
                if (validate_index(r, c)) {
                    idx = numCols*r + c;
                    axis.push_back(v[idx]);
                } else {
                    axis.push_back('.');
                }
            }
            wheel.push_back(axis);
        }
    }
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
        if (v[index] == 'X') {
          generate_wheel(row, col, wheel, v);
          for (auto axis : wheel) {
              if (axis == "XMAS") {
                  ++sum;
              }
          }            
        }
    }
  }
  std::cout << sum;

  return 0;
}