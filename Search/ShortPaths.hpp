/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 05-Nov-2018
 */

// -------------------------------------------------------------------------------------------------
#ifndef SHORT_PATHS_HPP
#define SHORT_PATHS_HPP
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
#include "Graph.hpp"
#include "IndexedPQ.hpp"

#include <vector>
// -------------------------------------------------------------------------------------------------

namespace graph
{

/**
 * @class Paths
 * @brief The Paths template class finds paths from given vertex to others.
 * @tparam Compare is the comparator policy to compare two paths to vertex
 * @tparam InitialValue is the initial distanse between two vertexes
 *
 * The Paths template class finds paths from given vertex to other vertexes
 * in the given graph with non-negative weighted edges.
 */
template<typename Compare, typename InitialValue>
class Paths
{
public:
    /**
     * @brief container of the edges
     */
    using EdgeContainer = std::vector<EdgeWeighted>;

    /**
     * @brief The Paths constructor just constructs required data structures.
     * @param[in] gr graph whose paths will be explored
     * @param[in] s initial vertex to explore the grahp
     */
    Paths(const EdgeWeightedGraph & gr, const size_t & s);

    /**
     * @brief Finds distance to given vertex.
     * @param[in] v index of the vertex
     * @return distance to given vertex
     */
    double distTo(const size_t & v) const;

    /**
     * @brief Defines whether there is a path to given vertex.
     * @param[in] v index of the vertex
     * @return true if there is a path to given vertex
     */
    bool hasPathTo(const size_t & v) const;

    /**
     * @brief Finds path to given vertex.
     * @param[in] v index of the vertex
     * @return path to given vertex as container of edges
     */
    EdgeContainer pathTo(const size_t & v) const;

protected:
    /**
     * @brief Changes path to given vertex for a better one.
     * @param[in] gr graph
     * @param[in] v index of the vertex
     *
     * Changes path to given vertex for a better one according to comparator results.
     */
    void relax(const EdgeWeightedGraph & gr, const size_t & v);
    /// Distances from initial vertex to all vertexes in the given graph.
    /// This distance equals InitialValue if there is no path to vertex from initial vertex.
    /// Distance from initial vertex to itself equals zero.
    std::vector<double> distTo_;

    /// Best edges to indexed vertexes from some other vertexes.
    EdgeContainer edgeTo_;
};


/**
 * @struct MaxDouble
 * @brief The MaxDouble struct is a functor that returns max value of double type.
 */
struct MaxDouble
{
    /**
     * @brief operator ()
     * @return maximal double value.
     */
    double operator()() const { return std::numeric_limits<double>::max(); }
};

/**
 * @struct MinDouble
 * @brief The MinDouble struct is a functor that returns lowest value of double
 * type.
 */
struct MinDouble
{
    /**
     * @brief operator ()
     * @return minimal double value.
     */
    double operator()() const { return std::numeric_limits<double>::lowest(); }
};

/**
 * @brief Explicit instantiation for short pathes.
 */
using ShortPaths = Paths<std::greater<>, MaxDouble>;

/**
 * @brief Explicit instantiation for long pathes.
 */
using LongPaths  = Paths<std::less<>, MinDouble>;


/**
 * @class DijkstraSP
 * @brief The DijkstraSP class calculates paths from given vertex to other vertexes,
 * using Dijkstra's algorithm.
 * @note Graph should consist of non-negative weighted edges.
 */
class DijkstraSP : public ShortPaths
{
public:
    /**
     * @brief The DijkstraSP constructor explores graph and finds shortest paths,
     * using Dijkstra's algorithm.
     * @param[in] gr graph whose paths will be explored
     * @param[in] s initial vertex to explore the grahp
     */
    DijkstraSP(const EdgeWeightedGraph & gr, const size_t & s);

    /**
     * @brief Changes path to given vertex for a better one.
     * @param[in] gr graph
     * @param[in] v index of the vertex
     * @note Overloads method of the base class.
     */
    void relax(const EdgeWeightedGraph & gr, const size_t & v);

    /// class name
    static char const * name;
private:
    data_structs::IndexedPriorityQueue<double, std::greater<double>> pq_;
};


/**
 * @class DijkstraAllPairsSP
 * @brief The DijkstraAllPairsSP class holds pairs of shortes paths.
 *
 * The DijkstraAllPairsSP class holds pairs of shortest paths from all vertexes to
 * other vertexes in the given acyclic graph with non-negative weighted edges.
 */
class DijkstraAllPairsSP
{
public:
    /**
     * @brief container of the edges
     */
    using EdgeContainer = ShortPaths::EdgeContainer;

    /**
     * @brief The DijkstraAllPairsSP constructor explores all graph for every vertex
     * as initial vertex and calculates shortest paths, using DijkstraSP algorithm.
     * @param[in] gr graph whose paths will be explored
     */
    explicit DijkstraAllPairsSP(const EdgeWeightedGraph & gr);

    /**
     * @brief Finds distance from one vertex to another.
     * @param[in] s vertex 'from'
     * @param[in] t vertex 'to'
     * @return distance from one vertex to another.
     */
    double distTo(const size_t & s, const size_t & t) const;

