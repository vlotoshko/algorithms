/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 10-Jun-2018
 */

//--------------------------------------------------------------------------------------------------
#ifndef GRAPH_DIRECTION_POLICIES_HPP
#define GRAPH_DIRECTION_POLICIES_HPP
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#include <stddef.h>
//-------------------------------------------------------------------------------------------------

namespace graph
{

/**
 * @struct NonDirectedGraphPolicy
 * @brief The NonDirectedGraphPolicy struct adds edges to the graph as graph is
 * non-directed.
 * @tparam G graph type
 */
template<typename G>
struct NonDirectedGraphPolicy
{
    /**
     * @brief Addes new edge to the graph.
     * @param[out] gr graph
     * @param[in] v vertex 'from'
     * @param[in] w vertex 'to'
     */
    static void addEdge(G & gr, size_t v, size_t w)
    {
        gr.vertexes_[v].emplace_back(v, w);
        gr.vertexes_[w].emplace_back(w, v);
        ++gr.e_;
    }

    /**
     * @brief Addes new edge to the graph.
     * @param[out] gr graph
     * @param[in] e new edge'
     */
    static void addEdge(G & gr, typename G::EdgeType e)
    {
        size_t v = e.either();
        size_t w = e.other(v);
        gr.vertexes_[v].push_back(e);
        gr.vertexes_[w].push_back(e);
        ++gr.e_;
    }

    /**
     * @brief Fills container with edges of the given graph.
     * @param[in] gr graph
     * @param[out] edges container for edges
     */
    static void edges(const G & gr, typename G::EdgeContainer & edges)
    {
        for (size_t v = 0; v < gr.vertexCount(); ++v)
        {
            for (auto e: gr.vertexes_[v])
            {
                if(e.other(v) > v)
                    edges.push_back(e);
            }
        }
    }

    /// @brief scale factor wich helps to calculate number of edges
    static inline size_t factor() { return 2; }
};

/**
 * @struct DirectedGraphPolicy
 * @brief The DirectedGraphPolicy struct adds edges to the graph as graph is directed.
 * @tparam G graph type
 */
template<typename G>
struct DirectedGraphPolicy
{
    /**
     * @brief Addes new edge to the graph.
     * @param[out] gr graph
     * @param[in] v vertex 'from'
     * @param[in] w vertex 'to'
     */
    static void addEdge(G & gr, size_t v, size_t w)
    {
        gr.vertexes_[v].emplace_back(v, w);
        ++gr.e_;
    }

    /**
     * @brief Addes new edge to the graph.
     * @param[out] gr graph
     * @param[in] e new edge'
     */
    static void addEdge(G & gr, typename G::EdgeType e)
    {
        gr.vertexes_[e.either()].push_back(e);
        ++gr.e_;
    }

    /**
     * @brief Fills container with edges of the given graph.
     * @param[in] gr graph
     * @param[out] edges container for edges
     */
    static void edges(const G & gr, typename G::EdgeContainer & edges)
    {
        for (size_t v = 0; v < gr.vertexCount(); ++v)
        {
            for (auto e: gr.vertexes_[v])
            {
                edges.push_back(e);
            }
        }
    }

    /// @brief scale factor wich helps to calculate number of edges
    static inline size_t factor() { return 1; }
};

} //namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_DIRECTION_POLICIES_HPP
//--------------------------------------------------------------------------------------------------

