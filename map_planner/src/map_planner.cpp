#include <map_planner/map_planner.h>
#include <grid/grid.h>
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

SquareGrid InitPlanner::initialize(std::string map_name) 
{
    std::string map_path = "../../data/" + map_name;
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
        		add_Wall(grid,col,row);
        	}
      	}
    }
    infile.close();
    return grid;
}

bool DFSPlanner::makePlan(SquareGrid graph, GridLocation start, GridLocation goal, std::vector<GridLocation>& path) 
{
    std::map<GridLocation, GridLocation> came_from;
    //implement stack to select neighbours to traverse
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
    std::cout << "\nPath planned using DFS algorithm:\n" ;
    path = reconstruct_path(start, goal, came_from);
    return true;
}

bool AStarPlanner::makePlan(SquareGrid graph, GridLocation start, GridLocation goal, std::vector<GridLocation>& path) 
{
    std::map<GridLocation, GridLocation> came_from;
    std::map<GridLocation, double> cost_so_far;
    //implement priority queue to select neighbour with highest priority
    typedef std::pair<double, GridLocation> PQElement;
    std::priority_queue <PQElement, std::vector<PQElement>, std::greater<PQElement>> frontier;

	frontier.emplace(0, start);
	came_from[start] = start;
	cost_so_far[start] = 0;
	  
	while (!frontier.empty()) 
	{
		GridLocation current = frontier.top().second;
        frontier.pop();

	    if (current == goal) 
	    {
	      break;
	    }

	    for (GridLocation next : graph.neighbors(current)) 
	    {
		    double new_cost = cost_so_far[current];
		    if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) 
		    {
		      cost_so_far[next] = new_cost;
		      double priority = new_cost + heuristic(next, goal);
		      frontier.emplace(priority, next);
		      came_from[next] = current;
		    }
	    }
	}
    std::cout << "\nPath planned using A* algorithm:\n" ;
    path = reconstruct_path(start, goal, came_from);
    return true;
}
