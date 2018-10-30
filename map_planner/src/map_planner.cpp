#include <map_planner/map_planner.h>

using namespace amrita2019;

void Planner::initialize(std::string map_name /*,DEFINE YOUR DATASTRUCTURE e.g GRAPH*/) {
    /**
    get the map_name, for non-ROS users, get the path directly and open the file in C++

    std::string map_path = ros::package::getPath("map_planner") + "/data" + "/" + map_name;
    PLEASE FILL IN YOUR LOGIC TO OPEN THIS FILE AND CONVERT TO THE DATASTRUCTURE OF YOUR CHOICE
    **/
}

bool DFSPlanner::makePlan(const Pose& start, const Pose& goal, std::vector<Pose>& plan) {
    std::cout << "Yet to be implemented" << std::endl;
    return false;
}

bool AStarPlanner::makePlan(const Pose& start, const Pose& goal, std::vector<Pose>& plan) {
    std::cout << "Yet to be implemented" << std::endl;
    return false;
}