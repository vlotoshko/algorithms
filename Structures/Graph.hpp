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
#include <memory>

namespace graph
{

class Graph;
struct IAddEdgeStrategy
{
    virtual void addEdge(Graph & gr, size_t v, size_t w) = 0;
    virtual ~IAddEdgeStrategy() = default;
};

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
    Graph (std::string fileName, std::unique_ptr<IAddEdgeStrategy> strategy);

    size_t vertexCount() const { return v_; }
    size_t edgeCount() const { return e_; }
    void addEdge(size_t v, size_t w);
    const GNode& operator[] (size_t index) const;
    void toString() const;

    static size_t degree(const Graph& g, size_t v);
    static size_t maxDegree(const Graph& g);
    static size_t avgDegree(const Graph& g);
    static int selfLoops(const Graph& g);

protected:
    friend struct NonDirectedGraphStrategy;
    friend struct DirectedGraphStrategy;
    size_t v_;
    size_t e_;
    std::vector<GNode> vertexes_;
    std::unique_ptr<IAddEdgeStrategy> addEdge_;
};

struct NonDirectedGraphStrategy : public IAddEdgeStrategy
{
    void addEdge(Graph & gr, size_t v, size_t w) override
    {
        gr.vertexes_[v].add(new Graph::GNode(w));
        gr.vertexes_[w].add(new Graph::GNode(v));
        ++gr.e_;
    }
};

struct DirectedGraphStrategy : public IAddEdgeStrategy
{
    void addEdge(Graph & gr, size_t v, size_t w) override
    {
        gr.vertexes_[v].add(new Graph::GNode(w));
        ++gr.e_;
    }
};

} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_HPP
//--------------------------------------------------------------------------------------------------

