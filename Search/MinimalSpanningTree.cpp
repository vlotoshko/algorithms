//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   08-Jul-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "MinimalSpanningTree.hpp"

#include <limits>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
namespace graph
{

PrimMST_Lazy::PrimMST_Lazy(const EdgeWeightedGraph & gr)
    : marked_(gr.vertexCount(), false), pq_()
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

PrimMST_Lazy::EdgeContainer PrimMST_Lazy::edges() const
{
    return mst_;
}

void PrimMST_Lazy::visit(const EdgeWeightedGraph &gr, size_t v)
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

PrimMST_Energy::PrimMST_Energy(const EdgeWeightedGraph & gr)
    : marked_(gr.vertexCount(), false)
    , distTo_(gr.vertexCount(), std::numeric_limits<double>::max())
    , edgeTo_(gr.vertexCount()), pq_(gr.vertexCount())
{
    distTo_[0] = 0;
    pq_.push(0, 0);
    while (!pq_.empty())
    {
//        std::cout << "weight = " << pq_.top() << std::endl;
        visit(gr, pq_.pop());
    }
}

PrimMST_Energy::EdgeContainer PrimMST_Energy::edges() const
{
    return edgeTo_;
}

void PrimMST_Energy::visit(const EdgeWeightedGraph &gr, size_t v)
{
    marked_[v] = true;
    std::cout << "v = " << v << std::endl;
    for (auto e : gr[v])
    {
        size_t w = e.other(v);
        if (marked_[w])
        {
            continue;
        }

        std::cout << "w = " << w << "; distTo_[w] = " << distTo_[w] << std::endl;
        if (e.weight() < distTo_[w])
        {
            std::cout << "  w = " << w << "; weight  = " << e.weight() << std::endl;

            edgeTo_[w] = e;
            distTo_[w] = e.weight();
            pq_.push(w, distTo_[w]);
        }
    }
}


} // namespace graph
