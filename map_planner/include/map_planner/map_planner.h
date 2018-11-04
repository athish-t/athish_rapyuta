#ifndef MAP_PLANNER_MAP_PLANNER_H
#define MAP_PLANNER_MAP_PLANNER_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <set>
#include <array>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>

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

double heuristic(GridLocation a, GridLocation b);

bool operator == (GridLocation a, GridLocation b);
bool operator != (GridLocation a, GridLocation b);
bool operator < (GridLocation a, GridLocation b);
std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc);

void add_Wall(SquareGrid& grid, int x, int y);
SquareGrid initializeGrid(int width, int height);


void draw_grid(const SquareGrid& graph, int field_width,
               std::map<GridLocation, double>* distances=nullptr,
               std::map<GridLocation, GridLocation>* point_to=nullptr,
               std::vector<GridLocation>* path=nullptr);


template<typename T, typename priority_t>
struct PriorityQueue 
{
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue <PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

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

void reconstruct_path(GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation> came_from);

namespace amrita2019 {

  /**
   * @class Planner
   * @brief Provides an interface for global planners used in navigation. All global planners written as plugins for the navigation stack must adhere to this interface.
   */
  class Planner{
    public:
      /**
       * @brief computes a plan given the start and end goal.
       * @param start start GridLocation of the robot
       * @param goal goal that needs to be reached by the robot
       * @param plan YOUR SOLUTION (NOTE: IT IS PASSED BY REFERENCE!)
       * @return PLEASE RETURN TRUE IF YOUR ALGORITHM WAS ABLE TO COMPUTE THE PLAN IN THE INHERTIED CLASS
       */
      virtual bool makePlan(SquareGrid graph, GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation>& came_from, std::map<GridLocation, double>& cost_so_far) = 0;

      /**
       * @brief  Initialization function for the BaseGlobalPlanner
       * @param  path of the bitmap
       * @param  TODO: Define a new data structure to convert the bitmap image to YOUR data structure
       */
      virtual void initialize(std::string map_path ,SquareGrid& grid);

      /**
       * @brief  Virtual destructor
       */
      virtual ~Planner(){}

    protected:
      Planner(){}
  };

  class DFSPlanner: public Planner {
      public:
        DFSPlanner(){};
        bool makePlan(SquareGrid graph, GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation>& came_from, std::map<GridLocation, double>& cost_so_far); 
        ~DFSPlanner(){};
  };

  class AStarPlanner: public Planner {
      public:
        AStarPlanner(){};
        bool makePlan(SquareGrid graph, GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation>& came_from, std::map<GridLocation, double>& cost_so_far); 
        ~AStarPlanner(){}
  };

};  // namespace nav_core



#endif  // MAP_PLANNER_MAP_PLANNER_H