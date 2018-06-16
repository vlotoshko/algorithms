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
//--------------------------------------------------------------------------------------------------

namespace graph
{

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
// Analizes graph for coupled components. Uncoupled components can be processing simultaneously
// in the different threads.
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

