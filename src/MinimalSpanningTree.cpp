/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 08-Jul-2018
 */

// -------------------------------------------------------------------------------------------------
#include "MinimalSpanningTree.hpp"
#include "UnionFind.hpp"

#include <limits>
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
namespace graph
{

char const * PrimMST_Lazy::name = "PrimMST_Lazy";
char const * PrimMST_Energy::name = "PrimMST_Energy";
char const * KruskalMST::name = "KruskalMST";

PrimMST_Lazy::PrimMST_Lazy(const EdgeWeightedGraph & gr)
    : marked_(gr.vertexCount(), false)
{
    visit(gr, 0); // Suppose graph is coupled

    while (!pq_.empty())
    {
        EdgeWeighted e = pq_.top();
        pq_.pop();

        size_t v = e.either();
        size_t w = e.other(v);

        if (marked_[v] && marked_[w])
        {
            continue;
        }
        mst_.push_back(e);

        if (!marked_[v])
        {
            visit(gr, v);
        }

        if (!marked_[w])
        {
            visit(gr, w);
        }
    }
}

PrimMST_Lazy::EdgeContainer PrimMST_Lazy::edges() const
{
    return mst_;
}

void PrimMST_Lazy::visit(const EdgeWeightedGraph & gr, const size_t & v)
{
    marked_[v] = true;
    for (const auto & e : gr[v])
    {
        if (!marked_[e.other(v)])
        {
            pq_.push(e);
        }
    }
}

PrimMST_Energy::PrimMST_Energy(const EdgeWeightedGraph & gr)
    : marked_(gr.vertexCount(), false)
    , distTo_(gr.vertexCount(), std::numeric_limits<double>::max())
    , edgeTo_(gr.vertexCount()), pq_(gr.vertexCount())
{
    distTo_[0] = 0;
    pq_.push(0, 0);
    while (!pq_.empty())
    {
        visit(gr, pq_.pop());
    }
}

PrimMST_Energy::EdgeContainer PrimMST_Energy::edges() const
{
    return edgeTo_;
}

void PrimMST_Energy::visit(const EdgeWeightedGraph & gr, const size_t & v)
{
    marked_[v] = true;
    for (const auto & e : gr[v])
    {
        size_t w = e.other(v);
        if (marked_[w])
        {
            continue;
        }
        if (e.weight() < distTo_[w])
        {
            edgeTo_[w] = e;
            distTo_[w] = e.weight();
            pq_.push(w, distTo_[w]);
        }
    }
}


KruskalMST::KruskalMST(const EdgeWeightedGraph & gr)
{
    EdgeContainer edges;
    NonDirectedGraphPolicy<EdgeWeightedGraph>::edges(gr, edges);
    uf::UnionFindInfo<size_t> unionFindInfo(edges.size());
    uf::UnionFind_QuickFind<size_t> uf;

    std::priority_queue<EdgeWeighted, std::vector<EdgeWeighted>, std::greater<>> edgePQ;
    for (const auto & item : edges)
    {
        edgePQ.push(item);
    }

    while (!edgePQ.empty() && mst_.size() < gr.vertexCount() - 1)
    {
        EdgeWeighted e = edgePQ.top();
        edgePQ.pop();

        auto v = e.either();
        auto w = e.other(v);
        if (uf.connected(unionFindInfo, v, w))
        {
            continue;
        }
        uf.unionComponents(unionFindInfo, v, w);
        mst_.push_back(e);
    }
}

KruskalMST::EdgeContainer KruskalMST::edges() const
{
    return mst_;
}

} // namespace graph
