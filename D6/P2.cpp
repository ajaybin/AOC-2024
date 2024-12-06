//Up    : (-1, 0) : Right
//Right : ( 0, 1) : Down
//Down  : ( 1, 0) : Left
//Left  : ( 0,-1) : Up
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <utility>

int numRows{0};
int numCols{0};
using obs_v = std::set<std::pair<int,int>>;
obs_v obstacles;
obs_v positions;
bool added_obstacle;
std::pair<int, int> obstacle;

bool is_oob(int row, int col) {
    bool oob{false};
    if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
      oob = true;
    }
    return oob;
}
void place_obstacle(int row, int col) {
    std::pair<int, int> position = std::make_pair(row,col);
    added_obstacle = false;
    if (!obstacles.contains(position)) {
        obstacles.insert(position);
        added_obstacle = true;
    }
}
void remove_obstacle(int row, int col) {
    if (added_obstacle) {
        obstacles.erase(std::make_pair(row, col));
    }
}
class guard_c {
    private:
        std::pair<int, int> position;
        std::pair<int, int> direction;
        std::map<std::pair<int,int>,std::vector<std::pair<int,int>>> history;
        bool check_history;
    public:
        void set_initial_position(int r, int c) {
            position = std::make_pair(r,c);
            direction = std::make_pair(-1,0);
            positions.insert(position);
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
        bool step(int& row, int& col, bool& is_looping) {
            int n_row, n_col;
            bool hit_obstacle{false};
            n_row = row + direction.first;
            n_col = col + direction.second;
            if (obstacles.contains(std::make_pair(n_row, n_col))) {
                turn_right();
                hit_obstacle = true;
                if (obstacle.first == n_row && obstacle.second == n_col) {
                    check_history = true;
                }
                if (check_history) {
                    std::pair<int, int> t;
                    t.first = row;
                    t.second = col;
                    if(history.contains(t) && std::find(history[t].cbegin(),history[t].cend(),direction)!=history[t].cend()) {
                        is_looping = true;
                    }
                    history[t].push_back(direction);
                }
            } else {
                row = n_row;
                col = n_col;
            }
            return hit_obstacle;
        }
        void move() {
            while (!is_oob(position.first, position.second)) {
                bool is_looping;
                positions.insert(position);
                step(position.first, position.second, is_looping);
            }
        }
        bool move_and_check() {
            bool is_looping{false};
            check_history = false;
            history.clear();
            while (!is_oob(position.first, position.second) && !is_looping) {
                step(position.first, position.second, is_looping);
            }           
            return is_looping;
        }
};

int main() {
  std::ifstream ifile("input.txt");
  std::string line;
  guard_c guard;
  std::pair<int, int> init;

  while(std::getline(ifile, line)) {
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == '#') {
            place_obstacle(numRows, i);
        }
        if (line[i] == '^') {
            init.first = numRows;
            init.second = i;
            guard.set_initial_position(numRows, i);
        }
    }
    ++numRows;
  }
  numCols = line.size();
  ifile.close();

  guard.move();

  int num_loops{0};
  int size = positions.size();
  int count{0};
  for (auto i : positions) {
    if (i == init) continue;
    guard.set_initial_position(init.first, init.second);
    place_obstacle(i.first, i.second);
    if (added_obstacle) {
        obstacle = i;
        if (guard.move_and_check()) {
            ++num_loops;
        }
        remove_obstacle(i.first, i.second);
    }
    std::cout << "loop " << ++count << " of " << size << std::endl;;
  }
  std::cout << num_loops << std::endl;
  return 0;
}