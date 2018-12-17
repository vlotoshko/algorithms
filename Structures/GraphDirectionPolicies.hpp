//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   10-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef GRAPH_DIRECTION_POLICIES_HPP
#define GRAPH_DIRECTION_POLICIES_HPP
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#include <stddef.h>
//-------------------------------------------------------------------------------------------------

namespace graph
{
template<typename G>
struct NonDirectedGraphPolicy
{
    static void addEdge(G & gr, size_t v, size_t w)
    {
        gr.vertexes_[v].emplace_back(v, w);
        gr.vertexes_[w].emplace_back(w, v);
        ++gr.e_;
    }

    static void addEdge(G & gr, typename G::EdgeType e)
    {
        size_t v = e.either();
        size_t w = e.other(v);
        gr.vertexes_[v].push_back(e);
        gr.vertexes_[w].push_back(e);
        ++gr.e_;
    }

    static void edges(const G & gr, typename G::EdgeContainer & edges)
    {
        for (size_t v = 0; v < gr.vertexCount(); ++v)
        {
            for (auto e: gr.vertexes_[v])
            {
                if(e.other(v) > v)
                    edges.push_back(e);
            }
        }
    }

    static inline size_t factor() { return 2; }
};

template<typename G>
struct DirectedGraphPolicy
{
    static void addEdge(G & gr, size_t v, size_t w)
    {
        gr.vertexes_[v].emplace_back(v, w);
        ++gr.e_;
    }

    static void addEdge(G & gr, typename G::EdgeType e)
    {
        gr.vertexes_[e.either()].push_back(e);
        ++gr.e_;
    }

    static void edges(const G & gr, typename G::EdgeContainer & edges)
    {
        for (size_t v = 0; v < gr.vertexCount(); ++v)
        {
            for (auto e: gr.vertexes_[v])
            {
                edges.push_back(e);
            }
        }
    }

    static inline size_t factor() { return 1; }
};

} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_DIRECTION_POLICIES_HPP
//--------------------------------------------------------------------------------------------------

