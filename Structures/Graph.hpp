/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 10-Jun-2018
 */

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

/**
 * @class GraphT
 * @brief The GraphT template class represents the graph data structure.
 * @tparam Edge edge type
 */
template <typename Edge = EdgeNonWeighted>
class GraphT
{
public:
    /// @brief type of the edges
    using EdgeType = Edge;

    /// @brief container of the edges
    using EdgeContainer = std::list<Edge>;

    /**
     * @brief The GraphT constructor creates empty grapth.
     * @param[in] v size of the graph
     */
    explicit GraphT(size_t v) : v_(v), e_(0), vertexes_(v) {}

    /**
     * @brief The GraphT constructor creates grapth reading data from the file.
     * @param[in] strategy type used for overloading template constructor
     * @param[in] fileName name of the file
     */
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

    /// @return number of vertexes in the graph
    size_t vertexCount() const { return v_; }

    /// @return number of edges in the graph
    size_t edgeCount() const { return e_; }

    /**
     * @brief Gets edges of the given vertex
     * @param[in] index vertex
     * @return edges of the given vertex
     */
    const EdgeContainer & operator[] (size_t index) const { return vertexes_[index]; }
protected:
    friend struct NonDirectedGraphPolicy<GraphT>;
    friend struct DirectedGraphPolicy<GraphT>;
    size_t v_;
    size_t e_;
    std::vector<EdgeContainer> vertexes_;
};

/**
 * @brief The Graph class is the explicit instantiation of GraphT with non-weighted edges.
 */
using Graph = GraphT<EdgeNonWeighted>;

/**
 * @brief The EdgeWeightedGraph class is the explicit instantiation of GraphT with
 * weighted edges.
 */
using EdgeWeightedGraph = GraphT<EdgeWeighted>;


} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_HPP
//--------------------------------------------------------------------------------------------------

