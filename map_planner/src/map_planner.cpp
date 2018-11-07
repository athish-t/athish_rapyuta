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

using namespace amrita2019;

SquareGrid InitPlanner::initialize(std::string map_path) 
{
	static int row = 0, col = 0, numrows , numcols ;
	unsigned char ch;
    std::ifstream infile;
    infile.open(map_path, std::ios::binary);  
    std::string inputLine = "";
    for(int i=0; i<4; i++)
    {
        if (i==2){
            infile >> numcols;
            infile >> numrows;
            getline(infile,inputLine);
        }
        else{
            getline(infile,inputLine);
        }
    }
    SquareGrid grid(numcols,numrows);
    for(row = 0; row < numrows; row++)
    {
    	for(col = 0; col < numcols ;col++)
    	{
        	infile >> ch;
        	if ((int)ch <250)
        	{
        		grid.walls.insert(GridLocation{col, row});
        	}
        	//std::cout<< (int)ch;
      	}
      	//cout<<endl;
    }
    infile.close();
    return grid;
}

bool DFSPlanner::makePlan(SquareGrid graph, GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation>& came_from, std::map<GridLocation, double>& cost_so_far) 
{
    came_from.clear();
    cost_so_far.clear();
    std::stack<GridLocation> frontier;
    frontier.push(start);

    came_from[start] = start;

    while (!frontier.empty()) 
    {
          GridLocation current = frontier.top();
          frontier.pop();

          if (current == goal) 
          {
            break;
          }
        
          for (GridLocation next : graph.neighbors(current)) 
          {
            if (came_from.find(next) == came_from.end()) 
            {
                frontier.push(next);
                came_from[next] = current;
            }
          }
    }
    return false;
}

bool AStarPlanner::makePlan(SquareGrid graph, GridLocation start, GridLocation goal, std::map<GridLocation,GridLocation>& came_from, std::map<GridLocation, double>& cost_so_far) 
{
    came_from.clear();
    cost_so_far.clear();
    PriorityQueue<GridLocation, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;
	  
	while (!frontier.empty()) 
	{
		GridLocation current = frontier.get();

	    if (current == goal) 
	    {
	      break;
	    }

	    for (GridLocation next : graph.neighbors(current)) 
	    {
		    double new_cost = cost_so_far[current];// + graph.cost(current, next);
		    if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) 
		    {
		      cost_so_far[next] = new_cost;
		      double priority = new_cost + heuristic(next, goal);
		      frontier.put(next, priority);
		      came_from[next] = current;
		    }
	    }
	}
    return true;
}

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

double heuristic(GridLocation a, GridLocation b) 
{
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void draw_grid(const SquareGrid& graph, int field_width,
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

void add_Wall(SquareGrid& grid, int x, int y) {
      grid.walls.insert(GridLocation{x, y});
}
/*
SquareGrid initializeGrid(int width, int height) {
  SquareGrid grid(width, height);
  add_rect(grid, 3, 3, 5, 12);
  add_rect(grid, 13, 4, 15, 15);
  add_rect(grid, 21, 0, 23, 7);
  add_rect(grid, 23, 5, 26, 7);
  return grid;
}*/



void reconstruct_path(GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation> came_from) 
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
}