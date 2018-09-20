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

Graph::Graph(size_t v, std::shared_ptr<IAddEdgeStrategy> strategy)
    : v_(v), e_(0), vertexes_(v), addEdge_(strategy)
{
    for (size_t i = 0; i < v_; ++i)
    {
        vertexes_[i].value = i;
    }
}

Graph::Graph(std::string fileName, std::shared_ptr<IAddEdgeStrategy> strategy)
    : e_(0), vertexes_(), addEdge_(strategy)
{
    std::ifstream file;
    file.open (fileName);

    size_t max = 0;
    size_t v = 0;
    size_t w = 0;
    while (file >> v && file >> w)
    {
        auto maxNew = std::max(std::max(v, w), max);
        if (maxNew > max)
        {
            max = maxNew;
            vertexes_.resize(max + 1);
        }
        addEdge(v, w);
    }

    size_t i = 0;
    for (auto & item : vertexes_)
    {
        item.value = i++;
    }
    v_ = vertexes_.size();
}

void Graph::addEdge(size_t v, size_t w)
{
    addEdge_->addEdge(*this, v, w);
}

void Graph::toString() const
{
    std::cout << "vertexes: " << v_ << "; edges: " << e_ << std::endl;
    for (auto const & vertex : vertexes_)
    {
        std::cout << vertex.value << ": ";
        GNode* n = vertex.next;
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
    while (n->next)
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
    // FIXME: do not multiply by 2 for the directed graph
    return 2 * g.edgeCount() / g.vertexCount();
}

int Graph::selfLoops(const Graph& g)
{
    int count = 0;
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        GNode * n = g[v].next;
        while (n)
        {
            if (n->value == v)
                ++count;
            n = n->next;
        }
    }
    // FIXME: do not divide by 2 for the directed graph
    return count / 2;
}

std::unique_ptr<Graph> Graph::reverse(const Graph & g)
{
    auto reversed = std::make_unique<Graph>(g.vertexCount(), g.addEdge_);
    for (size_t var = 0; var < g.vertexCount(); ++var)
    {

        size_t v = g[var].value;
        GNode* n = g[v].next;
        while (n)
        {
            reversed->addEdge(n->value, v);
            n = n->next;
        }
    }
    return reversed;
}

} // namespace graph
