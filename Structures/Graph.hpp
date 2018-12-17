//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   10-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef GRAPH_HPP
#define GRAPH_HPP
//--------------------------------------------------------------------------------------------------
#include "Edge.hpp"

#include <list>
#include <vector>
#include <memory>
#include <fstream>

namespace graph
{


template<typename G>
struct NonDirectedGraphStrategy
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
struct DirectedGraphStrategy
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

template <typename Edge = EdgeNonWeighted>
class GraphT
{
public:
    using EdgeType = EdgeNonWeighted;
    using EdgeContainer = std::list<Edge>;

    explicit GraphT(size_t v) : v_(v), e_(0), vertexes_(v) {}

    template<typename Strategy>
    GraphT (Strategy, std::string fileName)
    {
        std::ifstream file;
        file.open (fileName);

        size_t max = 0;
        size_t v = 0;
        size_t w = 0;
        while (file >> v && file >> w)
        {
            auto maxNew = std::max(std::max(v, w), max);
            if (maxNew > max)
            {
                max = maxNew;
                vertexes_.resize(max + 1);
            }
            Strategy::addEdge(*this, v, w);
        }
        v_ = vertexes_.size();
    }

    size_t vertexCount() const { return v_; }
    size_t edgeCount()   const { return e_; }
    const  EdgeContainer& operator[] (size_t index) const { return vertexes_[index]; }
protected:
    friend struct NonDirectedGraphStrategy<GraphT>;
    friend struct DirectedGraphStrategy<GraphT>;
    size_t v_;
    size_t e_;
    std::vector<EdgeContainer> vertexes_;
};

using Graph             = GraphT<EdgeNonWeighted>;
using EdgeWeightedGraph = GraphT<EdgeWeigthed>;


} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_HPP
//--------------------------------------------------------------------------------------------------

