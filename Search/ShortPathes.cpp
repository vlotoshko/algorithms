//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   05-Nov-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "ShortPathes.hpp"

#include <limits>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
namespace graph
{

ShortPathes::ShortPathes(const EdgeWeightedGraph & gr, size_t s) :
    distTo_(gr.vertexCount(), std::numeric_limits<double>::max()),
    edgeTo_(gr.vertexCount(), EdgeWeigthed{})
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
        for(EdgeWeigthed e = edgeTo_[v]; e != EdgeWeigthed{}; e = edgeTo_[e.either()])
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
    TopologicalEWG top(gr);

//    for (auto vertex : top.order())
//    {
//        relax(gr, vertex);
//    }
}

//--------------------------------------------------------------------------------------------------
// ------- DepthFirstOrder ----------------------------------------------------
//

DepthFirstOrderEWG::DepthFirstOrderEWG(const EdgeWeightedGraph & g)
  : marked_(g.vertexCount(), false)
  , reversePost_(), pre_(), post_()
{

    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        if (!marked_[v])
            dfs(g, v);
    }
}


void DepthFirstOrderEWG::dfs(const EdgeWeightedGraph & g, size_t v)
{
    marked_[v] = true;
    pre_.push(v);

//    Node<size_t>* n = g[v].next;
//    while (n)
//    {
//        if (!marked_[n->value])
//        {
//            dfs(g, n->value);
//        }
//        n = n->next;
//    }
//    post_.push(v);
//    reversePost_.push(v);
}


//--------------------------------------------------------------------------------------------------
// ------- TopologicalEWG ----------------------------------------------------
//

TopologicalEWG::TopologicalEWG(const EdgeWeightedGraph & g)
    : dfo_(EdgeWeightedGraph(0)), isDAG_(false)
{
    isDAG_ = !CyclicEWG(g).isCyclic();
    if (isDAG_)
    {
        dfo_ = DepthFirstOrderEWG(g);
    }
}

//--------------------------------------------------------------------------------------------------
// ------- CyclicEWG -----------------------------------------------------------------
//

CyclicEWG::CyclicEWG(const EdgeWeightedGraph & g) : hasCycle_(false), marked_(g.vertexCount(), false)
{
    for (size_t s = 0; s < g.vertexCount(); ++s)
    {
       if(!marked_[s])
           dfs(g ,s, s);
    }
}

void CyclicEWG::dfs(const EdgeWeightedGraph & g, size_t v, size_t u)
{
    marked_[v] = true;

//    GNode* n = g[v].next;
//    while (n)
//    {
//        if (!marked_[n->value])
//        {
//            dfs(g, n->value, v);
//        }
//        else if (n->value != u)
//        {
//            hasCycle_ = true;
//        }
//        n = n->next;
//    }
}

} // namespace graph
