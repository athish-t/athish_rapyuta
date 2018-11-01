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


int main (int argc, char *argv[]) {

    std::cout << "Planner executable called" << std::endl;
    std::string map_name = "maze.pgm";

    amrita2019::AStarPlanner astar; // construct astar planner.
    amrita2019::DFSPlanner dfs; // construct dfs planner

    astar.initialize(map_name);
    dfs.initialize(map_name);

    /** GET the start and goal from user and print the plan
    astar.makePlan(.....);
    dfs.makePlan (....);*/

    SquareGrid grid = make_diagram1(30,15);
    GridLocation start{1, 4};
    GridLocation goal{25, 10};
    std::map<GridLocation, GridLocation> came_from;
    std::map<GridLocation, double> cost_so_far;

    astar.makePlan(grid, start, goal, came_from, cost_so_far);

    draw_grid(grid, 2, nullptr, &came_from, nullptr);
    std::cout << '\n';
    draw_grid(grid, 3, &cost_so_far, nullptr, nullptr);
    std::cout << '\n';
    std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
    draw_grid(grid, 3, nullptr, nullptr, &path);

    /**
    BONUS POINTS: 
    1. use boost smart pointer
    2. use thread: one thread should plan a path using DFS and the other thread should plan the plan using Astar
    **/

    return 0;
}