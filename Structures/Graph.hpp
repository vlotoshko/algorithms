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
#include <vector>

namespace graph
{

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

    size_t vertexes() const { return v_; }
    size_t edges() const { return e_; }
    void addEdge(size_t v, size_t w);
    const GNode *adj(size_t v) const;
    void toString() const;

    static size_t degree(const Graph* g, size_t v);
    static size_t maxDegree(const Graph* g);
    static size_t avgDegree(const Graph* g);
    static int selfLoops(const Graph* g);

private:
    size_t v_;
    size_t e_;
    std::vector<GNode> adj_;
};

} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_HPP
//--------------------------------------------------------------------------------------------------

