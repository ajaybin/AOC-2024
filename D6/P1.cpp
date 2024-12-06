//Up    : (-1, 0) : Right
//Right : ( 0, 1) : Down
//Down  : ( 1, 0) : Left
//Left  : ( 0,-1) : Up
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

int numRows{0};
int numCols{0};
using obs_v = std::map<std::pair<int,int>, bool>;
obs_v obstacles;


bool is_oob(int row, int col) {
    bool oob{false};
    if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
      oob = true;
    }
    return oob;
}
class guard_c {
    private:
        std::pair<int, int> position;
        std::pair<int, int> direction;
        obs_v positions;

    public:
        void set_initial_position(int r, int c) {
            position = std::make_pair(r,c);
            direction = std::make_pair(-1,0);
            positions[position] = true;
        }
        void turn_right() {
            if (direction == std::make_pair(-1,0)) {
                direction = std::make_pair(0,1);
            } else if (direction == std::make_pair(0,1)) {
                direction = std::make_pair(1,0);
            } else if (direction == std::make_pair(1,0)) {
                direction = std::make_pair(0,-1);
            } else if (direction == std::make_pair(0,-1)) {
                direction = std::make_pair(-1,0);
            }
        }
        void step(int& row, int& col) {
            int n_row, n_col;
            n_row = row + direction.first;
            n_col = col + direction.second;
            if (obstacles.contains(std::make_pair(n_row, n_col))) {
                turn_right();
            } else {
                row = n_row;
                col = n_col;
            }
        }
        int move() {
            while (!is_oob(position.first, position.second)) {
                positions[position] = true;
                step(position.first, position.second);
            }
            return positions.size();
        }
};

int main() {
  std::ifstream ifile("input.txt");
  std::string line;
  guard_c guard;

  while(std::getline(ifile, line)) {
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == '#') {
            obstacles[std::make_pair(numRows,i)] = true;
        }
        if (line[i] == '^') {
            guard.set_initial_position(numRows, i);
        }
    }
    ++numRows;
  }
  numCols = line.size();
  ifile.close();
  std::cout << guard.move() << std::endl;

  return 0;
}