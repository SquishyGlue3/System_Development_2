<!-- Rotem Melamed
209039072
rotem.melamed25@gmail.com -->

Graph Algorithms Implementation

Overview
This project implements couple of algorithms on graphs such as, 1 -checking if the graph is connected, finding negative cycles, finding the shortest path and checking if the graph is bipartite.
I have divided the project to 3 main file : 1 - Graph.cpp, 2 - Algorithms.cpp, 3 - Test.cpp.

File Structure
1. Graph.hpp
This is simple header file the declare the Graph class and methods such as loading graph from a matrix, printing it and needed methods for the project
2. Algorithms.hpp
this is the same idea as the Graph.hpp but this is mainly for algoriths to be done *on* the graph 

3. Graph.cpp
This file provides the implementation of the Graph class declared in Graph.hpp. The key methods implemented are:

loadGraph(): Loads the graph from an adjacency matrix.
printGraph(): Prints the graph's adjacency matrix.
isEdge(): Checks if there is an edge between two vertices.
getEdgeValue(): Returns the value of the edge between two vertices.
getVerticesNum(): Returns the number of vertices in the graph.
isDirected(): Checks if the graph is directed.
isWeighted(): Checks if the graph is weighted.
getNeighbours(): Returns the neighbors of a vertex.
getRow(): Returns a specific row of the adjacency matrix.
getCol(): Returns a specific column of the adjacency matrix.
getTranspose(): Returns the transpose of the graph.

4. Algorithms.cpp
This file implements various graph algorithms eclared in Algorithms.hpp:

DFS(): Performs a depth-first search.
isConnected(): Checks if the graph is connected.
bellmanFord(): Uses the Bellman-Ford algorithm to detect negative cycles.
shortestPath(): Finds the shortest path between two vertices.
isContainsCycle(): Checks if the graph contains any cycle.
isBipartite(): Determines if the graph is bipartite.
negativeCycle(): Checks for the presence of negative cycles and returns the path if found.

5. Test.cpp
This file contains test cases to make sure the implemented algorithms do their job. It has 2 test cases group, testGraph, testing the graph creation and test Algorithms wich test the algorithms functions

6. Makefile
This file is used for compiling the code. It includes targets for compiling the main test program (test), running the tests, formatting the code with clang-format, and cleaning up generated files.

How to Use The code
Prerequisites
A C++ compiler (e.g., g++)
Make utility (if using the provided Makefile)

Compilation
To compile the code, navigate to the directory containing the files and run:
make
This will compile the source files and produce an executable named test.

Running Tests
To run the tests, execute the following command:
make run
This will run the test executable and output the results of the various test cases.

Code Formatting
To format the code using clang-format, run:
make tidy

Cleaning Up
To remove the compiled files and clean up the directory, run:
make clean
Detailed description of the Algorithms
1. Depth-First Search (DFS)
The DFS function performs a depth-first search on the graph starting from a given node. It is used in several other algorithms.

2. isConnected
The isConnected function checks if the graph is connected by performing DFS starting from each vertex and checking if all vertices are visited.

3. Bellman-Ford Algorithm
The bellmanFord function uses the Bellman-Ford algorithm to detect the presence of negative cycles in the graph. It updates the parent array to reconstruct paths and detect cycles.

4. Shortest Path
The shortestPath function finds the shortest path between two vertices. It uses BFS for unweighted graphs and the Bellman-Ford algorithm for weighted graphs.

5. isContainsCycle
The isContainsCycle function checks if the graph contains any cycle using BFS or DFS depending on whether the graph is directed or undirected.

6. isBipartite
The isBipartite function determines if the graph is bipartite by attempting to color the graph using two colors. If a conflict is found, the graph is not bipartite.

7. negativeCycle
The negativeCycle function checks for the presence of negative cycles in the graph using the Bellman-Ford algorithm. If a negative cycle is found, it returns the path of the cycle.


Conclusion
This project provides a comprehensive implementation of various graph algorithms. The code is modular, and the provided Makefile makes it easy to compile, run, and manage the project.

