// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#include "Graph.hpp"
using namespace ariel;

#include <iostream>
#include <vector>
using namespace std;

void Graph::loadGraph(std::vector<std::vector<int>> &matrix) // load the graph from the input matrix
{
  for (const std::vector<int> &row : matrix)
  {
    if (row.size() != matrix.size())
    { // check if the matrix is square by checking each row size vs the matrix size
      throw std::invalid_argument("Invalid graph");
    }
  }
  adjacencyMatrix = matrix;
}

void Graph::printGraph()
{
  for (const std::vector<int> &row : adjacencyMatrix)
  { // for each row in the original matrix(using reference), using const to prevent changing the original matrix
    for (const int edge : row)
    {
      std::cout << edge << " ";
    }
    std::cout << std::endl;
  }
}

Graph &Graph::getGraph() { return *this; }

int Graph::getEdgeValue(size_t i, size_t j)
{
  if (i >= adjacencyMatrix.size() || j >= adjacencyMatrix[i].size())
  {
    throw std::invalid_argument("Invalid index");
  }
  return this->adjacencyMatrix[i][j];
}

bool Graph::isEdge(size_t i, size_t j)
{
  if (i >= adjacencyMatrix.size() || j >= adjacencyMatrix[i].size())
  {
    throw std::invalid_argument("Invalid index");
  }
  return (adjacencyMatrix[i][j] != 0); // if the value is not 0 than there is an edge
}

size_t Graph::getVerticesNum() { return adjacencyMatrix.size(); }

bool Graph::isDirected()
{
  for (size_t i = 0; i < adjacencyMatrix.size(); i++)
  {
    for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
    {
      if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
      {
        return true;
      }
    }
  }
  return false;
}

bool Graph::isWeighted()
{
  for (size_t i = 0; i < adjacencyMatrix.size(); i++)
  {
    for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
    {
      if (adjacencyMatrix[i][j] > 1)
      {
        return true;
      }
    }
  }
  return false;
}

vector<size_t> Graph::getNeighbours(size_t i)
{
  vector<size_t> neighbours;
  for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
  {
    if (isEdge(i, j))
    {
      neighbours.push_back(j);
    }
  }
  return neighbours;
}

vector<int> Graph::getRow(size_t i)
{
  return adjacencyMatrix[i];
}

vector<int> Graph::getCol(size_t j)
{
  std::vector<int> col;
  for (size_t i = 0; i < adjacencyMatrix.size(); i++)
  {
    col.push_back(adjacencyMatrix[i][j]); // push the value of the j column in the i place in the col vector
  }
  return col;
}

Graph Graph::getTranspose()
{
  Graph g;
  std::vector<std::vector<int>> transposedMatrix;
  for (size_t i = 0; i < adjacencyMatrix.size(); i++)
  {
    std::vector<int> row;
    for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
    {
      row.push_back(adjacencyMatrix[j][i]); // push the value of the j column in the i place in the row vector
    }
    transposedMatrix.push_back(row);
  }
  g.loadGraph(transposedMatrix);
  return g;
}

size_t Graph::getRowSum()
{
  vector<int> row = this->getRow(0);
  return row.size();
}

size_t Graph::getColSum()
{
  vector<int> col = this->getCol(0);
  return col.size();
}

string getDimention(Graph &g) // output the dimention of a graph
{
  int countRow = g.getRowSum();
  int countCol = g.getColSum();
  return to_string(countRow) + "x" + to_string(countCol);
}
size_t ariel::Graph::getEdgesNum() const
{
  Graph g = *this;
  size_t count = 0;
  for (size_t i = 0; i < g.getVerticesNum(); i++)
  {
    for (size_t j = 0; j < g.getVerticesNum(); j++)
    {
      if (g.isEdge(i, j))
      {
        count++;
      }
    }
  }
  return count;
}
Graph ariel::operator+(Graph &g1, Graph &g2)
{
  Graph g;
  std::vector<std::vector<int>> sumMatrix;
  if (getDimention(g1) != getDimention(g2))
  {
    throw std::invalid_argument("Invalid graph");
  }
  for (size_t i = 0; i < g1.getRowSum(); i++)
  {
    std::vector<int> row;
    for (size_t j = 0; j < g1.getColSum(); j++)
    {
      row.push_back(g1.getEdgeValue(i, j) + g2.getEdgeValue(i, j)); //
    }
    sumMatrix.push_back(row);
  }
  g.loadGraph(sumMatrix);
  return g;
}

Graph &ariel::Graph::operator+=(Graph &g)
{
  *this = *this + g;
  return *this;
}

void ariel::Graph::operator+() const{}

