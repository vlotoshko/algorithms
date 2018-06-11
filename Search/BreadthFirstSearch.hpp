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

//--------------------------------------------------------------------------------------------------
namespace graph
{


//--------------------------------------------------------------------------------------------------
// Finds all pathes to the concrete vertex using breadth first search algorithm
//
class BreadthFirstPaths
{
public:
    BreadthFirstPaths(Graph* g, size_t s);
    bool hasPathTo(size_t v) { return marked_[v]; }
    std::string pathTo(size_t v);

private:
    std::vector<bool> marked_;
    std::vector<size_t> edgeTo_;
    size_t s_;
    void bfs(Graph* g, size_t v);
};

} // namespace graph


//--------------------------------------------------------------------------------------------------
#endif // BREADTH_FIRST_SEARCH_HPP
//--------------------------------------------------------------------------------------------------

