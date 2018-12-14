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

Graph::Graph(size_t v, std::shared_ptr<IDirectionStrategy> strategy)
    : v_(v), e_(0), vertexes_(v), directionStrategy_(strategy)
{
}

Graph::Graph(std::string fileName, std::shared_ptr<IDirectionStrategy> strategy)
    : e_(0), vertexes_(), directionStrategy_(strategy)
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
    v_ = vertexes_.size();
}

void Graph::addEdge(size_t v, size_t w)
{
    directionStrategy_->addEdge(*this, v, w);
}

void Graph::toString() const
{
    std::cout << "vertexes: " << v_ << "; edges: " << e_ << std::endl;
    for (size_t v = 0; v < vertexCount(); ++v)
    {
        auto const & edges = vertexes_[v];
        std::cout << v << ": ";
        for (auto const & edge : edges)
        {
            std::cout << edge.other(v) << " ";
        }
        std::cout << std::endl;
    }
}

const Graph::EdgeContainer & Graph::operator[](size_t index) const
{
    return vertexes_[index];
}

size_t Graph::degree(const Graph& g, size_t v)
{
    return g[v].size();
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
    return g.directionStrategy_->factor() * g.edgeCount() / g.vertexCount();
}

size_t Graph::selfLoops(const Graph& g)
{
    size_t count = 0;

    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            if (edge.other(v) == v)
            {
                ++count;
            }
        }
    }
    return count / g.directionStrategy_->factor();
}

std::unique_ptr<Graph> Graph::reverse(const Graph & g)
{
    auto reversed = std::make_unique<Graph>(g.vertexCount(), g.directionStrategy_);
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            reversed->addEdge(edge.other(v), v);
        }
    }
    return reversed;
}

} // namespace graph
