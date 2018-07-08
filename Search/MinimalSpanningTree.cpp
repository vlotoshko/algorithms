//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   08-Jul-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "MinimalSpanningTree.hpp"
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
namespace graph
{

LazyPrimMST::LazyPrimMST(const EdgeWeightedGraph & gr)
    : marked_(gr.vertexCount())
{
    visit(gr, 0); // Suppose graph is coupled

    while (!pq_.empty())
    {
        Edge e = pq_.top();
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

LazyPrimMST::EdgeContainer LazyPrimMST::edges() const
{
    return mst_;
}

void LazyPrimMST::visit(const EdgeWeightedGraph &gr, size_t v)
{
    marked_[v] = true;
    for (auto e : gr[v])
    {
        if (!marked_[e.other(v)])
        {
            pq_.push(e);
        }
    }
}



} // namespace graph
