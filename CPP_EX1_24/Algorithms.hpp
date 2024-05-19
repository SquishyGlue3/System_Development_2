// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <iostream>
#include "Graph.hpp"
using namespace std;

void DFS(int node, Graph& g, std::vector<bool>& visited);
bool isConnected(Graph& g);
void bellmanFord(Graph& g, vector<int>& parent);
string shortestPath (Graph& g, int start, int end);
bool isContainsCycle(Graph& g);
string isBipartite(Graph& g);
string negativeCycle(Graph& g);
#endif // ALGORITHMS_HPP
