/**
 * -------------------------------------------------------------------------------------------------
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @skype vlotoshko
 * @date 05-Nov-2018
 * -------------------------------------------------------------------------------------------------
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
 * -------------------------------------------------------------------------------
 * @class Paths
 * @brief The Paths template class finds paths from given vertex
 * @tparam Compare is the comparator policy to compare two paths to vertex
 * @tparam InitialValue is the initial distanse between two vertexes
 *
 * The Paths template class holds finds paths from given vertex to other vertexes
 * in the given graph with non-negative weighted edges
 * -------------------------------------------------------------------------------
 */
template<typename Compare, typename InitialValue>
class Paths
{
public:
    using EdgeContainer = std::vector<EdgeWeighted>;

    /**
     * \brief Paths constructor
     * \param graph whose paths will be explored
     * \param initial vertex to explore the grahp
     *
     * Paths constructor just constructs required data structures
     */
    Paths(const EdgeWeightedGraph & gr, size_t s);

    /**
     * \brief returns distance to given vertex
     * \param vertex's index
     * \return distance to given vertex
     */
    double distTo(size_t v) const;

    /**
     * \brief defines whether there is a path to given vertex
     * \param vertex's index
     * \return true if there is a path to given vertex
     */
    bool hasPathTo(size_t v) const;

    /**
     * \brief returns path to given vertex
     * \param vertex's index
     * \return path to given vertex as container of edges
     */
    EdgeContainer pathTo(size_t v) const;

protected:
    /**
     * \brief changes path to given vertex for a better one
     * \param graph
     * \param vertex's index
     *
     * changes path to given vertex for a better one according to comparator results
     */
    void relax(const EdgeWeightedGraph & gr, size_t v);
    /// distances from initial vertex to all vertexes in the given graph
    /// distance equals InitialValue if there is no path to vertex from initial vertex
    /// distance from initial vertex to itself equals zero
    std::vector<double> distTo_;
    /// best edges to indexed vertexes from some other vertexes
    EdgeContainer edgeTo_;
};


/**
 * -------------------------------------------------------------------------------
 * @struct MaxDouble
 * @brief The MaxDouble struct is a functor that returns max value of double type
 * -------------------------------------------------------------------------------
 */
struct MaxDouble
{
    double operator()() const { return std::numeric_limits<double>::max(); }
};

/**
 * -------------------------------------------------------------------------------
 * @struct MinDouble
 * @brief The MinDouble struct is a functor that returns lowest value of double
 * type
 * -------------------------------------------------------------------------------
 */
struct MinDouble
{
    double operator()() const { return std::numeric_limits<double>::lowest(); }
};

using ShortPaths = Paths<std::greater<>, MaxDouble>;
using LongPaths  = Paths<std::less<>, MinDouble>;


/**
 * -------------------------------------------------------------------------------
 * @class DijkstraSP
 * @brief The DijkstraSP class calculates shortest paths from given vertex
 *
 * The DijkstraSP class calculates paths from given vertex to other vertexes,
 * using Dijkstra's algorithm.
 * Graph should consist of non-negative weighted edges.
 * -------------------------------------------------------------------------------
 */
class DijkstraSP : public ShortPaths
{
public:
    /**
     * \brief DijkstraSP constructor
     * \param graph whose paths will be explored
     * \param initial vertex to explore the grahp
     *
     * DijkstraSP constructor explores graph and finds shortest paths, using
     * DijkstraSP algorithm.
     */
    DijkstraSP(const EdgeWeightedGraph & gr, size_t s);
    /// uses its own implenemtation of relax method and hides base class's implementation
    void relax(const EdgeWeightedGraph & gr, size_t v);

    /// class name
    static char const * name;
private:
    data_structs::IndexedPriorityQueue<double, std::greater<double>> pq_;
};


/**
 * -------------------------------------------------------------------------------
 * @class DijkstraAllPairsSP
 * @brief The DijkstraAllPairsSP class holds pairs of shortes paths
 *
 * The DijkstraAllPairsSP class holds pairs of shortest paths from all vertexes to
 * other vertexes in the given acyclic graph with non-negative weighted edges
 * -------------------------------------------------------------------------------
 */
class DijkstraAllPairsSP
{
public:
    using EdgeContainer = ShortPaths::EdgeContainer;

    /**
     * \brief DijkstraAllPairsSP constructor
     * \param graph whose paths will be explored
     *
     * DijkstraAllPairsSP constructor explores all graph for every vertex as
     * initial vertex and calculates shortest paths, using DijkstraSP algorithm.
     */
    explicit DijkstraAllPairsSP(const EdgeWeightedGraph & gr);

