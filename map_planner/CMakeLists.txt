cmake_minimum_required(VERSION 2.8.3)
project(map_planner)

add_compile_options(-std=c++11)

###########
## Build ##
###########

include_directories(
  include/map_planner
  include/a
  ${catkin_INCLUDE_DIRS}
)

add_library(map_planner
   src/map_planner.cpp
   src/a.cpp
)

add_executable(map_planner_node src/map_planner_node.cpp)

target_link_libraries(map_planner_node
   map_planner
)