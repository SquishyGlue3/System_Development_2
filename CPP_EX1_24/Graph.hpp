// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>


class Graph {
private:
    std::vector<std::vector<int>> adjacencyMatrix;
public:
    void loadGraph(std::vector<std::vector<int>>& matrix);
    void printGraph();
    Graph& getGraph();
    int getEdgeValue(std::vector<int>::size_type i, std::vector<int>::size_type j);
    bool isEdge(std::vector<int>::size_type i, std::vector<int>::size_type j);
    int getVerticesNum();
    bool isDirected();
    bool isWeighted();
    std::vector<int> getNeighbours(std::vector<int>::size_type i);
    std::vector<int> getRow(std::vector<int>::size_type i);
    std::vector<int> getCol(std::vector<int>::size_type j);
    Graph getTranspose();
};
    #endif // GRAPH_HPP