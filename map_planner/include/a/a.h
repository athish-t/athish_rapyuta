#ifndef MAP_PLANNER_A_H
#define MAP_PLANNER_A_H

#include <map_planner/map_planner.h> //ddc
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



struct GridLocation {
  int x, y;
};

struct SquareGrid {

  std::array<GridLocation, 8> SquareGrid::DIRS =
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

bool operator == (GridLocation a, GridLocation b);
bool operator != (GridLocation a, GridLocation b);
bool operator < (GridLocation a, GridLocation b);
std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc);

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2);
SquareGrid make_diagram1(int width, int height);

template<class Graph>
void draw_grid(const Graph& graph, int field_width,
               std::map<GridLocation, double>* distances=nullptr,
               std::map<GridLocation, GridLocation>* point_to=nullptr,
               std::vector<GridLocation>* path=nullptr);


template<typename T, typename priority_t>
struct PriorityQueue {
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue<PQElement, std::vector<PQElement>,
                 std::greater<PQElement>> elements;

  inline bool empty() const {
     return elements.empty();
  }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};

template<typename Location>
std::vector<Location> reconstruct_path(Location start, Location goal, std::map<Location, Location> came_from);

inline double heuristic(GridLocation a, GridLocation b);

#endif