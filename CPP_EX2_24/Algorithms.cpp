// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#include "Algorithms.hpp"
using namespace ariel;

void Algorithms::DFS(size_t node, Graph &g, vector<bool> &visited)
{
  visited[node] = true;
  for (size_t i = 0; i < g.getVerticesNum(); ++i)
  {
    if (g.isEdge(node, i) && !visited[i])
    {
      DFS(i, g, visited);
    }
  }
}

bool Algorithms::isConnected(Graph &g)
{
  if (g.getVerticesNum() == 0)
  {
    return true;
  }

  vector<bool> visited(g.getVerticesNum(), false);

  for (size_t i = 0; i < g.getVerticesNum(); ++i)
  {
    if (!visited[i])
    {
      DFS(i, g, visited);
    }
  }

  for (bool v : visited)
  {
    if (!v)
    {
      return false;
    }
  }

  return true;
}

string Algorithms::bellmanFord(Graph &g, vector<int> &parent)
{
  for (size_t i = 0; i < g.getVerticesNum(); i++)
  {
    parent[i] = -1;
  }
  for (size_t i = 0; i < g.getVerticesNum();
       i++)
  { // using Bellman-Ford algorithm to detect negative cycles starting
    // from each vertex
    vector<int> distance(g.getVerticesNum(), INT_MAX);
    distance[i] = 0;
    parent[i] = 0;

    for (size_t l = 0; l < g.getVerticesNum() - 1; l++)
    {
      for (size_t j = 0; j < g.getVerticesNum(); j++)
      {
        for (size_t k = 0; k < g.getVerticesNum(); k++)
        {
          if (g.isEdge(j, k) && distance[j] != INT_MAX &&
              distance[j] + g.getEdgeValue(j, k) < distance[k])
          {
            distance[k] = distance[j] + g.getEdgeValue(j, k);
            parent[k] = j;
          }
        }
      }
    }

    string negativeCyclePath;
    for (size_t j = 0; j < g.getVerticesNum(); j++)
    {
      for (size_t k = 0; k < g.getVerticesNum(); k++)
      {
        if (g.isEdge(j, k) && distance[j] != INT_MAX &&
            distance[j] + g.getEdgeValue(j, k) < distance[k])
        {
          size_t node = k;
          for (size_t i = 0; i < g.getVerticesNum(); i++)
          {
            node = (size_t)parent[node];
          }
          size_t start = node;
          negativeCyclePath = to_string(start);
          for (size_t i = (size_t)parent[start]; i != start;
               i = (size_t)parent[i])
          {
            negativeCyclePath += "->" + to_string(i);
          }
          negativeCyclePath += "->" + to_string(start);
          return "The graph contains negative cycle " + negativeCyclePath;
        }
      }
    }
  }
  return "algorithms finished";
}

string Algorithms::shortestPath(Graph &g, size_t start, size_t end)
{
  if (start == end)
  {
    return to_string(start);
  }
  if (g.getVerticesNum() == 0)
  {
    return "There are no vertices in the graph.";
  }

  vector<int> parent(g.getVerticesNum(), -1);
  if (!g.isWeighted())
  {
    queue<int> q;
    q.push(start);
    parent[start] = start;

    while (!q.empty())
    {
      size_t node = (size_t)q.front();
      q.pop();
      for (size_t i = 0; i < g.getVerticesNum(); ++i)
      {
        if (g.isEdge(node, i) && parent[i] == -1)
        {
          parent[i] = node;
          q.push(i);
          if (i == end)
          {
            break;
          }
        }
      }
    }
  }
  else
  {
    string bellman = bellmanFord(g, parent);
    if (bellman != "algorithms finished")
    {
      return bellman;
    }
  }
  if (parent[end] == -1)
  {
    return "No path found";
  }

  vector<int> path;
  for (size_t at = end; at != start; at = (size_t)parent[at])
  {
    path.push_back(at);
  }
  path.push_back(start);

  std::reverse(path.begin(), path.end());
  string result;
  for (size_t i = 0; i < path.size(); ++i)
  {
    result += to_string(path[i]);
    if (i != path.size() - 1)
    {
      result += "->";
    }
  }

  return result;
}

bool Algorithms::isContainsCycle(Graph &g)
{
  if (g.getVerticesNum() == 0)
  {
    return false;
  }

  vector<bool> visited(g.getVerticesNum(), false);
  if (g.isDirected())
  {
    for (size_t i = 0; i < g.getVerticesNum(); i++)
    {
      queue<int> q;
      q.push(i);
      visited[i] = true;
      while (!q.empty())
      {
        size_t node = (size_t)q.front();
        q.pop();
        for (size_t j = 0; j < g.getVerticesNum(); j++)
        {
          if (g.isEdge(node, j))
          {
            if (visited[j])
            {
              return true;
            }
            visited[j] = true;
            q.push(j);
          }
        }
      }
    }
    return false;
  }
  else
  {
    for (size_t i = 0; i < g.getVerticesNum(); i++)
    {
      if (!visited[i])
      {
        queue<int> q;
        q.push(i);
        visited[i] = true;
        while (!q.empty())
        {
          size_t node = (size_t)q.front();
          q.pop();
          for (size_t j = 0; j < g.getVerticesNum(); j++)
          {
            if (g.isEdge(node, j))
            {
              if (visited[j])
              {
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

string Algorithms::isBipartite(Graph &g)
{
  if (g.getVerticesNum() == 0)
  {
    return "The graph is bipartite: A={}, B={}";
  }

  vector<int> color(g.getVerticesNum(), -1);

  for (size_t i = 0; i < g.getVerticesNum(); ++i)
  {
    if (color[i] == -1)
    {
      color[i] = 0;
      vector<size_t> neighbours = g.getNeighbours(i);
      if (neighbours.empty())
      {
        continue;
      }
      for (size_t j : neighbours)
      {
        if (color[j] == 0)
        {
          return "The graph is not bipartite.";
        }
        if (color[j] == -1)
        {
          color[j] = 1;
        }
      }
    }
  }

  string groupA = "";
  string groupB = "";
  for (size_t i = 0; i < g.getVerticesNum(); ++i)
  {
    if (color[i] == 0)
    {
      groupA += to_string(i) + ", ";
    }
    else if (color[i] == 1)
    {
      groupB += to_string(i) + ", ";
    }
    else
    {
      return "The color of the vertex is not 0 or 1";
    }
  }
  if (groupA.empty())
  {
    groupA = ".."; 
  }
  if (groupB.empty())
  {
    groupB = ".."; 
  }
  groupA.pop_back(); 
  groupB.pop_back(); 
  groupA.pop_back();
  groupB.pop_back();

  return "The graph is bipartite: A={" + groupA + "}, B={" + groupB + "}.";
}


string Algorithms::negativeCycle(Graph &g)
{
  if (g.getVerticesNum() == 0)
  {
    return "The graph does not contain any negative cycle";
  }

  vector<int> parent(g.getVerticesNum(), -1);
  string bellman = bellmanFord(g, parent);
  if (bellman != "algorithms finished")
  {
    return bellman;
  }
  return "The graph does not contain any negative cycle";
}