void ariel::Graph::operator-() const
{
  Graph g = *this;
  for (size_t i = 0; i < g.getRowSum(); i++)
  {
    for (size_t j = 0; j < g.getColSum(); j++)
    {
      g.adjacencyMatrix[i][j] = -g.adjacencyMatrix[i][j];
    }
  }
}

Graph ariel::operator-(Graph &g1, Graph &g2)
{
  if (getDimention(g1) != getDimention(g2))
  {
    throw std::invalid_argument("Invalid graph");
  }
  Graph g;
  std::vector<std::vector<int>> subMatrix;
  for (size_t i = 0; i < g1.getRowSum(); i++)
  {
    std::vector<int> row;
    for (size_t j = 0; j < g1.getColSum(); j++)
    {
      row.push_back(g1.getEdgeValue(i, j) - g2.getEdgeValue(i, j));
    }
    subMatrix.push_back(row);
  }
  g.loadGraph(subMatrix);
  return g;
}

Graph &ariel::Graph::operator-=(Graph &g)
{
  *this = *this - g;
  return *this;
}

bool ariel::operator==(Graph &g1, Graph &g2)
{
  if (getDimention(g1) != getDimention(g2))
  {
    return false;
  }
  for (size_t i = 0; i < g1.getRowSum(); i++)
  {
    for (size_t j = 0; j < g1.getColSum(); j++)
    {
      if (g1.getEdgeValue(i, j) != g2.getEdgeValue(i, j))
      {
        return false;
      }
    }
  }
  return true;
}

bool ariel::operator<(Graph &g1, Graph &g2)
{ 
  if (g1 == g2) // step 1 - check if the graphs are equal
  {
    return false;
  }
  if (g1.getEdgesNum() < g2.getEdgesNum()) // step 3 - g2 has more edges
  {
    return true;
  }
  if (g1.getEdgesNum() == g2.getEdgesNum())
  {
    if (g1.getVerticesNum() < g2.getVerticesNum()) // step 3 - they have same amount of edges and g2 has more vertices
    {
      return true;
    }
  }
  return false; // if none of the above conditions are met
}

bool ariel::operator<=(Graph &g1, Graph &g2)
{
  return (g1 < g2 || g1 == g2);
}

bool ariel::operator>(Graph &g1, Graph &g2)
{
  return !(g1 <= g2);
}

bool ariel::operator>=(Graph &g1, Graph &g2)
{
  return !(g1 < g2);
}

bool ariel::operator!=(Graph &g1, Graph &g2)
{
  return !(g1 == g2);
}

Graph &ariel::Graph::operator++()// pre-increment
{
  for (size_t i = 0; i < this->getRowSum(); i++)
  {
    for (size_t j = 0; j < this->getColSum(); j++)
    {
      this->adjacencyMatrix[i][j]++;
    }
  }
  return *this;
}

Graph ariel::Graph::operator++(int)// post-increment
{
  Graph g = *this;
  ++*this;
  return g;
}

Graph &ariel::Graph::operator--()// pre-decrement
{
  for (size_t i = 0; i < this->getRowSum(); i++)
  {
    for (size_t j = 0; j < this->getColSum(); j++)
    {
      this->adjacencyMatrix[i][j]--;
    }
  }
  return *this;
}

Graph ariel::Graph::operator--(int)// post-decrement
{
  Graph g = *this;
  --*this;
  return g;
}

Graph ariel::operator*(Graph &g1, Graph &g2)
{
  if (g1.getColSum() != g2.getRowSum())
  {
    throw std::invalid_argument("Invalid graphs multiplication");
  }
  Graph g;
  std::vector<std::vector<int>> mulMatrix;
  for (size_t i = 0; i < g1.getRowSum(); i++)
  {
    std::vector<int> row;
    for (size_t j = 0; j < g2.getColSum(); j++)
    {
      int sum = 0;
      for (size_t k = 0; k < g1.getColSum(); k++)
      {
        sum += g1.getEdgeValue(i, k) * g2.getEdgeValue(k, j);
      }
      row.push_back(sum);
    }
    mulMatrix.push_back(row);
  }
  g.loadGraph(mulMatrix);
  return g;
}

Graph ariel::operator*(Graph &g, int scalar)
{
  Graph g1 = g;
  for (size_t i = 0; i < g1.getRowSum(); i++)
  {
    for (size_t j = 0; j < g1.getColSum(); j++)
    {
      g1.adjacencyMatrix[i][j] *= scalar;
    }
  }
  return g1;
}

std::ostream &ariel::operator<<(std::ostream &os, Graph &g)
{
  for (size_t i = 0; i < g.getRowSum(); i++)
  {
    for (size_t j = 0; j < g.getColSum(); j++)
    {
      os << g.getEdgeValue(i, j) << " ";
    }
    os << std::endl;
  }
  return os;
}
