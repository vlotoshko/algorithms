//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   11-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef BREADTH_FIRST_SEARCH_HPP
#define BREADTH_FIRST_SEARCH_HPP
//--------------------------------------------------------------------------------------------------
#include "Graph.hpp"

#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
//--------------------------------------------------------------------------------------------------

namespace graph
{


//--------------------------------------------------------------------------------------------------
// Deep first search implementation
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
class DeepFirstPaths
{
public:
    DeepFirstPaths(const Graph & g, size_t s);
    bool hasPathTo(size_t v) const { return marked_[v]; }
    std::string pathTo(size_t v) const;

private:
    std::vector<bool> marked_;
    std::vector<size_t> edgeTo_;
    size_t s_;
    void dfs(const Graph& g, size_t v);
};


//--------------------------------------------------------------------------------------------------
// Sorts vertexes by pre, post and reversed post orders while performing dfs algorithm
//
class DepthFirstOrder
{
public:
    DepthFirstOrder(const Graph & g);
    std::stack<size_t> & reversePost() { return reversePost_; }
    std::queue<size_t> & pre() { return pre_; }
    std::queue<size_t> & post() { return post_; }
private:
    std::vector<bool> marked_;
    std::stack<size_t> reversePost_;
    std::queue<size_t> pre_;
    std::queue<size_t> post_;
    void dfs(const Graph & g, size_t v);
};


//--------------------------------------------------------------------------------------------------
// Topological sort. Applies only with directed acyclic graphs
//
class Topological
{
public:
    Topological(const Graph & g);
    std::stack<size_t> & order() { return dfo_.reversePost(); }
    bool isDAG() { return isDAG_; }
private:
    DepthFirstOrder dfo_;
    bool isDAG_;
};


//--------------------------------------------------------------------------------------------------
// Kosaraju algorithm for Strong Coupled Components - SCC.
//
class KosarajuSCC
{
public:
    KosarajuSCC(const Graph & g);
    bool stronglyConnected(size_t v, size_t w) { return id_[v] == id_[w]; }
    size_t count() { return count_; }
    size_t id(size_t v) { return id_[v]; }
private:
    size_t count_;
    std::vector<bool> marked_;
    std::vector<size_t> id_;
    void dfs(const Graph & g, size_t v);
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
    CoupledComponents(const Graph & g);
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
// Defines whether graph is cyclic or not
//
class Cyclic
{
public:
    Cyclic(const Graph & g);
    bool isCyclic() { return hasCycle_; }
private:
    bool hasCycle_;
    std::vector<bool> marked_;
    void dfs(const Graph & g, size_t v, size_t u);
};


//--------------------------------------------------------------------------------------------------
//
//
class TwoColored
{
public:
    TwoColored(const Graph& g);
    bool isBipartite() { return isTwoColors_; }
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
    SymbolGraph (std::string fileName);
    ~SymbolGraph();
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
#endif // BREADTH_FIRST_SEARCH_HPP
//--------------------------------------------------------------------------------------------------

