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
#include <stack>
#include <queue>
#include <memory>

namespace graph
{

struct IDirectionEWGStrategy;

//--------------------------------------------------------------------------------------------------
//
//
class EdgeWeightedGraph
{
public:
    using EdgeContainer = std::list<EdgeWeigthed>;
    explicit EdgeWeightedGraph(size_t v);
    EdgeWeightedGraph(std::string fileName, std::shared_ptr<IDirectionEWGStrategy> strategy);

    size_t vertexCount() const { return v_; }
    size_t edgeCount() const { return e_; }
    void addEdge(EdgeWeigthed e);
    const EdgeContainer& operator[] (size_t index) const;
    EdgeContainer edges() const;

    void toString() const;

protected:
    friend struct NonDirectedEWGraphStrategy;
    friend struct DirectedEWGraphStrategy;
    size_t v_;
    size_t e_;
    std::vector<EdgeContainer> vertexes_;
    std::shared_ptr<IDirectionEWGStrategy> directionStrategy_;
};


//--------------------------------------------------------------------------------------------------
//
//
struct IDirectionEWGStrategy
{
    virtual void addEdge(EdgeWeightedGraph & gr, EdgeWeigthed e) = 0;
    virtual void edges(const EdgeWeightedGraph & gr, EdgeWeightedGraph::EdgeContainer & ec) = 0;
    virtual ~IDirectionEWGStrategy() = default;
};

struct NonDirectedEWGraphStrategy : public IDirectionEWGStrategy
{
    void addEdge(EdgeWeightedGraph & gr, EdgeWeigthed e) override;
    void edges(const EdgeWeightedGraph & gr, EdgeWeightedGraph::EdgeContainer & ec) override;
};

struct DirectedEWGraphStrategy : public IDirectionEWGStrategy
{
    void addEdge(EdgeWeightedGraph & gr, EdgeWeigthed e) override;
    void edges(const EdgeWeightedGraph & gr, EdgeWeightedGraph::EdgeContainer & ec) override;
};

//--------------------------------------------------------------------------------------------------
// Sorts vertexes by pre, post and reversed post orders while performing dfs algorithm
//
class DepthFirstOrderEWG
{
public:
    explicit DepthFirstOrderEWG(const EdgeWeightedGraph & g);
    std::stack<size_t> & reversePost() { return reversePost_; }
    std::queue<size_t> & pre() { return pre_; }
    std::queue<size_t> & post() { return post_; }
private:
    std::vector<bool> marked_;
    std::stack<size_t> reversePost_;
    std::queue<size_t> pre_;
    std::queue<size_t> post_;
    void dfs(const EdgeWeightedGraph & g, size_t v);
};


//--------------------------------------------------------------------------------------------------
// Topological sort. Applies only with directed acyclic graphs
//
class TopologicalEWG
{
public:
    explicit TopologicalEWG(const EdgeWeightedGraph & g);
    std::stack<size_t> & order() { return dfo_.reversePost(); }
    bool isDAG() const { return isDAG_; }
private:
    DepthFirstOrderEWG dfo_;
    bool isDAG_;
};

//----------------------------------------CyclicEWG----------------------------------------------------------
// Defines whether graph is cyclic or not
//EdgeWeightedGraph
class CyclicEWG
{
public:
    explicit CyclicEWG(const EdgeWeightedGraph & g);
    bool isCyclic() const { return hasCycle_; }
private:
    bool hasCycle_;
    std::vector<bool> marked_;
    void dfs(const EdgeWeightedGraph & g, size_t v, size_t u);
};

} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // EDGEWEIGHTEDGRAPH_HPP
//--------------------------------------------------------------------------------------------------

