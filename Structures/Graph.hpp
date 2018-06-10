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

class Graph
{
public:
    Graph(size_t v);
    Graph (std::string fileName);
    ~Graph();

    size_t vortexes() { return v_; }
    size_t edges() { return e_; }
    void addEdge(int v, int w);
    Node<int>* adj(size_t v);
    void toString();

    static size_t degree(Graph* g, size_t v);
    static size_t maxDegree(Graph* g);
    static size_t avgDegree(Graph* g);
    static int selfLoops(Graph* g);

private:
    size_t v_;
    size_t e_;
    Node<int>* adj_;
};

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_HPP
//--------------------------------------------------------------------------------------------------

