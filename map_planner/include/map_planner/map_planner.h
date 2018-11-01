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
      template<typename Location, typename Graph>
      bool makePlan(Graph graph, Location start, Location goal, std::map<Location, Location>& came_from, std::map<Location, double>& cost_so_far)  = 0;

      /**
       * @brief  Initialization function for the BaseGlobalPlanner
       * @param  path of the bitmap
       * @param  TODO: Define a new data structure to convert the bitmap image to YOUR data structure
       */
      virtual void initialize(std::string map_name /*,*DEFINE YOUR DATASTRUCTURE e.g GRAPH*/);

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
        template<typename Location, typename Graph>
        bool makePlan(Graph graph, Location start, Location goal, std::map<Location, Location>& came_from, std::map<Location, double>& cost_so_far); 
        ~DFSPlanner(){};
  };

  class AStarPlanner: public Planner {
      public:
        AStarPlanner(){};
        template<typename Location, typename Graph>
        bool makePlan(Graph graph, Location start, Location goal, std::map<Location, Location>& came_from, std::map<Location, double>& cost_so_far); 
        ~AStarPlanner(){}
  };

};  // namespace nav_core

#endif  // MAP_PLANNER_MAP_PLANNER_H