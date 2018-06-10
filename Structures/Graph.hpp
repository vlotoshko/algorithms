//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   10-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef GRAPH_HPP
#define GRAPH_HPP
//--------------------------------------------------------------------------------------------------
#include "Node.hpp"

#include<iostream>
#include <map>

//--------------------------------------------------------------------------------------------------
// Graph structure. Containes array of vertexes, where vertex V is a node and the value of the node
// is an index of vertex connected with V. All other vertexes connected with V adds to the node
// as linked list.
//
class Graph
{
public:
    using GNode = Node<size_t>;

    Graph(size_t v);
    Graph (std::string fileName);
    ~Graph();

    size_t vertexes() { return v_; }
    size_t edges() { return e_; }
    void addEdge(size_t v, size_t w);
    GNode *adj(size_t v);
    void toString();

    static size_t degree(Graph* g, size_t v);
    static size_t maxDegree(Graph* g);
    static size_t avgDegree(Graph* g);
    static int getLoops(Graph* g);

private:
    size_t v_;
    size_t e_;
    GNode* adj_;
};

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_HPP
//--------------------------------------------------------------------------------------------------

