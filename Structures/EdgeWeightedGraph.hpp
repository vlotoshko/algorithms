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

struct IDirectionStrategy;

//--------------------------------------------------------------------------------------------------
//
//
class EdgeWeightedGraph
{
public:
    using EdgeContainer = std::list<Edge>;
    explicit EdgeWeightedGraph(size_t v);
    EdgeWeightedGraph(std::string fileName, std::shared_ptr<IDirectionStrategy> strategy);

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
    std::shared_ptr<IDirectionStrategy> directionStrategy_;
};


//--------------------------------------------------------------------------------------------------
//
//
struct IDirectionStrategy
{
    virtual void addEdge(EdgeWeightedGraph & gr, Edge e) = 0;
    virtual void edges(const EdgeWeightedGraph & gr, EdgeWeightedGraph::EdgeContainer & ec) = 0;
    virtual ~IDirectionStrategy() = default;
};

struct NonDirectedEWGraphStrategy : public IDirectionStrategy
{
    void addEdge(EdgeWeightedGraph & gr, Edge e) override;
    void edges(const EdgeWeightedGraph & gr, EdgeWeightedGraph::EdgeContainer & ec) override;
};

struct DirectedEWGraphStrategy : public IDirectionStrategy
{
    void addEdge(EdgeWeightedGraph & gr, Edge e) override;
    void edges(const EdgeWeightedGraph & gr, EdgeWeightedGraph::EdgeContainer & ec) override;
};

} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // EDGEWEIGHTEDGRAPH_HPP
//--------------------------------------------------------------------------------------------------

