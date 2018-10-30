#ifndef MAP_PLANNER_MAP_PLANNER_H
#define MAP_PLANNER_MAP_PLANNER_H

#include <iostream>
#include <string>
#include <vector>


namespace amrita2019 {

  struct Pose {
    float x;
    float y;
    float theta;
  };

  /**
   * @class Planner
   * @brief Provides an interface for global planners used in navigation. All global planners written as plugins for the navigation stack must adhere to this interface.
   */
  class Planner{
    public:
      /**
       * @brief computes a plan given the start and end goal
       * @param start start pose of the robot
       * @param goal goal that needs to be reached by the robot
       * @param plan YOUR SOLUTION (NOTE: IT IS PASSED BY REFERENCE!)
       * @return PLEASE RETURN TRUE IF YOUR ALGORITHM WAS ABLE TO COMPUTE THE PLAN IN THE INHERTIED CLASS
       */
      virtual bool makePlan(const Pose& start, const Pose& goal, std::vector<Pose>& plan) = 0;

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
        bool makePlan(const Pose& start, const Pose& goal, std::vector<Pose>& plan);
        ~DFSPlanner(){};
  };

  class AStarPlanner: public Planner {
      public:
        AStarPlanner(){};
        bool makePlan(const Pose& start, const Pose& goal, std::vector<Pose>& plan);
        ~AStarPlanner(){}
  };

};  // namespace nav_core

#endif  // MAP_PLANNER_MAP_PLANNER_H