    /**
     * @brief Finds path from one vertex to another.
     * @param[in] s vertex 'from'
     * @param[in] t vertex 'to'
     * @return path from one vertex to another.
     */
    EdgeContainer pathTo(const size_t & s, const size_t & t) const;
private:
    /// DijkstraSP for all indexed vertexes as initial vertexes
    std::vector<DijkstraSP> all_;
};


/**
 * @class AcyclicShortPaths
 * @brief The AcyclicShortPaths class holds shortest paths from given vertex.
 *
 * The AcyclicShortPaths class calculates shortest paths from given vertex to other
 * vertexes in the given graph. AcyclicShortPaths uses topological sort property
 * to calculate paths.
 * @note Graph should be directed, acyclic and consist of
 * non-negative weighted edges.
 */
class AcyclicShortPaths : public ShortPaths
{
public:
    /**
     * @brief container of the edges
     */
    using EdgeContainer = ShortPaths::EdgeContainer;

    /**
     * @brief The AcyclicShortPaths constructor explores all graph and calculates
     * shortest paths, using topolocigal sort.
     * @param[in] gr graph whose paths will be explored
     * @param[in] s initial vertex to explore the grahp
     */
    AcyclicShortPaths(const EdgeWeightedGraph & gr, const size_t & s);

    /// class name
    static char const * name;
};


/**
 * @class AcyclicLongPaths
 * @brief The AcyclicLongPaths class holds longest paths from given vertex.
 *
 * The AcyclicLongPaths class calculates longest paths from given vertex to other
 * vertexes in the given graph. AcyclicLongPaths uses topological sort property
 * to calculate paths.
 * @note Graph should be directed, acyclic and consist of
 * non-negative weighted edges.
 */
class AcyclicLongPaths : public LongPaths
{
public:
    /**
     * @brief container of the edges
     */
    using EdgeContainer = ShortPaths::EdgeContainer;

    /**
     * @brief The AcyclicLongPaths constructor explores all graph and calculates
     * longest paths, using topolocigal sort.
     * @param[in] gr graph whose paths will be explored
     * @param[in] s initial vertex to explore the grahp
     */
    AcyclicLongPaths(const EdgeWeightedGraph & gr, const size_t & s);

    /// class name
    static char const * name;
};


/**
 * @struct ContinuousJob
 * @brief The ContinuousJob struct has job duration and list of dependent jobs
 *
 * The ContinuousJob struct has job duration and list of dependent jobs.
 * Dependent jobs list is a vector with indexes of these jobs in the some other
 * container with all jobs. So these indexes should not be bigger than size of
 * that contaier.
 */
struct ContinuousJob
{
    ContinuousJob() = default;

    /// Time duration of job lasting
    double duration;
    /// Indexes of dependent jobs in the container with all jobs
    std::vector<size_t> dependentJobs;
};

/// @brief container of continuous jobs
using ContinuousJobs = std::vector<ContinuousJob>;


/**
 * @brief The criticalPathMethod function generates graph for parallel dependend
 * jobs
 * @param[in] jobs continuous jobs
 * @return AcyclicLongPaths object which presents distTo as time when
 * dependent job can be started to execute.
 */
AcyclicLongPaths criticalPathMethod(const ContinuousJobs & jobs);


// -------------------------------------------------------------------------------
// ---------------- Template classes definitions ---------------------------------
// -------------------------------------------------------------------------------


template<typename Compare, typename InitialValue>
Paths<Compare, InitialValue>::Paths(const EdgeWeightedGraph & gr, const size_t & s) :
    distTo_(gr.vertexCount(), InitialValue{}()),
    edgeTo_(gr.vertexCount(), EdgeWeighted{})
{
    distTo_[s] = 0;
}

template<typename Compare, typename InitialValue>
double Paths<Compare, InitialValue>::distTo(const size_t & v) const
{
    return distTo_[v];
}

template<typename Compare, typename InitialValue>
bool Paths<Compare, InitialValue>::hasPathTo(const size_t & v) const
{
    return Compare{}(InitialValue{}(), distTo_[v]);
}

template<typename Compare, typename InitialValue>
typename Paths<Compare, InitialValue>::EdgeContainer Paths<Compare, InitialValue>::pathTo(const size_t & v) const
{
    typename Paths<Compare, InitialValue>::EdgeContainer edges;

    if (hasPathTo(v))
    {
        for(EdgeWeighted e = edgeTo_[v]; e != EdgeWeighted{}; e = edgeTo_[e.either()])
        {
            edges.push_back(e);
        }
    }
    return edges;
}

template<typename Compare, typename InitialValue>
void Paths<Compare, InitialValue>::relax(const EdgeWeightedGraph & gr, const size_t & v)
{
    for (const auto & edge : gr[v])
    {
        size_t w = edge.other(v);
        if (Compare{}(distTo_[w], distTo_[v] + edge.weight()))
        {
            distTo_[w] = distTo_[v] + edge.weight();
            edgeTo_[w] = edge;
        }
    }
}

} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // SHORT_PATHS_HPP
//--------------------------------------------------------------------------------------------------

