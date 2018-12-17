//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   10-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef GRAPH_HPP
#define GRAPH_HPP
//--------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#include "Edge.hpp"
#include "GraphDirectionPolicies.hpp"

#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
//-------------------------------------------------------------------------------------------------


namespace graph
{

template <typename Edge = EdgeNonWeighted>
class GraphT
{
public:
    using EdgeType = EdgeNonWeighted;
    using EdgeContainer = std::list<Edge>;

    explicit GraphT(size_t v) : v_(v), e_(0), vertexes_(v) {}

    template<typename Strategy>
    GraphT (Strategy, std::string fileName)
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
            Strategy::addEdge(*this, v, w);
        }
        v_ = vertexes_.size();
    }

    size_t vertexCount() const { return v_; }
    size_t edgeCount()   const { return e_; }
    const  EdgeContainer& operator[] (size_t index) const { return vertexes_[index]; }
protected:
    friend struct NonDirectedGraphPolicy<GraphT>;
    friend struct DirectedGraphPolicy<GraphT>;
    size_t v_;
    size_t e_;
    std::vector<EdgeContainer> vertexes_;
};

using Graph             = GraphT<EdgeNonWeighted>;
using EdgeWeightedGraph = GraphT<EdgeWeighted>;


} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_HPP
//--------------------------------------------------------------------------------------------------

