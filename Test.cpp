// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <cassert> // Include for assertions
#include <iostream>
#include <vector>
using namespace std;

// Function to test loading and printing a graph
void testGraph(vector<vector<int>> &matrix) {
  Graph graph;
  try {
    graph.loadGraph(matrix);
    cout << "Loaded Graph:" << endl;
    graph.printGraph();
    cout << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
}

// Function to test algorithms on a graph
void testAlgorithms(vector<vector<int>> &matrix, bool isConnectedExpected,
                    string isBipartiteExpected,
                    string hasNegativeCycleExpected) {
  Graph graph;
  try {
    graph.loadGraph(matrix);
    cout << "Testing Algorithms:" << endl;
    cout << "Is connected: " << isConnected(graph) << endl;
    cout << "Is connected: " << isConnectedExpected << endl;
    assert(isConnected(graph) == isConnectedExpected);
    assert(isBipartite(graph) == isBipartiteExpected);
    cout << negativeCycle(graph) << endl;
    cout << hasNegativeCycleExpected << endl;
    assert(negativeCycle(graph) == hasNegativeCycleExpected);
    cout << "All algorithm tests passed!" << endl;
  } catch (const invalid_argument &e) {
    cerr << "Error: " << e.what() << endl;
  }
}

int main() {
  // Test graph 1
  cout << "Graph 1:\n";
  vector<vector<int>> matrix1 = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
  testGraph(matrix1);
  testAlgorithms(matrix1, true, "The graph is bipartite: A={0, 2}, B={1}.",
                 "The graph does not contain any negative cycle");

  // Test graph 2
  cout << "\nGraph 2:\n";
  vector<vector<int>> matrix2 = {{0, 1, 1, 0, 0},
                                 {1, 0, 1, 0, 0},
                                 {1, 1, 0, 1, 0},
                                 {0, 0, 1, 0, 0},
                                 {0, 0, 0, 0, 0}};
  testGraph(matrix2);
  testAlgorithms(matrix2, true, "The graph is not bipartite",
                 "The graph does not contain any negative cycle");

  // Test graph 3
  cout << "\nGraph 3:\n";
  vector<vector<int>> matrix3 = {
      {0, 1, 2, 0}, {1, 0, 3, 0}, {2, 3, 0, 4}, {0, 0, 4, 0}, {0, 0, 0, 5}};
  testGraph(matrix3);
  testAlgorithms(matrix3, true,
                 "The graph is bipartite: A={0, 1, 2, 3}, B={4}.",
                 "The graph does not contain any negative cycles");

  // Test graph 4
  cout << "\nGraph 4:\n";
  vector<vector<int>> matrix4 = {
      {0, 1, 2, 0, 5}, {1, 0, 3, 0}, {2, 3, 0, 4}, {0, 0, 4, 0}};
  testGraph(matrix4);
  testAlgorithms(matrix4, false, "The graph is not bipartite",
                 "The graph does not contain any negative cycles");

  // Test graph 5
  cout << "\nGraph 5:\n";
  vector<vector<int>> matrix5 = {{0, 1, 1, 1, 1},
                                 {1, 0, 1, 1, 1},
                                 {1, 1, 0, 1, 1},
                                 {1, 1, 1, 0, 1},
                                 {1, 1, 1, 1, 0}};
  testGraph(matrix5);
  testAlgorithms(matrix5, true, "The graph is not bipartite",
                 "The graph does not contain any negative cycle");

  // Test graph 6 with negative cycles
  cout << "\nGraph 6:\n";
  vector<vector<int>> matrix6 = {{0, -1, -1}, {-1, 0, -1}, {-1, -1, 0}};
  testGraph(matrix6);
  testAlgorithms(matrix6, true, "The graph is not bipartite",
                 "The graph contains a negative cycle: 2->1->2");
  return 0;
}
