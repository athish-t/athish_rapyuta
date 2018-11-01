#include <map_planner/map_planner.h>
#include <a/a.h>
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

using namespace amrita2019;

void Planner::initialize(std::string map_name /*,DEFINE YOUR DATASTRUCTURE e.g GRAPH*/) {
    /**
    get the map_name, for non-ROS users, get the path directly and open the file in C++

    std::string map_path = ros::package::getPath("map_planner") + "/data" + "/" + map_name;
    PLEASE FILL IN YOUR LOGIC TO OPEN THIS FILE AND CONVERT TO THE DATASTRUCTURE OF YOUR CHOICE.
    **/
}

bool DFSPlanner::makePlan(SquareGrid graph, GridLocation start, GridLocation goal, std::map<GridLocation, GridLocation>& came_from, std::map<GridLocation, double>& cost_so_far) 
{
    std::cout << "Yet to be implemented" << std::endl;
    return false;
}

bool AStarPlanner::makePlan(SquareGrid graph, GridLocation start, GridLocation goal, std::map<GridLocation,GridLocation>& came_from, std::map<GridLocation, double>& cost_so_far) 
{
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
    return false;
}