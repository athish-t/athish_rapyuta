#include <map_planner.h>
#include <a.h>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>//dcdc
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <string>

bool SquareGrid::in_bounds(GridLocation id) const 
{
    return 0 <= id.x && id.x < width
        && 0 <= id.y && id.y < height;
}

bool SquareGrid::passable(GridLocation id) const 
{
    return walls.find(id) == walls.end();
}

std::vector<GridLocation> SquareGrid::neighbors(GridLocation id) const
{
	std::vector<GridLocation> results;

	for (GridLocation dir : DIRS) {
	  GridLocation next{id.x + dir.x, id.y + dir.y};
	  if (in_bounds(next) && passable(next)) {
	    results.push_back(next);
	  }
	}

	if ((id.x + id.y) % 2 == 0) {
	  // aesthetic improvement on square grids
	  std::reverse(results.begin(), results.end());
	}

	return results;
}

bool operator == (GridLocation a, GridLocation b) {
  return a.x == b.x && a.y == b.y;
}

bool operator != (GridLocation a, GridLocation b) {
  return !(a == b);
}

bool operator < (GridLocation a, GridLocation b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc) {
  out << '(' << loc.x << ',' << loc.y << ')';
  return out;
}

template<class Graph>
void draw_grid(const Graph& graph, int field_width,
               std::map<GridLocation, double>* distances,
               std::map<GridLocation, GridLocation>* point_to,
               std::vector<GridLocation>* path) {
  for (int y = 0; y != graph.height; ++y) {
    for (int x = 0; x != graph.width; ++x) {
      GridLocation id {x, y};
      std::cout << std::left << std::setw(field_width);
      if (graph.walls.find(id) != graph.walls.end()) {
        std::cout << std::string(field_width, '#');
      } else if (point_to != nullptr && point_to->count(id)) {
        GridLocation next = (*point_to)[id];
        if (next.x == x + 1) { std::cout << "> "; }
        else if (next.x == x - 1) { std::cout << "< "; }
        else if (next.y == y + 1) { std::cout << "v "; }
        else if (next.y == y - 1) { std::cout << "^ "; }
        else { std::cout << "* "; }
      } else if (distances != nullptr && distances->count(id)) {
        std::cout << (*distances)[id];
      } else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
        std::cout << '@';
      } else {
        std::cout << '.';
      }
    }
    std::cout << '\n';
  }
}

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2) {
  for (int x = x1; x < x2; ++x) {
    for (int y = y1; y < y2; ++y) {
      grid.walls.insert(GridLocation{x, y});
    }
  }
}

SquareGrid make_diagram1(int width, int height) {
  SquareGrid grid(width, height);
  add_rect(grid, 3, 3, 5, 12);
  add_rect(grid, 13, 4, 15, 15);
  add_rect(grid, 21, 0, 23, 7);
  add_rect(grid, 23, 5, 26, 7);
  return grid;
}


template<typename Location>
std::vector<Location> reconstruct_path(
   Location start, Location goal,
   std::map<Location, Location> came_from
) {
  std::vector<Location> path;
  Location current = goal;
  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start); // optional
  std::reverse(path.begin(), path.end());
  return path;
}

inline double heuristic(GridLocation a, GridLocation b) 
{
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}