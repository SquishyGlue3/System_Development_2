// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#include "Graph.hpp"
#include <iostream>
#include <vector>
using namespace std;

void Graph::loadGraph(std::vector<std::vector<int>>
                          &matrix) // load the graph from the input matrix
{
  for (const std::vector<int> &row : matrix) {
    if (row.size() !=
        matrix.size()) { // check if the matrix is square by checking each row
                         // size vs the matrix size
      throw std::invalid_argument("Invalid graph");
    }
  }
  adjacencyMatrix = matrix;
}

void Graph::printGraph() {
  for (const std::vector<int> &row :
       adjacencyMatrix) { // for each row in the original matrix(using
                          // reference), using const to prevent changing the
                          // original matrix
    for (const int edge : row) {
      std::cout << edge << " ";
    }
    std::cout << std::endl;
  }
}

Graph &Graph::getGraph() { return *this; }

int Graph::getEdgeValue(std::vector<int>::size_type i,
                        std::vector<int>::size_type j) {
  return adjacencyMatrix[i][j];
}

bool Graph::isEdge(std::vector<int>::size_type i,
                   std::vector<int>::size_type j) {
  return (adjacencyMatrix[i][j] !=
          0); // if the value is not 0 than there is an edge
}

int Graph::getVerticesNum() { return adjacencyMatrix.size(); }

bool Graph::isDirected() {
  for (std::vector<int>::size_type i = 0; i < adjacencyMatrix.size(); i++) {
    for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size();
         j++) {
      if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i]) {
        return true;
      }
    }
  }
  return false;
}

bool Graph::isWeighted() {
  for (std::vector<int>::size_type i = 0; i < adjacencyMatrix.size(); i++) {
    for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size();
         j++) {
      if (adjacencyMatrix[i][j] > 1) {
        return true;
      }
    }
  }
  return false;
}

vector<int> Graph::getNeighbours(std::vector<int>::size_type i) {
  vector<int> neighbours;
  for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size(); j++) {
    if (isEdge(i, j)) {
      neighbours.push_back(j);
    }
  }
  return neighbours;
}

vector<int> Graph::getRow(std::vector<int>::size_type i) {
  return adjacencyMatrix[i];
}

vector<int> Graph::getCol(std::vector<int>::size_type j) {
  std::vector<int> col;
  for (std::vector<int>::size_type i = 0; i < adjacencyMatrix.size(); i++) {
    col.push_back(adjacencyMatrix[i][j]); // push the value of the j column in
                                          // the i place in the col vector
  }
  return col;
}

Graph Graph::getTranspose() {
  Graph g;
  std::vector<std::vector<int>> transposedMatrix;
  for (std::vector<int>::size_type i = 0; i < adjacencyMatrix.size(); i++) {
    std::vector<int> row;
    for (std::vector<int>::size_type j = 0; j < adjacencyMatrix[i].size();
         j++) {
      row.push_back(adjacencyMatrix[j][i]); // push the value of the j column in
                                            // the i place in the row vector
    }
    transposedMatrix.push_back(row);
  }
  g.loadGraph(transposedMatrix);
  return g;
};