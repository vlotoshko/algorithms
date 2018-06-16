//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   10-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Graph.hpp"

#include <fstream>
#include <stack>
#include <queue>

//--------------------------------------------------------------------------------------------------
namespace graph
{

Graph::Graph(size_t v) : v_(v), e_(0), adj_(v)
{
    for (size_t i = 0; i < v_; ++i)
    {
        adj_[i].value = i;
    }
}

Graph::Graph(std::string fileName) : e_(0)
{
    std::ifstream file;
    file.open (fileName);
    file >> v_;

    adj_ = std::vector<GNode>(v_);
    size_t i = 0;
    for (auto & item : adj_)
    {
        item.value = i++;
    }

    size_t v;
    size_t w;
    while (file >> v && file >> w)
    {
        addEdge(v, w);
    }
}

void Graph::addEdge(size_t v, size_t w)
{
    adj_[v].add(new GNode(w));
    adj_[w].add(new GNode(v));
    ++e_;
}

const Graph::GNode *Graph::adj(size_t v) const
{
    return &adj_[v];
}

void Graph::toString() const
{
    std::string s;

    std::cout << "vertex: " << v_ << "; edges: " << e_ << std::endl;
    for (size_t var = 0; var < vertexes(); var++)
    {
        std::cout << adj(var)->value << ": ";
        GNode* n = adj(var)->next;
        while (n)
        {
            std::cout << n->value << " ";
            n = n->next;
        }
        std::cout << std::endl;
    }
}


size_t Graph::degree(const Graph *g, size_t v)
{
    size_t degree = 0;
    const GNode * n = g->adj(v);
    while(n->next)
    {
        ++degree;
        n = n->next;
    }
    return degree;
}

size_t Graph::maxDegree(const Graph *g)
{
    size_t max = 0;
    for (size_t i = 0; i < g->vertexes(); ++i)
    {
        size_t d = degree(g, i);
        if (d > max)
            max = d;
    }
    return max;
}

size_t Graph::avgDegree(const Graph *g)
{
    return 2 * g->edges() / g->vertexes();
}

int Graph::selfLoops(const Graph *g)
{
    int count = 0;
    for (size_t v = 0; v < g->vertexes(); ++v)
    {
        GNode* n = g->adj(v)->next;
        while(n)
        {
            if (n->value == v)
                ++count;
            n = n->next;
        }
    }
    return count / 2;
}

} // namespace graph
