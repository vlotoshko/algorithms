//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   11-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP
//--------------------------------------------------------------------------------------------------
#include "Graph.hpp"

#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <sstream>
#include <functional>
//--------------------------------------------------------------------------------------------------

namespace graph
{

template<typename G>
void toString(const G & g)
{
    std::cout << "vertexes: " << g.vertexCount() << "; edges: " << g.edgeCount() << std::endl;
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        auto const & edges = g[v];
        std::cout << v << ": ";
        for (auto const & edge : edges)
        {
            std::cout << edge.other(v) << " ";
        }
        std::cout << std::endl;
    }
}

template<typename G>
size_t degree   (const G & g, size_t v) { return g[v].size(); }

template<typename G>
size_t maxDegree(const G & g)
{
    size_t max = 0;
    for (size_t i = 0; i < g.vertexCount(); ++i)
    {
        size_t d = degree(g, i);
        if (d > max)
            max = d;
    }
    return max;
}

template<typename Strategy, typename G>
size_t avgDegree(const G & g) { return Strategy::factor() * g.edgeCount() / g.vertexCount(); }

template<typename Strategy, typename G>
size_t selfLoops(const G & g)
{
    size_t count = 0;

    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            if (edge.other(v) == v)
            {
                ++count;
            }
        }
    }
    return count / Strategy::factor();
}

template<typename Strategy, typename G>
std::unique_ptr<G> reverse(const G & g)
{
    auto reversed = std::make_unique<Graph>(g.vertexCount());
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            Strategy::addEdge(*reversed, edge.other(v), v);
        }
    }
    return reversed;
}


//--------------------------------------------------------------------------------------------------
// ------- DeepFirstSearch implementation -----------------------------------------------
//
template<typename G>
size_t deepFirstSearh(const G & g, size_t s)
{
    std::vector<bool> marked(g.vertexCount(), false);
    size_t count = 0;

    std::function<void(const G & g, size_t s)> dfs;
    dfs = [&marked, &count, &dfs](const G & g, size_t v) -> void {
        marked[v] = true;
        ++count;
        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            auto w = edge.other(v);
            if (!marked[w])
            {
    //            std::cout << v << " - " << w << std::endl;
                dfs(g, w);
            }
        }
    };

    dfs(g, s);
    return count;
}

//--------------------------------------------------------------------------------------------------
// ------- DeepFirstSearch as class -----------------------------------------------
//
class DeepFirstSearch
{
public:
    DeepFirstSearch(const Graph & g, size_t s);
    bool marked(size_t v) const { return marked_[v]; }
    int count() const { return count_; }

private:
    std::vector<bool> marked_;
    int count_;
    void dfs(const Graph & g, size_t v);
};


//--------------------------------------------------------------------------------------------------
// Finds all pathes to the concrete vertex using deep first search algorithm
//
template<typename G>
class DeepFirstPaths
{
public:
    DeepFirstPaths(const G & g, size_t s)
        : marked_(g.vertexCount(), false), edgeTo_(g.vertexCount()), s_(s)
    {
        dfs(g ,s);
    }
    bool hasPathTo(size_t v) const { return marked_[v]; }
    std::string pathTo(size_t v) const
    {
        std::stringstream pathStr;
        if (!hasPathTo(v))
        {
            pathStr << "none";
            return pathStr.str();
        }

        std::stack<size_t> path;

        for (size_t i = v; i != s_; i = edgeTo_[i])
        {
            path.push(i);
        }
        path.push(s_);

        while (!path.empty())
        {
           pathStr << path.top();
           path.pop();
           pathStr << (!path.empty() ? " - " : "");
        }
        return pathStr.str();
    }

private:
    std::vector<bool> marked_;
    std::vector<size_t> edgeTo_;
    size_t s_;
    void dfs(const Graph& g, size_t v)
    {
        marked_[v] = true;

        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            auto w = edge.other(v);
            if (!marked_[w])
            {
    //            std::cout << v << " - " <<w << std::endl;
                edgeTo_[w] = v;
                dfs(g, w);
            }
        }
    }
};


//--------------------------------------------------------------------------------------------------
// Sorts vertexes by pre, post and reversed post orders while performing dfs algorithm
//
template<typename G>
class DepthFirstOrder
{
public:
    explicit DepthFirstOrder(const G & g)
        : marked_(g.vertexCount(), false)
        , reversePost_(), pre_(), post_()
      {

          for (size_t v = 0; v < g.vertexCount(); ++v)
          {
              if (!marked_[v])
                  dfs(g, v);
          }
      }
    std::stack<size_t> & reversePost() { return reversePost_; }
    std::queue<size_t> & pre() { return pre_; }
    std::queue<size_t> & post() { return post_; }
private:
    std::vector<bool> marked_;
    std::stack<size_t> reversePost_;
    std::queue<size_t> pre_;
    std::queue<size_t> post_;
    void dfs(const G & g, size_t v)
    {
        marked_[v] = true;
        pre_.push(v);

        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            auto w = edge.other(v);
            if (!marked_[w])
            {
                dfs(g, w);
            }
        }

