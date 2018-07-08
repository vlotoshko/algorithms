//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   04-Jul-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef EDGEWEIGHTEDGRAPH_HPP
#define EDGEWEIGHTEDGRAPH_HPP
//--------------------------------------------------------------------------------------------------
#include "Node.hpp"
#include "Edge.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <memory>

namespace graph
{

class EdgeWeightedGraph;
struct IAddEdgeStrategy
{
    virtual void addEdge(EdgeWeightedGraph & gr, Edge e) = 0;
    virtual ~IAddEdgeStrategy() = default;
};

//--------------------------------------------------------------------------------------------------
// Graph structure. Containes array of vertexes, where vertex V is a node and the value of the node
// is an index of vertex connected with V. All other vertexes connected with V adds to the node
// as linked list.
//
class EdgeWeightedGraph
{
public:
    using EdgeContainer = std::list<Edge>;
    EdgeWeightedGraph(size_t v);
    EdgeWeightedGraph(std::string fileName, std::unique_ptr<IAddEdgeStrategy> strategy);

    size_t vertexCount() const { return v_; }
    size_t edgeCount() const { return e_; }
    void addEdge(Edge e);
    const EdgeContainer& operator[] (size_t index) const;
    EdgeContainer edges() const;

    void toString() const;

protected:
    friend struct NonDirectedGraphStrategy;
    friend struct DirectedGraphStrategy;
    size_t v_;
    size_t e_;
    std::vector<EdgeContainer> edges_;
    std::unique_ptr<IAddEdgeStrategy> addEdge_;
};

struct NonDirectedGraphStrategy : public IAddEdgeStrategy
{
    void addEdge(EdgeWeightedGraph & gr, Edge e) override
    {
        size_t v = e.either();
        size_t w = e.other(v);
        gr.edges_[v].push_back(e);
        gr.edges_[w].push_back(e);
        ++gr.e_;
    }
};

struct DirectedGraphStrategy : public IAddEdgeStrategy
{
    void addEdge(EdgeWeightedGraph & gr, Edge e) override
    {
        gr.edges_[e.either()].push_back(e);
        ++gr.e_;
    }
};

} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // EDGEWEIGHTEDGRAPH_HPP
//--------------------------------------------------------------------------------------------------

