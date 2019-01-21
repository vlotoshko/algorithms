//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   05-Nov-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "ShortPathes.hpp"
#include "GraphAlgorithms.hpp"

#include <limits>
//--------------------------------------------------------------------------------------------------


namespace graph
{

char const * DijkstraSP::name = "DijkstraSP";
char const * AcyclicSP::name = "AcyclicSP";
char const * AcyclicLP::name = "AcyclicLP";


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
    for (const auto & edge : gr[v])
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
        all_.emplace_back(gr, v);
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

AcyclicSP::AcyclicSP(const EdgeWeightedGraph & gr, size_t s) : ShortPathes(gr, s)
{
    distTo_[s] = 0;
    graph::Topological<EdgeWeightedGraph> top(gr);

    auto edges = top.order();
    auto getItem = [&edges] (size_t & item)
    {
        if (edges.empty())
        {
            return false;
        }

        item = edges.top();
        edges.pop();
        return true;
    };

    size_t vertex = 0;
    while(getItem(vertex))
    {
        relax(gr, vertex);
    }
}

AcyclicLP::AcyclicLP(const EdgeWeightedGraph & gr, size_t s) : LongPathes(gr, s)
{
    distTo_[s] = 0;
    graph::Topological<EdgeWeightedGraph> top(gr);

    auto edges = top.order();
    auto getItem = [&edges] (size_t & item)
    {
        if (edges.empty())
        {
            return false;
        }

        item = edges.top();
        edges.pop();
        return true;
    };

    size_t vertex = 0;
    while(getItem(vertex))
    {
        relax(gr, vertex);
    }
}

} // namespace graph
