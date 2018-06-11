//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   11-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef DEEPSEARCH_HPP
#define DEEPSEARCH_HPP
//--------------------------------------------------------------------------------------------------
#include "Graph.hpp"

#include <string>
#include <vector>

//--------------------------------------------------------------------------------------------------
namespace graph
{

//--------------------------------------------------------------------------------------------------
// Deep search implementation
//
class DeepFirstSearch
{
public:
    DeepFirstSearch(Graph* g, size_t s);
    bool marked(size_t v) { return marked_[v]; }
    int count() { return count_; }

private:
    std::vector<bool> marked_;
    int count_;
    void dfs(Graph* g, size_t v);
};


//--------------------------------------------------------------------------------------------------
// Finds all pathes to the concrete vertex using deep search algorithm
//
class DeepFirstPaths
{
public:
    DeepFirstPaths(Graph* g, size_t s);
    bool hasPathTo(size_t v) { return marked_[v]; }
    std::string pathTo(size_t v);

private:
    std::vector<bool> marked_;
    std::vector<size_t> edgeTo_;
    size_t s_;
    void dfs(Graph* g, size_t v);
};

} // namespace graph


//--------------------------------------------------------------------------------------------------
#endif // DEEPSEARCH_HPP
//--------------------------------------------------------------------------------------------------

