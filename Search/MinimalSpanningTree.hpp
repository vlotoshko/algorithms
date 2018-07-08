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

#include <vector>
#include <queue>
//--------------------------------------------------------------------------------------------------

namespace graph
{


class LazyPrimMST
{
public:
    using EdgeContainer = EdgeWeightedGraph::EdgeContainer;

    LazyPrimMST(const EdgeWeightedGraph & gr);
    EdgeContainer edges() const;
private:
    std::vector<bool> marked_;
    EdgeContainer mst_;
    std::priority_queue<Edge> pq_;
    void visit(const EdgeWeightedGraph & gr, size_t v);
};


} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // MINIMAL_SPANNING_TREE_HPP
//--------------------------------------------------------------------------------------------------

