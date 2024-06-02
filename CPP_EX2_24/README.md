# מטלה 2
Here are the new features that have been added to the Graph class. 

New Methods in Graph.cpp

getGraph(): Returns the current graph object.

getRowSum(): Returns the number of vertices (i.e., the sum of rows) in the graph.

getColSum(): Returns the number of vertices (i.e., the sum of columns) in the graph.

getEdgesNum(): Returns the number of edges in the graph.

operator+ (Graph &g1, Graph &g2): Overloads the + operator to add two graphs.

operator+= (Graph &g): Overloads the += operator to add another graph to the current graph.

operator+(): Overloads the unary + operator (empty implementation).

operator-(): Overloads the unary - operator to negate the adjacency matrix values.

operator- (Graph &g1, Graph &g2): Overloads the - operator to subtract one graph from another.

operator-= (Graph &g): Overloads the -= operator to subtract another graph from the current graph.

operator== (Graph &g1, Graph &g2): Overloads the == operator to compare two graphs for equality.

operator< (Graph &g1, Graph &g2): Overloads the < operator to compare two graphs.

operator<= (Graph &g1, Graph &g2): Overloads the <= operator to compare two graphs.

operator> (Graph &g1, Graph &g2): Overloads the > operator to compare two graphs.

operator>= (Graph &g1, Graph &g2): Overloads the >= operator to compare two graphs.

operator!= (Graph &g1, Graph &g2): Overloads the != operator to compare two graphs for inequality.

operator++(): Overloads the pre-increment operator to increment all edge values by one.

operator++(int): Overloads the post-increment operator to increment all edge values by one.

operator--(): Overloads the pre-decrement operator to decrement all edge values by one.

operator--(int): Overloads the post-decrement operator to decrement all edge values by one.

*operator (Graph &g1, Graph &g2)**: Overloads the * operator to multiply two graphs (matrix multiplication).

*operator (Graph &g, int scalar)**: Overloads the * operator to multiply a graph by a scalar.

operator<< (std::ostream &os, Graph &g): Overloads the << operator to print the graph.
