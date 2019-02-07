/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 08-Jul-2018
 */

// -------------------------------------------------------------------------------------------------
#ifndef MINIMAL_SPANNING_TREE_HPP
#define MINIMAL_SPANNING_TREE_HPP
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
#include "Graph.hpp"
#include "IndexedPQ.hpp"

#include <vector>
#include <queue>
#include <functional>
// -------------------------------------------------------------------------------------------------

namespace graph
{

/**
 * @class PrimMST_Lazy
 * @brief The PrimMST_Lazy class finds the minimal spanning tree, using Prim's algorithm lazy
 * variant.
 */
class PrimMST_Lazy
{
public:
    using EdgeContainer = EdgeWeightedGraph::EdgeContainer;

    /// class name
    static char const * name;

    /**
     * @brief The PrimMST_Lazy constructor explores graph and builds minimal spanning tree.
     * @param[in] gr graph
     */
    explicit PrimMST_Lazy(const EdgeWeightedGraph & gr);

    /// @returns edges of minimal spanning tree
    EdgeContainer edges() const;
private:
    /**
     * @brief The visit method adds nearest edges of the vertex to the queue.
     * @param[in] gr edgeweighted graph
     * @param[in] v initial vertex
     */
    void visit(const EdgeWeightedGraph & gr, const size_t & v);

    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;

    /// edges of minimal spanning tree
    EdgeContainer mst_;

    /// queue of edges to traverse the graph selecting the minimal edge
    std::priority_queue<EdgeWeighted, std::vector<EdgeWeighted>, std::greater<EdgeWeighted>> pq_;
};


/**
 * @class PrimMST_Energy
 * @brief The PrimMST_Energy class finds the minimal spanning tree, using Prim's algorithm
 * energy variant.
 */
class PrimMST_Energy
{
public:
    using EdgeContainer = std::vector<EdgeWeighted>;

    /// class name
    static char const * name;

    /**
     * @brief The PrimMST_Energy constructor explores graph and builds minimal spanning tree.
     * @param[in] gr graph
     */
    explicit PrimMST_Energy(const EdgeWeightedGraph & gr);

    /// @returns edges of minimal spanning tree
    EdgeContainer edges() const;
private:
    /**
     * @brief The visit method adds nearest edges of the vertex to the queue if edges have
     * smaller distance than found before.
     * @param[in] gr edgeweighted graph
     * @param[in] v initial vertex
     */
    void visit(const EdgeWeightedGraph & gr, const size_t & v);

    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;

    /// holds minimal distance to the vertex
    std::vector<double> distTo_;

    /// edges of minimal spanning tree
    EdgeContainer edgeTo_;

    /// queue of edges to traverse the graph selecting the minimal edge
    data_structs::IndexedPriorityQueue<double, std::greater<double>> pq_;
};


/**
 * @class KruskalMST
 * @brief The KruskalMST class finds the minimal spanning tree, using Kruskal's algorithm
 */
class KruskalMST
{
public:
    using EdgeContainer = EdgeWeightedGraph::EdgeContainer;

    /// class name
    static char const * name;

    /**
     * @brief The KruskalMST constructor explores graph and builds minimal spanning tree,
     * using unionFind object
     * @param[in] gr edgeweighted graph
     */
    explicit KruskalMST(const EdgeWeightedGraph & gr);

    /// @returns edges of minimal spanning tree
    EdgeContainer edges() const;
private:
    /// edges of minimal spanning tree
    EdgeContainer mst_;
};

} // namespace graph

// -------------------------------------------------------------------------------------------------
#endif // MINIMAL_SPANNING_TREE_HPP
// -------------------------------------------------------------------------------------------------

