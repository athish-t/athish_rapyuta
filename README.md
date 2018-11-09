# A* and DFS path planning algorithms
2019 campus placement programming round

## To clone this repository, use:
        git clone -b master https://github.com/athish-thirumal/athish_rapyuta.git
        
## Setup and running
1. Install cmake, Visual Studio
2. Navigate to map_planner directory. Then create build files in 'build' directory
```
mkdir build
cd build
cmake -G "Visual Studio 15 2017" ..
```
3. To compile from command prompt:
```
cmake --build .
```
4. To run .exe from command prompt
```
cd Debug
map_planner_node.exe
```
## Brief outline of program flow
Get start and goal coordinates in pixels from user --> Read image from /data folder and convert pixels to nodes of a graph --> Call A* planner function, print planned path to console out --> Call DFS planner function, print planned path to console out --> End

## Reference material 
https://www.redblobgames.com/pathfinding/a-star/introduction.html

Most of the knowledge required for programming this task was obtained from the above website. It contains interactive tools to understand how A* algorithm works. The author has also provided a basic template of code snippets to start implementing the algorithm in our own project, and the program I have written is inspired from this.

## Some variables used in the code


## Overview of algorithms used
### DFS
Depth First Search is a classic traversal method for graphs. It uses a stack to keep track of the visited nodes. It traverses throughout the depth of an adjacent node until a dead-end is reached, pushing each visited node into the stack. Once a dead-end is reached, it goes to the node in the stack that has unvisited neighbours.

DFS is not a commonly used algorithm for shortest path planning, as opposed to Breadth First Search, as it tends to expore the graph unevenly, and thus may take longer to reach the goal. It may even miss the goal when it's right next to the current visited node, since it only follows the stack to traverse. BFS on the other hand, searches the graph in a uniform fashion from the start node, and thus can reach the goal quicker.

### A*
A* is a very commonly used for shortest path planning. Unlike BFS and DFS that searches the graph in all directions, A* tends to search in a more efficient manner. It used a priority queue to keep track of the visited nodes, where the priority is the sum of distance traversed so far and the distance to goal. This is different from Dijkstra's algorithm in the fact that Dijkstra's uses only the distance travelled so far, but A* also factors in the distance to goal. The node with the highest priority is visited first.

## Future work
1. Implement multithreading to run the two algorithms in two threads
        I tried this, but encountered some problem with sharing variables so the final path was not correct. So I deleted all changes I made completely. However, I missed adding the changes to git, so am not able to retrieve them for documentation
2. Use smart pointers
        Initial study was done, but not tried yet.
        




