// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void DFS(std::vector<int>::size_type node, Graph &g, vector<bool> &visited) {
  visited[node] = true;
  for (std::vector<int>::size_type i = 0; i < g.getVerticesNum(); ++i) {
    if (g.isEdge(node, i) && !visited[i]) {
      DFS(i, g, visited);
    }
  }
}

bool isConnected(Graph &g) {
  if (g.getVerticesNum() == 0) {
    return true;
  }

  vector<bool> visited(g.getVerticesNum(), false);

  for (std::vector<int>::size_type i = 0; i < g.getVerticesNum(); ++i) {
    if (!visited[i]) {
      DFS(i, g, visited);
    }
  }

  for (bool v : visited) {
    if (!v) {
      return false;
    }
  }

  return true;
}

void bellmanFord(Graph &g, vector<int> &parent) {
  for (std::vector<int>::size_type i = 0; i < g.getVerticesNum(); i++) {
    parent[i] = -1;
  }
  for (std::vector<int>::size_type i = 0; i < g.getVerticesNum();
       i++) { // using Bellman-Ford algorithm to detect negative cycles starting
              // from each vertex
    vector<int> distance(g.getVerticesNum(), INT_MAX);
    distance[i] = 0;
    parent[i] = 0;

    for (std::vector<int>::size_type l = 0; l < g.getVerticesNum() - 1; l++) {
      for (std::vector<int>::size_type j = 0; j < g.getVerticesNum(); j++) {
        for (std::vector<int>::size_type k = 0; k < g.getVerticesNum(); k++) {
          if (g.isEdge(j, k) && distance[j] != INT_MAX &&
              distance[j] + g.getEdgeValue(j, k) < distance[k]) {
            distance[k] = distance[j] + g.getEdgeValue(j, k);
            parent[k] = j;
          }
        }
      }
    }

    string negativeCyclePath;
    for (std::vector<int>::size_type j = 0; j < g.getVerticesNum(); j++) {
      for (std::vector<int>::size_type k = 0; k < g.getVerticesNum(); k++) {
        if (g.isEdge(j, k) && distance[j] != INT_MAX &&
            distance[j] + g.getEdgeValue(j, k) < distance[k]) {
          std::vector<int>::size_type node = k;
          for (std::vector<int>::size_type i = 0; i < g.getVerticesNum(); i++) {
            node = parent[node];
          }
          std::vector<int>::size_type start = node;
          negativeCyclePath = to_string(start);
          for (std::vector<int>::size_type i = parent[start]; i != start;
               i = parent[i]) {
            negativeCyclePath += "->" + to_string(i);
          }
          negativeCyclePath += "->" + to_string(start);
          throw runtime_error("The graph contains a negative cycle: " +
                              negativeCyclePath);
        }
      }
    }
  }
}

string shortestPath(Graph &g, std::vector<int>::size_type start,
                    std::vector<int>::size_type end) {
  if (start == end) {
    return to_string(start);
  }
  if (g.getVerticesNum() == 0) {
    return "There are no vertices in the graph.";
  }

  vector<int> parent(g.getVerticesNum(), -1);
  if (!g.isWeighted()) {
    queue<int> q;
    q.push(start);
    parent[start] = start;

    while (!q.empty()) {
      std::vector<int>::size_type node = q.front();
      q.pop();
      for (std::vector<int>::size_type i = 0; i < g.getVerticesNum(); ++i) {
        if (g.isEdge(node, i) && parent[i] == -1) {
          parent[i] = node;
          q.push(i);
          if (i == end) {
            break;
          }
        }
      }
    }
  } else {
    try {
      bellmanFord(g, parent);
    } catch (const runtime_error &e) {
      return e.what();
    }
  }

  if (parent[end] == -1) {
    return "No path found";
  }

  vector<int> path;
  for (std::vector<int>::size_type at = end; at != start; at = parent[at]) {
    path.push_back(at);
  }
  path.push_back(start);

  std::reverse(path.begin(), path.end());
  string result;
  for (size_t i = 0; i < path.size(); ++i) {
    result += to_string(path[i]);
    if (i != path.size() - 1) {
      result += "->";
    }
  }

  return result;
}

bool isContainsCycle(Graph &g) {
  if (g.getVerticesNum() == 0) {
    return false;
  }

  vector<bool> visited(g.getVerticesNum(), false);
  if (g.isDirected()) {
    for (std::vector<int>::size_type i = 0; i < g.getVerticesNum(); i++) {
      queue<int> q;
      q.push(i);
      visited[i] = true;
      while (!q.empty()) {
        std::vector<int>::size_type node = q.front();
        q.pop();
        for (std::vector<int>::size_type j = 0; j < g.getVerticesNum(); j++) {
          if (g.isEdge(node, j)) {
            if (visited[j]) {
              return true;
            }
            visited[j] = true;
            q.push(j);
          }
        }
      }
    }
    return false;
  } else {
    for (std::vector<int>::size_type i = 0; i < g.getVerticesNum(); i++) {
      if (!visited[i]) {
        queue<int> q;
        q.push(i);
        visited[i] = true;
        while (!q.empty()) {
          std::vector<int>::size_type node = q.front();
          q.pop();
          for (std::vector<int>::size_type j = 0; j < g.getVerticesNum(); j++) {
            if (g.isEdge(node, j)) {
              if (visited[j]) {
                return true;
              }
              visited[j] = true;
              q.push(j);
            }
          }
        }
      }
    }
    return false;
  }
}

string isBipartite(Graph &g) {
  if (g.getVerticesNum() == 0) {
    return "The graph is bipartite: A={}, B={}";
  }

  vector<int> color(g.getVerticesNum(), -1);

  for (std::vector<int>::size_type i = 0; i < g.getVerticesNum(); i++) {
    if (color[i] == -1) {
      color[i] = 0;
      queue<int> q;
      q.push(i);

      while (!q.empty()) {
        std::vector<int>::size_type u = q.front();
        q.pop();

        for (std::vector<int>::size_type v = 0; v < g.getVerticesNum(); ++v) {
          if (g.isEdge(u, v)) {
            if (color[v] == -1) {
              color[v] = 1 - color[u];
              q.push(v);
            } else if (color[v] == color[u]) {
              return "The graph is not bipartite";
            }
          }
        }
      }
    }
  }

  string groupA = "";
  string groupB = "";
  for (std::vector<int>::size_type i = 0; i < g.getVerticesNum(); ++i) {
    if (color[i] == 0) {
      groupA += to_string(i) + ", ";
    } else {
      groupB += to_string(i) + ", ";
    }
  }
  if (groupA.empty()) {
    groupA = ".."; // adding ".." to indicate empty set as in the next lines we
                   // remove the last two characters
  }
  if (groupB.empty()) {
    groupB = ".."; // same as above
  }
  groupA.pop_back(); // remove last ' '
  groupB.pop_back(); // remove last ' '
  groupA.pop_back(); // remove last ','
  groupB.pop_back(); // remove last ','

  return "The graph is bipartite: A={" + groupA + "}, B={" + groupB + "}.";
}

string negativeCycle(Graph &g) {
  if (g.getVerticesNum() == 0) {
    return "The graph does not contain any negative cycle";
  }

  vector<int> parent(g.getVerticesNum(), -1);
  try {
    bellmanFord(g, parent);
  } catch (const runtime_error &e) {
    return e.what();
  }
  return "The graph does not contain any negative cycle";
}
