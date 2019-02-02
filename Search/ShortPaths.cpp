//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   05-Nov-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "ShortPaths.hpp"
#include "GraphAlgorithms.hpp"

#include <limits>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
namespace graph
{

char const * DijkstraSP::name = "DijkstraSP";
char const * AcyclicShortPaths::name = "AcyclicShortPaths";
char const * AcyclicLongPaths::name = "AcyclicLongPaths";


DijkstraSP::DijkstraSP(const EdgeWeightedGraph & gr, size_t s)
    : ShortPaths(gr ,s), pq_(gr.vertexCount())
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

AcyclicShortPaths::AcyclicShortPaths(const EdgeWeightedGraph & gr, size_t s) : ShortPaths(gr, s)
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

AcyclicLongPaths::AcyclicLongPaths(const EdgeWeightedGraph & gr, size_t s) : LongPaths(gr, s)
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


AcyclicLongPaths criticalPathMethod(const ContinuousJobs &jobs)
{
    using Strategy = graph::DirectedGraphPolicy<graph::EdgeWeightedGraph>;
    using Edge = graph::EdgeWeightedGraph::EdgeType;

    auto n = jobs.size();
    auto s = n * 2;
    auto t = n * 2 + 1;
    EdgeWeightedGraph graph = graph::EdgeWeightedGraph(n * 2 + 2);

    for (size_t i = 0; i < n; ++i)
    {
        Strategy::addEdge(graph, Edge{i, i+n, jobs[i].duration});
        Strategy::addEdge(graph, Edge{s, i, 0.0});
        Strategy::addEdge(graph, Edge{i+n, t, 0.0});
        for (auto jobIndex : jobs[i].dependentJobs)
        {
            Strategy::addEdge(graph, Edge{i+n, jobIndex, 0.0});
        }
    }

    return AcyclicLongPaths(graph, s);
}

} // namespace graph
