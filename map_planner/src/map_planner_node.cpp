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
#include <fstream>


int main (int argc, char *argv[]) {

    std::cout << "Planner executable called" << std::endl;
    std::string map_path = "C:/Users/Athish/Downloads/Rapyuta/athish_rapyuta/map_planner/data/maze.pgm";

    amrita2019::AStarPlanner astar; // construct astar planner.
    amrita2019::DFSPlanner dfs; // construct dfs planner

    SquareGrid grid(110,110);
    GridLocation start;
    GridLocation goal;
    std::map<GridLocation, GridLocation> came_from;
    std::map<GridLocation, double> cost_so_far;

    std::cout << "Enter start coordinates:\n";
    std::cin >> start.x >> start.y;
    std::cout << "\nEnter goal coordintes:";
    std::cin >> goal.x >> goal.y;

    astar.initialize(map_path, grid);
    dfs.initialize(map_path, grid);

    /** GET the start and goal from user and print the plan
    dfs.makePlan (....);*/

    astar.makePlan(grid, start, goal, came_from, cost_so_far);

    /*draw_grid(grid, 2, nullptr, &came_from, nullptr);
    std::cout << '\n';
    draw_grid(grid, 3, &cost_so_far, nullptr, nullptr);
    std::cout << '\n';*/
    std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
    //draw_grid(grid, 3, nullptr, nullptr, &path);
    std::cout << "\n";
    for(int i=0; i<path.size(); ++i)
        std::cout << path[i] << ' ';

    /**
    BONUS POINTS: 
    1. use boost smart pointer
    2. use thread: one thread should plan a path using DFS and the other thread should plan the plan using Astar
    **/

    return 0;
}