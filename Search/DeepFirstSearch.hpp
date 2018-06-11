//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   11-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef DEEP_FIRST_SEARCH_HPP
#define DEEP_FIRST_SEARCH_HPP
//--------------------------------------------------------------------------------------------------
#include "Graph.hpp"

#include <string>
#include <vector>

//--------------------------------------------------------------------------------------------------
namespace graph
{

//--------------------------------------------------------------------------------------------------
// Deep firstS search implementation
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
// Finds all pathes to the concrete vertex using deep first search algorithm
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
#endif // DEEP_FIRST_SEARCH_HPP
//--------------------------------------------------------------------------------------------------

