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

namespace graph
{

struct IDirectionStrategy;

// FIXME: description is not actual
//--------------------------------------------------------------------------------------------------
// Graph structure. Containes array of vertexes, where vertex V is a node and the value of the node
// is an index of vertex connected with V. All other vertexes connected with V adds to the node
// as linked list.
//
class Graph
{
public:
    using EdgeContainer = std::list<Edge>;

    Graph(size_t v, std::shared_ptr<IDirectionStrategy> strategy);
    Graph (std::string fileName, std::shared_ptr<IDirectionStrategy> strategy);

    size_t vertexCount() const { return v_; }
    size_t edgeCount()   const { return e_; }
    void   toString()    const;

    void   addEdge(size_t v, size_t w);
    const EdgeContainer& operator[] (size_t index) const;

    static size_t degree(const Graph& g, size_t v);
    static size_t maxDegree(const Graph& g);
    static size_t avgDegree(const Graph& g);
    static size_t selfLoops(const Graph& g);
    static std::unique_ptr<Graph> reverse(const Graph& g);

protected:
    friend struct NonDirectedGraphStrategy;
    friend struct DirectedGraphStrategy;
    size_t v_;
    size_t e_;
    std::vector<EdgeContainer> vertexes_;
    std::shared_ptr<IDirectionStrategy> directionStrategy_;
};

struct IDirectionStrategy
{
    virtual void addEdge(Graph & gr, size_t v, size_t w) = 0;
    virtual size_t factor() const = 0;
    virtual ~IDirectionStrategy() = default;
};

struct NonDirectedGraphStrategy : public IDirectionStrategy
{
    void addEdge(Graph & gr, size_t v, size_t w) override
    {
        gr.vertexes_[v].emplace_back(v, w);
        gr.vertexes_[w].emplace_back(w, v);
        ++gr.e_;
    }
    size_t factor() const override { return 2; }
};

struct DirectedGraphStrategy : public IDirectionStrategy
{
    void addEdge(Graph & gr, size_t v, size_t w) override
    {
        gr.vertexes_[v].emplace_back(v, w);
        ++gr.e_;
    }
    size_t factor() const override { return 1; }
};

} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_HPP
//--------------------------------------------------------------------------------------------------

