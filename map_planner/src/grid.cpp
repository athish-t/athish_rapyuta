#include <map_planner/map_planner.h>
#include <iomanip>
#include <string>
#include <vector>

//member functions of class SquareGrid
bool SquareGrid::in_bounds(GridLocation id) const 
{
    return 0 <= id.x && id.x < width
        && 0 <= id.y && id.y < height;
}

bool SquareGrid::notWall(GridLocation id) const 
{
    return walls.find(id) == walls.end();
}

std::vector<GridLocation> SquareGrid::neighbors(GridLocation id) const
{
    std::vector<GridLocation> results;

    for (GridLocation dir : DIRS) {
      GridLocation next{id.x + dir.x, id.y + dir.y};
      if (in_bounds(next) && notWall(next)) {
        results.push_back(next);
      }
    }

    if ((id.x + id.y) % 2 == 0) {
      // aesthetic improvement on square grids
      std::reverse(results.begin(), results.end());
    }

    return results;
}

inline extern double heuristic(GridLocation a, GridLocation b) 
{
  return std::abs(a.x - b.x) + std::abs(a.y - b.y); //manhattan distance
}

inline extern void add_Wall(SquareGrid& grid, int x, int y) {
      grid.walls.insert(GridLocation{x, y});
}

std::vector<GridLocation> reconstruct_path(GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation> came_from) 
{
  std::vector<GridLocation> path;
  path.clear();
  GridLocation current = goal;
  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start); // optional
  std::reverse(path.begin(), path.end());
  std::cout << std::endl;
  for(int i=0; i<path.size(); ++i)
        std::cout << path[i] << ' ';
  std::cout << std::endl ;
  return path;
}

void draw_grid(const SquareGrid graph, std::vector<GridLocation> path) 
{
  int field_width = 1;
  for (int y = 0; y != graph.height; ++y) 
  {
    for (int x = 0; x != graph.width; ++x) 
    {
      GridLocation id {x, y};
      std::cout << std::left << std::setw(field_width);
      if (graph.walls.find(id) != graph.walls.end()) 
        std::cout << std::string(field_width, '#'); 
      else if (find(path.begin(), path.end(), id) != path.end()) 
        std::cout << '@';
      else 
        std::cout << '.';
    }
    std::cout << '\n';
  }
}

//overloading operators to make comparing grid locations easy
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