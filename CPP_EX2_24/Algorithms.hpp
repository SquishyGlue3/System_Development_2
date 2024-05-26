// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <algorithm>
#include <climits>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "Graph.hpp"

namespace ariel
{
    class Algorithms
    {
    public:
        static void DFS(size_t node, Graph &g, std::vector<bool> &visited);
        static bool isConnected(Graph &g);
        static string bellmanFord(Graph &g, vector<int> &parent);
        static string shortestPath(Graph &g, size_t start, size_t end);
        static bool isContainsCycle(Graph &g);
        static string isBipartite(Graph &g);
        static string negativeCycle(Graph &g);
    };
}
#endif // ALGORITHMS_HPP
