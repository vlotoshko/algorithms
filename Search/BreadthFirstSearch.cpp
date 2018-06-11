//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   11-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "BreadthFirstSearch.hpp"
#include <sstream>
#include <queue>
#include <stack>

//--------------------------------------------------------------------------------------------------

namespace graph
{
using GNode = Graph::GNode;

BreadthFirstPaths::BreadthFirstPaths(Graph* g, size_t s)
    : marked_(g->vertexes(), false), edgeTo_(g->vertexes()), s_(s)
{
    bfs(g ,s);
}

void BreadthFirstPaths::bfs(Graph *g, size_t v)
{
    marked_[v] = true;
    std::queue<size_t> queue;
    queue.push(v);

    while (!queue.empty())
    {
        size_t x = queue.front();
        queue.pop();
        GNode* n = g->adj(x)->next;

        while(n)
        {
            if (!marked_[n->value])
            {
                std::cout << x << " - " << n->value << std::endl;
                edgeTo_[n->value] = x;
                marked_[n->value] = true;
                queue.push(n->value);
            }
            n = n->next;
        }
    }
}

std::string BreadthFirstPaths::pathTo(size_t v)
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
