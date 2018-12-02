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

EdgeWeightedGraph::EdgeWeightedGraph(size_t v) : v_(v), e_(0), vertexes_(v)
{
}

EdgeWeightedGraph::EdgeWeightedGraph(std::string fileName, std::shared_ptr<IDirectionStrategy> strategy)
    : e_(0), vertexes_(), directionStrategy_(std::move(strategy))
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
            vertexes_.resize(max + 1);
        }
        addEdge(Edge(v, w, weight));
    }
    v_ = vertexes_.size();
}

void EdgeWeightedGraph::addEdge(Edge e)
{
    directionStrategy_->addEdge(*this, e);
}

const EdgeWeightedGraph::EdgeContainer &EdgeWeightedGraph::operator[](size_t index) const
{
    return vertexes_[index];
}

EdgeWeightedGraph::EdgeContainer EdgeWeightedGraph::edges() const
{
    EdgeContainer ec;
    directionStrategy_->edges(*this, ec);
    return ec;
}

void EdgeWeightedGraph::toString() const
{
    std::cout << "vertexes: " << v_ << "; edges: " << e_ << std::endl;
    auto ec = edges();
    for (auto const & edge : ec)
    {
        auto v = edge.either();
        std::cout << v << "-" << edge.other(v) << " cost: " << edge.weight() << std::endl;
    }
}


void NonDirectedEWGraphStrategy::addEdge(EdgeWeightedGraph & gr, Edge e)
{
    size_t v = e.either();
    size_t w = e.other(v);
    gr.vertexes_[v].push_back(e);
    gr.vertexes_[w].push_back(e);
    ++gr.e_;
}

void NonDirectedEWGraphStrategy::edges(const EdgeWeightedGraph & gr, EdgeWeightedGraph::EdgeContainer & ec)
{
    for (size_t v = 0; v < gr.vertexCount(); ++v)
    {
        for (auto e: gr.vertexes_[v])
        {
            if(e.other(v) > v)
                ec.push_back(e);
        }
    }
}

void DirectedEWGraphStrategy::addEdge(EdgeWeightedGraph & gr, Edge e)
{
    gr.vertexes_[e.either()].push_back(e);
    ++gr.e_;
}

void DirectedEWGraphStrategy::edges(const EdgeWeightedGraph & gr, EdgeWeightedGraph::EdgeContainer & ec)
{
    for (size_t v = 0; v < gr.vertexCount(); ++v)
    {
        for (auto e: gr.vertexes_[v])
        {
            ec.push_back(e);
        }
    }
}


} // namespace graph
