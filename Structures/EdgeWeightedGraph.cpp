//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   04-Jul-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "EdgeWeightedGraph.hpp"

#include <fstream>
#include <stack>
#include <queue>

//--------------------------------------------------------------------------------------------------
namespace graph
{

EdgeWeightedGraph::EdgeWeightedGraph(size_t v) : v_(v), e_(0), edges_(v)
{
}

EdgeWeightedGraph::EdgeWeightedGraph(std::string fileName, std::unique_ptr<IAddEdgeStrategy> strategy)
    : e_(0), edges_(), addEdge_(std::move(strategy))
{
    std::ifstream file;
    file.open (fileName);

    size_t max = 0;
    size_t v = 0;
    size_t w = 0;
    double weight = 0;
    while (file >> v && file >> w && file >> weight)
    {
        auto maxNew = std::max(std::max(v, w), max);
        if (maxNew > max)
        {
            max = maxNew;
            edges_.resize(max + 1);
        }
        addEdge(Edge(v, w, weight));
    }
}

void EdgeWeightedGraph::addEdge(Edge e)
{
    addEdge_->addEdge(*this, e);
}

const EdgeWeightedGraph::EdgeContainer &EdgeWeightedGraph::operator[](size_t index) const
{
    return edges_[index];
}

EdgeWeightedGraph::EdgeContainer EdgeWeightedGraph::edges() const
{
    EdgeContainer ec;
    for (size_t v = 0; v < v_; ++v)
    {
        for(auto e: edges_[v])
        {
            if(e.other(v) > v)
                ec.push_back(e);
        }
    }

    return ec;
}

void EdgeWeightedGraph::toString() const
{
    std::string s;

    std::cout << "vertexes: " << v_ << "; edges: " << e_ << std::endl;
    for (auto const & edgelist : edges_)
    {
        for (auto const & edge: edgelist)
        {
            auto v = edge.either();
            std::cout << v << " - " << edge.other(v) << edge.weight() << std::endl;
        }
        std::cout << std::endl;
    }
}


} // namespace graph
