#include <map_planner/map_planner.h>
#include <iostream>

int main (int argc, char *argv[]) {

    std::cout << "Planner executable called" << std::endl;
    std::string map_name = "maze.pgm";

    amrita2019::InitPlanner planner; //construct planner to initialize grid from image
    amrita2019::AStarPlanner astar; // construct astar planner.
    amrita2019::DFSPlanner dfs; // construct dfs planner

    SquareGrid grid = planner.initialize(map_name);
    GridLocation start;
    GridLocation goal;
    std::vector<GridLocation> path;

    start:
    //Get start and goal coordinates from the user
    std::cout << "Enter start coordinates: ";
    std::cin >> start.x >> start.y;
    if (grid.notWall(start) == false)
    {
        std::cout << "\nThe location you have entered is an obstacle. Please try again\n";
        goto start; //check if start location is a wall
    }

    goal:
    std::cout << "\nEnter goal coordintes: ";
    std::cin >> goal.x >> goal.y;
    if (grid.notWall(goal) == false)
    {
        std::cout << "\nThe location you have entered is an obstacle. Please try again\n";
        goto goal; //check if goal location is a wall
    }
    std::cout << std::endl;

    //descriptions of all arguments passed are written in map_planner.h 
    astar.makePlan(grid, start, goal, path);
    dfs.makePlan (grid, start, goal, path);

    return 0;
}