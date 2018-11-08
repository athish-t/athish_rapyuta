#ifndef GRID_GRID_H
#define GRID_GRID_H

#include <map_planner/map_planner.h>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>

struct GridLocation {
  int x, y;
};

struct SquareGrid {

  std::array<GridLocation, 8> DIRS =
  {
      GridLocation{1, 0}, GridLocation{0, -1}, GridLocation{-1, 0}, GridLocation{0, 1}, GridLocation{1, 1}, GridLocation{-1, 1}, GridLocation{-1, -1}, GridLocation{1, -1}
  };

  int width, height;
  std::set<GridLocation> walls;

  SquareGrid(int width_, int height_)
     : width(width_), height(height_) {}

  bool in_bounds(GridLocation id) const; 

  bool passable(GridLocation id) const;

  std::vector<GridLocation> neighbors(GridLocation id) const;
};

inline extern double heuristic(GridLocation a, GridLocation b);

bool operator == (GridLocation a, GridLocation b);
bool operator != (GridLocation a, GridLocation b);
bool operator < (GridLocation a, GridLocation b);
std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc);

inline extern void add_Wall(SquareGrid& grid, int x, int y);


std::vector<GridLocation> reconstruct_path(GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation> came_from);

#endif  // GRID_GRID_H