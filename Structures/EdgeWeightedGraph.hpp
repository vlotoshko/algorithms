//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   04-Jul-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef EDGEWEIGHTEDGRAPH_HPP
#define EDGEWEIGHTEDGRAPH_HPP
//--------------------------------------------------------------------------------------------------
#include "Edge.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <memory>

namespace graph
{

class EdgeWeightedGraph;
struct IAddEdgeWeightedStrategy
{
    virtual void addEdge(EdgeWeightedGraph & gr, Edge e) = 0;
    virtual ~IAddEdgeWeightedStrategy() = default;
};

//--------------------------------------------------------------------------------------------------
//
//
class EdgeWeightedGraph
{
public:
    using EdgeContainer = std::list<Edge>;
    explicit EdgeWeightedGraph(size_t v);
    EdgeWeightedGraph(std::string fileName, std::shared_ptr<IAddEdgeWeightedStrategy> strategy);

    size_t vertexCount() const { return v_; }
    size_t edgeCount() const { return e_; }
    void addEdge(Edge e);
    const EdgeContainer& operator[] (size_t index) const;
    EdgeContainer edges() const;

    void toString() const;

protected:
    friend struct NonDirectedEWGraphStrategy;
    friend struct DirectedEWGraphStrategy;
    size_t v_;
    size_t e_;
    std::vector<EdgeContainer> vertexes_;
    std::shared_ptr<IAddEdgeWeightedStrategy> addEdge_;
};

struct NonDirectedEWGraphStrategy : public IAddEdgeWeightedStrategy
{
    void addEdge(EdgeWeightedGraph & gr, Edge e) override
    {
        size_t v = e.either();
        size_t w = e.other(v);
        gr.vertexes_[v].push_back(e);
        gr.vertexes_[w].push_back(e);
        ++gr.e_;
    }
};

struct DirectedEWGraphStrategy : public IAddEdgeWeightedStrategy
{
    void addEdge(EdgeWeightedGraph & gr, Edge e) override
    {
        gr.vertexes_[e.either()].push_back(e);
        ++gr.e_;
    }
};

} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // EDGEWEIGHTEDGRAPH_HPP
//--------------------------------------------------------------------------------------------------

