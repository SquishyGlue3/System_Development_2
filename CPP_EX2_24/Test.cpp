// Rotem Melamed
// 209039072
// rotem.melamed25@gmail.com
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace ariel;
using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    ariel::Graph g4;
    g4.loadGraph(expectedGraph);
    for (size_t i = 0; i < g3.getVerticesNum(); i++)
    {
        for (size_t j = 0; j < g3.getVerticesNum(); j++)
        {
            int g3Edge = g3.getEdgeValue(i, j);
            int g4Edge = g4.getEdgeValue(i, j);
            CHECK(g3Edge == g4Edge); // checking if all edges are equal
        }
    }
    CHECK(g3 == g4); // checking if the graphs are equal using the == operator
}

TEST_CASE("Test graph operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 == g2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}};
    g3.loadGraph(graph3);

    CHECK(g1 != g3);
    CHECK(g1 > g3);
    CHECK(g3 < g1);
    CHECK(g1 >= g3);
    CHECK(g3 <= g1);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g4.loadGraph(graph4);
    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g5.loadGraph(graph5);
    CHECK(g4 < g5);
    CHECK(g5 > g4);
}

TEST_CASE("Test graph + / -")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {1, 2, 1},
        {2, 1, 2},
        {1, 2, 1}};
    g2.loadGraph(graph2);

    ariel::Graph g1copy;
    g1copy.loadGraph(graph1);

    g1++;
    CHECK(g1 == g2);

    g1--;
    CHECK(g1 == g1copy);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g4.loadGraph(graph4);

    g4 += g1;
    CHECK(g4 == g1);

    ariel::Graph g5;
    ariel::Graph g5copy;
    g5.loadGraph(graph4);
    g5copy.loadGraph(graph4);

    g5 -= g1;
    g5 += g1;
    CHECK(g5 == g5copy);
}
TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    ariel::Graph g5;
    g5.loadGraph(expectedGraph);
    CHECK(g4 == g5);

    ariel::Graph g10 = g1 * 2;
    ariel::Graph g6;
    vector<vector<int>> expectedGraph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g6.loadGraph(expectedGraph2);
    CHECK(g10 == g6);
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_NOTHROW(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}
TEST_CASE("Test Graph Basic Operations")
{
    Graph g;
    vector<vector<int>> matrix = {
        {0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g.loadGraph(matrix);

    CHECK(g.getVerticesNum() == 5);

    CHECK(g.isEdge(0, 1) == true);
    CHECK(g.isEdge(0, 2) == false);

    CHECK(g.getEdgeValue(1, 2) == 1);
    CHECK(g.getEdgeValue(0, 2) == 0);

    CHECK(g.isDirected() == false);
    CHECK(g.isWeighted() == false);

    vector<size_t> neighbours = g.getNeighbours(1);
    CHECK(neighbours.size() == 2);
    CHECK(neighbours[0] == 0);
    CHECK(neighbours[1] == 2);

    Graph transpose = g.getTranspose();
    CHECK(transpose.getEdgeValue(1, 0) == 1);
    CHECK(transpose.getEdgeValue(2, 1) == 1);
}

TEST_CASE("Test Algorithms Basic Operations")
{
    Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g1.loadGraph(matrix1);
    Algorithms algo;

    CHECK(algo.isConnected(g1) == true);

    CHECK(algo.shortestPath(g1, 0, 4) == "0->1->2->3->4");

    CHECK(algo.isContainsCycle(g1) == true);

    CHECK(algo.isBipartite(g1) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}.");

    CHECK(algo.negativeCycle(g1) == "The graph does not contain any negative cycle");

    Graph g2; // testing undirected graph with cycle
    vector<vector<int>> matrix2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g2.loadGraph(matrix2);

    CHECK(algo.isContainsCycle(g2) == true);
    CHECK(algo.isConnected(g2) == true);
    CHECK(algo.isBipartite(g2) == "The graph is bipartite: A={0, 2}, B={1, 3, 4}.");
    CHECK(algo.negativeCycle(g2) == "The graph does not contain any negative cycle");
    CHECK(algo.shortestPath(g2, 0, 4) == "0->4");
}

TEST_CASE("Test Algorithms Weighted Graph")
{
    Graph g1; // testing weighted graph with negative cycle
    vector<vector<int>> matrix1 = {
        {0, 2, 0, 0, 0},
        {2, 0, 3, 0, 0},
        {0, 3, 0, -4, 0},
        {0, 0, -4, 0, 5},
        {0, 0, 0, 5, 0}};
    g1.loadGraph(matrix1);
    Algorithms algo;

    CHECK(algo.isConnected(g1) == true);

    CHECK(algo.shortestPath(g1, 0, 4) == "The graph contains negative cycle 3->2->3");

    CHECK(algo.negativeCycle(g1) == "The graph contains negative cycle 3->2->3");

    CHECK(algo.isBipartite(g1) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}.");

    Graph g2; // testing weighted graph with no negative cycle
    vector<vector<int>> matrix2 = {
        {0, 1, 0, 4},
        {2, 0, 9, 1},
        {6, 2, 0, 0},
        {3, 1, 0, 0}};
    g2.loadGraph(matrix2);
    CHECK(algo.negativeCycle(g2) == "The graph does not contain any negative cycle");

    CHECK(algo.shortestPath(g2, 0, 3) == "0->3");

    CHECK(algo.isConnected(g2) == true);

    CHECK(algo.isBipartite(g2) == "The graph is not bipartite.");

    // Test with a directed graph that contains a cycle
    vector<vector<int>> matrix3 = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g2.loadGraph(matrix3);
    CHECK(algo.negativeCycle(g2) == "The graph does not contain any negative cycle");
    CHECK(algo.shortestPath(g2, 0, 2) == "0->2");
    CHECK(algo.isConnected(g2) == true);
    CHECK(algo.isBipartite(g2) == "The graph is bipartite: A={0}, B={1, 2, 3}.");
    CHECK(algo.isContainsCycle(g2) == true);
}

TEST_CASE("Test graph subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3 = g1 - g2;
    vector<vector<int>> expectedGraph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    ariel::Graph g4;
    g4.loadGraph(expectedGraph);

    CHECK(g3 == g4);
}

TEST_CASE("Test graph scalar multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2 = g1 * 3;
    vector<vector<int>> expectedGraph = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    ariel::Graph g3;
    g3.loadGraph(expectedGraph);

    CHECK(g2 == g3);
}

TEST_CASE("Test graph transpose")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2 = g1.getTranspose();
    vector<vector<int>> expectedGraph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    ariel::Graph g3;
    g3.loadGraph(expectedGraph);

    CHECK(g2 == g3);
}

TEST_CASE("Test graph equality with different sizes")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1},
        {1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 != g2);
}

