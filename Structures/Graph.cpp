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

Graph::Graph(size_t v) : v_(v), e_(0), vertexes_(v)
{
    for (size_t i = 0; i < v_; ++i)
    {
        vertexes_[i].value = i;
    }
}

Graph::Graph(std::string fileName) : e_(0)
{
    std::ifstream file;
    file.open (fileName);
    file >> v_;

    vertexes_ = std::vector<GNode>(v_);
    size_t i = 0;
    for (auto & item : vertexes_)
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
    vertexes_[v].add(new GNode(w));
    vertexes_[w].add(new GNode(v));
    ++e_;
}

//const Graph::GNode *Graph::adj(size_t v) const
//{
//    return &vertexes_[v];
//}

void Graph::toString() const
{
    std::string s;

    std::cout << "vertex: " << v_ << "; edges: " << e_ << std::endl;
    for (size_t var = 0; var < vertexCount(); var++)
    {
        std::cout << operator[](var).value << ": ";
        GNode* n = operator[](var).next;
        while (n)
        {
            std::cout << n->value << " ";
            n = n->next;
        }
        std::cout << std::endl;
    }
}

const Graph::GNode & Graph::operator[](size_t index) const
{
    return vertexes_[index];
}


size_t Graph::degree(const Graph& g, size_t v)
{
    size_t degree = 0;
    const GNode * n = &g[v];
    while(n->next)
    {
        ++degree;
        n = n->next;
    }
    return degree;
}

size_t Graph::maxDegree(const Graph& g)
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

size_t Graph::avgDegree(const Graph & g)
{
    return 2 * g.edgeCount() / g.vertexCount();
}

int Graph::selfLoops(const Graph& g)
{
    int count = 0;
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        GNode * n = g[v].next;
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
