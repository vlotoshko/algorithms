//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   08-Jul-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef MINIMAL_SPANNING_TREE_HPP
#define MINIMAL_SPANNING_TREE_HPP
//--------------------------------------------------------------------------------------------------
#include "EdgeWeightedGraph.hpp"
#include "IndexedPQ.hpp"

#include <vector>
#include <queue>
#include <functional>
//--------------------------------------------------------------------------------------------------

namespace graph
{

class PrimMST_Lazy
{
public:
    using EdgeContainer = EdgeWeightedGraph::EdgeContainer;

    explicit PrimMST_Lazy(const EdgeWeightedGraph & gr);
    EdgeContainer edges() const;
private:
    std::vector<bool> marked_;
    EdgeContainer mst_;
    std::priority_queue<EdgeWeigthed, std::vector<EdgeWeigthed>, std::greater<EdgeWeigthed>> pq_;
    void visit(const EdgeWeightedGraph & gr, size_t v);
};

class PrimMST_Energy
{
public:
    using EdgeContainer = std::vector<EdgeWeigthed>;

    explicit PrimMST_Energy(const EdgeWeightedGraph & gr);
    EdgeContainer edges() const;
private:
    std::vector<bool> marked_;
    std::vector<double> distTo_;
    EdgeContainer edgeTo_;
    data_structs::IndexedPriorityQueue<double, std::greater<double>> pq_;
    void visit(const EdgeWeightedGraph & gr, size_t v);
};


class KruskalMST
{
public:
    using EdgeContainer = EdgeWeightedGraph::EdgeContainer;

    explicit KruskalMST(const EdgeWeightedGraph & gr);
    EdgeContainer edges() const;
private:
    EdgeContainer mst_;
};

} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // MINIMAL_SPANNING_TREE_HPP
//--------------------------------------------------------------------------------------------------

