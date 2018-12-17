//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   05-Nov-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "ShortPathes.hpp"

#include <limits>
//--------------------------------------------------------------------------------------------------


namespace graph
{

ShortPathes::ShortPathes(const EdgeWeightedGraph & gr, size_t s) :
    distTo_(gr.vertexCount(), std::numeric_limits<double>::max()),
    edgeTo_(gr.vertexCount(), EdgeWeighted{})
{
    distTo_[s] = 0;
}

double ShortPathes::distTo(size_t v) const
{
    return distTo_[v];
}

bool ShortPathes::hasPathTo(size_t v) const
{
    return distTo_[v] < std::numeric_limits<double>::max();
}

ShortPathes::EdgeContainer ShortPathes::pathTo(size_t v) const
{
    ShortPathes::EdgeContainer edges;

    if (hasPathTo(v))
    {
        for(EdgeWeighted e = edgeTo_[v]; e != EdgeWeighted{}; e = edgeTo_[e.either()])
        {
            edges.push_back(e);
        }
    }
    return edges;
}

void ShortPathes::relax(const EdgeWeightedGraph & gr, size_t v)
{
    for (auto edge : gr[v])
    {
        size_t w = edge.other(v);
        if (distTo_[w] > distTo_[v] + edge.weight())
        {
            distTo_[w] = distTo_[v] + edge.weight();
            edgeTo_[w] = edge;
        }
    }
}

DijkstraSP::DijkstraSP(const EdgeWeightedGraph & gr, size_t s)
    : ShortPathes(gr ,s), pq_(gr.vertexCount())
{
    pq_.push(s, 0);

    while (!pq_.empty())
    {
        relax(gr, pq_.pop());
    }
}

void DijkstraSP::relax(const EdgeWeightedGraph & gr, size_t v)
{
    for (auto edge : gr[v])
    {
        size_t w = edge.other(v);
        if (distTo_[w] > distTo_[v] + edge.weight())
        {
            distTo_[w] = distTo_[v] + edge.weight();
            edgeTo_[w] = edge;
            pq_.push(w, distTo_[w]);
        }
    }
}

DijkstraAllPairsSP::DijkstraAllPairsSP(const EdgeWeightedGraph & gr)
{
    all_.reserve(gr.vertexCount());
    for (size_t v = 0; v < gr.vertexCount(); ++v)
    {
        all_.push_back(DijkstraSP{gr, v});
    }
}

double DijkstraAllPairsSP:: distTo(size_t s, size_t t)    const
{
    return all_[s].distTo(t);
}

DijkstraAllPairsSP::EdgeContainer DijkstraAllPairsSP::pathTo(size_t s, size_t t) const
{
    return all_[s].pathTo(t);
}

AcyclicSP::AcyclicSP(const EdgeWeightedGraph & gr, size_t s) : ShortPathes (gr, s)
{
    distTo_[s] = 0;
//    TopologicalEWG top(gr);

//    for (auto vertex : top.order())
//    {
//        relax(gr, vertex);
//    }
}


} // namespace graph
