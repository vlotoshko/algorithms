//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   10-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "DeepSearch.hpp"
#include <sstream>
#include <stack>

//--------------------------------------------------------------------------------------------------

namespace graph
{

using GNode = Graph::GNode;

DeepFirstSearch::DeepFirstSearch(Graph* g, size_t s) : marked_(g->vertexes(), false)
{
    dfs(g ,s);
}

void DeepFirstSearch::dfs(Graph *g, size_t v)
{
    marked_[v] = true;
    ++count_;
    GNode* n = g->adj(v)->next;
    while(n)
    {
        if (!marked_[n->value])
        {
            std::cout << v << " - " << n->value << std::endl;
            dfs(g, n->value);
        }
        n = n->next;
    }
}


//--------------------------------------------------------------------------------------------------
//
DeepFirstPaths::DeepFirstPaths(Graph* g, size_t s)
    : marked_(g->vertexes(), false), edgeTo_(g->vertexes()), s_(s)
{
    dfs(g ,s);
}

void DeepFirstPaths::dfs(Graph *g, size_t v)
{
    marked_[v] = true;

    GNode* n = g->adj(v)->next;
    while(n)
    {
        if (!marked_[n->value])
        {
            std::cout << v << " - " << n->value << std::endl;
            edgeTo_[n->value] = v;
            dfs(g, n->value);
        }
        n = n->next;
    }
}

std::string DeepFirstPaths::pathTo(size_t v)
{
    std::stringstream pathStr;
    if(!hasPathTo(v))
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

}
