#ifndef GRID_GRID_H
#define GRID_GRID_H

#include <map_planner/map_planner.h>
#include <iostream>
#include <map>
#include <set>
#include <array>
#include <queue>

//Location of robot in the grid in pixels. 
//Using only 2-D cartesian co-ordinates with first row as x-axis
struct GridLocation {
  int x, y;
};

//The structure to store the image as a graph. 
struct SquareGrid {
  //array to define the directions of traversal. 
  std::array<GridLocation, 8> DIRS =
  {
      GridLocation{1, 0}, GridLocation{0, -1}, GridLocation{-1, 0}, GridLocation{0, 1}, GridLocation{1, 1}, GridLocation{-1, 1}, GridLocation{-1, -1}, GridLocation{1, -1}
  };

  int width, height;
  std::set<GridLocation> walls;

  SquareGrid(int width_, int height_)
     : width(width_), height(height_) {}

  bool in_bounds(GridLocation id) const; //check if location is inside the dimensions of the grid

  bool passable(GridLocation id) const; //used by neighbors() function to check for walls

  std::vector<GridLocation> neighbors(GridLocation id) const; //return all neighbouring nodes, by checking for walls

};

inline extern double heuristic(GridLocation a, GridLocation b); // heuristic for A* algorithm

inline extern void add_Wall(SquareGrid& grid, int x, int y);

/* Function reconstructs path between start and goal, using the came_from map created in the makePlan algorithm
 * @param start: start GridLocation of the robot
 * @param goal: goal that needs to be reached by the robot
 * @param came_from: created in algorithm logic to keep track of movements
 * @return path: THE SOLUTION of algorithm
*/
std::vector<GridLocation> reconstruct_path(GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation> came_from);

//overloading operators to make comparing grid locations easy
bool operator == (GridLocation a, GridLocation b);
bool operator != (GridLocation a, GridLocation b);
bool operator < (GridLocation a, GridLocation b);
std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc);

#endif  // GRID_GRID_H