TEST_CASE("Test empty graph")
{
    vector<vector<int>> matrix = {};
    Graph g;
    g.loadGraph(matrix);
    CHECK(g.getVerticesNum() == 0);
    CHECK(g.isDirected() == false);
    CHECK(g.isWeighted() == false);
}
TEST_CASE("Test empty graph operations")
{
    ariel::Graph g1;
    vector<vector<int>> emptyGraph = {};
    g1.loadGraph(emptyGraph);

    ariel::Graph g2;
    g2.loadGraph(emptyGraph);

    CHECK(g1 == g2);
    CHECK_NOTHROW(g1 + g2);
    CHECK_NOTHROW(g1 - g2);
    CHECK_NOTHROW(g1 * 2);
}

TEST_CASE("Test graph with self-loops")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {1, 1, 0},
        {1, 1, 1},
        {0, 1, 1}};
    g1.loadGraph(graph);

    CHECK(g1.isEdge(0, 0) == true);
    CHECK(g1.isEdge(1, 1) == true);
    CHECK(g1.isEdge(2, 2) == true);
}

TEST_CASE("Test graph with negative weights")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    g1.loadGraph(graph);

    CHECK(g1.getEdgeValue(0, 1) == -1);
    CHECK(g1.getEdgeValue(1, 2) == -1);
}

TEST_CASE("Test directed graph operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g1.loadGraph(graph);

    CHECK(g1.isDirected() == true);
    CHECK(g1.isEdge(0, 1) == true);
    CHECK(g1.isEdge(1, 0) == false);
}

TEST_CASE("Test large graph operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph(1000, vector<int>(1000, 1));
    g1.loadGraph(graph);

    CHECK(g1.getVerticesNum() == 1000);
    CHECK(g1.getEdgeValue(0, 1) == 1);
}

TEST_CASE("Test disconnected graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g1.loadGraph(graph);
    ariel::Algorithms algo;

    CHECK(algo.isConnected(g1) == false);
}