    /**
     * \brief changes path to given vertex for a better one
     * \param graph
     * \param vertex's index
     *
     * changes path to given vertex for a better one according to comparator results
     */
    double        distTo(size_t s, size_t t)  const;

    /**
     * \brief changes path to given vertex for a better one
     * \param graph
     * \param vertex's index
     *
     * changes path to given vertex for a better one according to comparator results
     */
    EdgeContainer pathTo(size_t s, size_t t) const;
private:
    /// DijkstraSP for all indexed vertexes as initial vertexes
    std::vector<DijkstraSP> all_;
};


/**
 * -------------------------------------------------------------------------------
 * @class AcyclicShortPaths
 * @brief The AcyclicShortPaths class holds shortest paths from given vertex
 *
 * The AcyclicShortPaths class calculates shortest paths from given vertex to other
 * vertexes in the given graph. AcyclicShortPaths uses topological sort property
 * to calculate paths. Graph should be directed, acyclic and consist of
 * non-negative weighted edges.
 * -------------------------------------------------------------------------------
 */
class AcyclicShortPaths : public ShortPaths
{
public:
    using EdgeContainer = ShortPaths::EdgeContainer;

    /**
     * \brief AcyclicShortPaths constructor
     * \param graph whose paths will be explored
     * \param initial vertex to explore the grahp
     *
     * AcyclicShortPaths constructor explores all graph and calculates shortest
     * paths, using topolocigal sort.
     */
    AcyclicShortPaths(const EdgeWeightedGraph & gr, size_t s);

    /// class name
    static char const * name;
};


/**
 * -------------------------------------------------------------------------------
 * @class AcyclicLongPaths
 * @brief The AcyclicLongPaths class holds longest paths from given vertex
 *
 * The AcyclicLongPaths class calculates longest paths from given vertex to other
 * vertexes in the given graph. AcyclicLongPaths uses topological sort property
 * to calculate paths. Graph should be directed, acyclic and consist of
 * non-negative weighted edges.
 * -------------------------------------------------------------------------------
 */
class AcyclicLongPaths : public LongPaths
{
public:
    using EdgeContainer = ShortPaths::EdgeContainer;

    /**
     * \brief AcyclicLongPaths constructor
     * \param graph whose paths will be explored
     * \param initial vertex to explore the grahp
     *
     * AcyclicLongPaths constructor explores all graph and calculates longest
     * paths, using topolocigal sort.
     */
    AcyclicLongPaths(const EdgeWeightedGraph & gr, size_t s);

    /// class name
    static char const * name;
};


/**
 * -------------------------------------------------------------------------------
 * @struct ContinuousJob
 * @brief The ContinuousJob struct has job duration and list of dependent jobs
 *
 * The ContinuousJob struct has job duration and list of dependent jobs.
 * Dependent jobs list is a vector with indexes of these jobs in the some other
 * container with all jobs. So these indexes should not be bigger than size of
 * that contaier.
 * -------------------------------------------------------------------------------
 */
struct ContinuousJob
{
    ContinuousJob() = default;

    /// Time duration of job lasting
    double duration;
    /// Indexes of dependent jobs in the container with all jobs
    std::vector<size_t> dependentJobs;
};

using ContinuousJobs = std::vector<ContinuousJob>;


/**
 * -------------------------------------------------------------------------------
 * @brief The criticalPathMethod function generates graph for parallel dependend
 * jobs
 * @param Const reference to ContinuousJobs
 * @return Returns AcyclicLongPaths object which presents distTo as time when
 * dependent job can be started to execute
 * -------------------------------------------------------------------------------
 */
AcyclicLongPaths criticalPathMethod(const ContinuousJobs & jobs);



// -------------------------------------------------------------------------------
// Template classes definitions
// -------------------------------------------------------------------------------

template<typename Compare, typename InitialValue>
Paths<Compare, InitialValue>::Paths(const EdgeWeightedGraph & gr, size_t s) :
    distTo_(gr.vertexCount(), InitialValue{}()),
    edgeTo_(gr.vertexCount(), EdgeWeighted{})
{
    distTo_[s] = 0;
}

template<typename Compare, typename InitialValue>
double Paths<Compare, InitialValue>::distTo(size_t v) const
{
    return distTo_[v];
}

template<typename Compare, typename InitialValue>
bool Paths<Compare, InitialValue>::hasPathTo(size_t v) const
{
    return Compare{}(InitialValue{}(), distTo_[v]);
}

template<typename Compare, typename InitialValue>
typename Paths<Compare, InitialValue>::EdgeContainer Paths<Compare, InitialValue>::pathTo(size_t v) const
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
void Paths<Compare, InitialValue>::relax(const EdgeWeightedGraph & gr, size_t v)
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

