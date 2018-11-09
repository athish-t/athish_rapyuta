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

## Description of some variables, classes and functions used
### Frontier 
In DFS, it is the stack that keeps track of the visited nodes. The stack is what gives the algorithm its 'Depth-First' logic because of its LIFO approach. On the other hand, BFS uses a queue to keep track of the visited nodes.

In A*, the frontier is a priority queue (not FIFO), where the elements are queued according to its priority value. Here we access elements from the priority queue that has the least priority. The priority value here is the sum of distance travelled so far and distance to goal.

### came_from
This is used in both DFS and A* to keep track of which node was visited first before being in the current node. The reconstruct_path() function uses this to return the final path. It is updated for every node after the algorithm decides which node to visit next.
std::map<GridLocation, GridLocation> came_from is a map/dictionary whose mapped value is the previously visited node, and the key value is the current node.

### cost_so_far
Used by the A* algorithm to update the number of nodes it has visited so far. This when added with the distance to goal gives the priority used in this algorithm
std::map<GridLocation, double> cost_so_far is a map whose key value is a grid location, and the mapped value is the distance in nodes from the start

### GridLocation{}
Class that contains x and y coordinates of a particular pixel

### heuristic()
Function to calculate distance from current location in grid to the goal, for use in A* algorithm. Here, the manhattan Distance is calculated.

### reconstructpath(start, goal, came_from)
Function that recieves the start and goal locations and uses the came_from map to construct a path starting from the goal to the start. Then the vector of grid locations is reversed to get the path from start to goal.
It returns std::vector<GridLocation>.

### SquareGrid{}



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
        




