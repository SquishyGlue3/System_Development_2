// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
using namespace std;
namespace ariel
{

    class Graph
    {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;

    public:
        void loadGraph(std::vector<std::vector<int>> &matrix);
        void printGraph();
        Graph &getGraph();
        int getEdgeValue(size_t i, size_t j);
        bool isEdge(size_t i, size_t j);
        size_t getVerticesNum();
        size_t getEdgesNum();
        bool isDirected();
        bool isWeighted();
        std::vector<size_t> getNeighbours(size_t i);
        std::vector<int> getRow(size_t i);
        std::vector<int> getCol(size_t j);
        Graph getTranspose();
        friend Graph operator+(Graph &g1, Graph &g2);
        Graph& operator+=(Graph &g);
        void operator+() const;
        void operator-() const;
        friend Graph& operator-(Graph &g1, Graph &g2);
        Graph& operator-=(Graph &g);
        friend bool operator<(Graph &g1, Graph &g2);
        friend bool operator<=(Graph &g1, Graph &g2);
        friend bool operator>(Graph &g1, Graph &g2);
        friend bool operator>=(Graph &g1, Graph &g2);
        friend bool operator==(Graph &g1, Graph &g2);
        friend bool operator!=(Graph &g1, Graph &g2);
        Graph& operator++();//pre-increment, ie. ++g
        Graph operator++(int);//post-increment, ie. g++
        Graph& operator--();//pre-decrement, ie. --g
        Graph operator--(int);//post-decrement, ie. g--
        friend Graph& operator*(Graph &g1, Graph &g2);
        friend Graph& operator*(Graph &g, int scalar);
        friend std::ostream& operator<<(std::ostream &os, Graph &g);
    };
};
#endif // GRAPH_HPP