        post_.push(v);
        reversePost_.push(v);
    }
};

//--------------------------------------------------------------------------------------------------
// Defines whether graph is cyclic or not
//

template<typename G>
class Cyclic
{
public:
    explicit Cyclic(const G & g) : hasCycle_(false), marked_(g.vertexCount(), false)
    {
        for (size_t s = 0; s < g.vertexCount(); ++s)
        {
           if(!marked_[s])
               dfs(g ,s, s);
        }
    }
    bool isCyclic() const { return hasCycle_; }
private:
    bool hasCycle_;
    std::vector<bool> marked_;
    void dfs(const G & g, size_t v, size_t u)
    {
        marked_[v] = true;
        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            auto w = edge.other(v);
            if (!marked_[w])
            {
                dfs(g, w, v);
            }
            else if (w != u)
            {
                hasCycle_ = true;
            }
        }
    }
};


//--------------------------------------------------------------------------------------------------
// Topological sort. Applies only with directed acyclic graphs
//
template<typename G>
class Topological
{
public:
    explicit Topological(const G & g) : dfo_(G(0)), isDAG_(false)
    {
        isDAG_ = !Cyclic<G>(g).isCyclic();
        if (isDAG_)
        {
            dfo_ = DepthFirstOrder<G>(g);
        }
    }

    std::stack<size_t> & order() { return dfo_.reversePost(); }
    bool isDAG() const { return isDAG_; }
private:
    DepthFirstOrder<G> dfo_;
    bool isDAG_;
};


//--------------------------------------------------------------------------------------------------
// Kosaraju algorithm for Strong Coupled Components - SCC.
//
template<typename G>
class KosarajuSCC
{
public:
    explicit KosarajuSCC(const G & g) : count_(0), marked_(g.vertexCount(), false), id_(g.vertexCount())
    {
        auto r = reverse<DirectedGraphStrategy<G>>(g);
        DepthFirstOrder<G> order(*r);

        while (order.reversePost().size() > 0)
        {
            size_t i = order.reversePost().top();
            if (!marked_[i])
            {
                dfs(g, i);
                ++count_;
            }
            order.reversePost().pop();
        }
    }
    bool stronglyConnected(size_t v, size_t w) const { return id_[v] == id_[w]; }
    size_t count() const { return count_; }
    size_t id(size_t v) const { return id_[v]; }
private:
    size_t count_;
    std::vector<bool> marked_;
    std::vector<size_t> id_;
    void dfs(const G & g, size_t v)
    {
        marked_[v] = true;
        id_[v] = count_;

        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            auto w = edge.other(v);
            if (!marked_[w])
            {
                dfs(g, w);
            }
        }
    }
};


//--------------------------------------------------------------------------------------------------
// TransitiveClosure
//
class TransitiveClosure
{
public:
    explicit TransitiveClosure(const Graph & g);
    ~TransitiveClosure();
    bool reachable(size_t v, size_t w);
private:
    std::vector<DeepFirstSearch *> vDFS_;
};


//--------------------------------------------------------------------------------------------------
// Finds all pathes to the concrete vertex using breadth first search algorithm
//
class BreadthFirstPaths
{
public:
    BreadthFirstPaths(const Graph & g, size_t s);
    bool hasPathTo(size_t v) const { return marked_[v]; }
    std::string pathTo(size_t v) const;

private:
    std::vector<bool> marked_;
    std::vector<size_t> edgeTo_;
    size_t s_;
    void bfs(const Graph & g, size_t v);
};


//--------------------------------------------------------------------------------------------------
// Analizes graph for coupled components.
//
class CoupledComponents
{
public:
    explicit CoupledComponents(const Graph & g);
    bool connected(size_t v, size_t w) const { return id_[v] == id_[w]; }
    size_t componentsCount() const { return count_; }
    size_t id(size_t v) const { return id_[v]; }

private:
    size_t count_;
    std::vector<bool> marked_;
    std::vector<size_t> id_;
    void dfs(const Graph & g, size_t v);
};





//--------------------------------------------------------------------------------------------------
//
//
class TwoColored
{
public:
    explicit TwoColored(const Graph& g);
    bool isBipartite() const { return isTwoColors_; }
private:
    bool isTwoColors_;
    std::vector<bool> marked_;
    std::vector<bool> colors_;
    void dfs(const Graph& g, size_t v);
};


//--------------------------------------------------------------------------------------------------
//
//
class SymbolGraph
{
public:
    explicit SymbolGraph(std::string fileName);
    ~SymbolGraph();

    SymbolGraph(const SymbolGraph&) = delete;
    SymbolGraph& operator= (const SymbolGraph&) = delete;

    Graph& G() const { return *g_; }
    bool contains(std::string key) const;
    int index(std::string key) const;
    std::string name(size_t index) const;
    std::string lexical(size_t index) const;
private:
    std::map<std::string, size_t> st_;
    std::vector<std::string> keys_;
    Graph* g_;
};


} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_ALGORITHMS_HPP
//--------------------------------------------------------------------------------------------------

