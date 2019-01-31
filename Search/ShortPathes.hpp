/**
 * --------------------------------------------------------------------------------------------------
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @skype vlotoshko
 * @date 05-Nov-2018
 * --------------------------------------------------------------------------------------------------
 */

//--------------------------------------------------------------------------------------------------
#ifndef SHORT_PATHES_HPP
#define SHORT_PATHES_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Graph.hpp"
#include "IndexedPQ.hpp"

#include <vector>
//--------------------------------------------------------------------------------------------------

namespace graph
{

template<typename Compare, typename InitialValue>
class Paths
{
public:
    using EdgeContainer = std::vector<EdgeWeighted>;

    Paths(const EdgeWeightedGraph & gr, size_t s);
    double        distTo(size_t v)    const;
    bool          hasPathTo(size_t v) const;
    EdgeContainer pathTo(size_t v)    const;

protected:
    void relax(const EdgeWeightedGraph & gr, size_t v);
    std::vector<double> distTo_;
    EdgeContainer edgeTo_;
};

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

struct MaxDouble
{
    double operator()() const { return std::numeric_limits<double>::max(); }
};

struct MinDouble
{
    double operator()() const { return std::numeric_limits<double>::lowest(); }
};
using ShortPaths = Paths<std::greater<>, MaxDouble>;
using LongPaths  = Paths<std::less<>, MinDouble>;



/**
 * -------------------------------------------------------------------------------
 * @class DijkstraSP
 * @brief The DijkstraSP class holds shortest paths from given vertex
 *
 * The DijkstraSP class holds shortest paths from given vertex to other vertexes
 * in the given graph with non-negative weighted edges
 * -------------------------------------------------------------------------------
 */
class DijkstraSP : public ShortPaths
{
public:
    DijkstraSP(const EdgeWeightedGraph & gr, size_t s);
    void relax(const EdgeWeightedGraph & gr, size_t v); // hides relax of base class

    static char const * name;
private:
    data_structs::IndexedPriorityQueue<double, std::greater<double>> pq_;
};


/**
 * -------------------------------------------------------------------------------
 * @class DijkstraAllPairsSP
 * @brief The DijkstraAllPairsSP class holds pairs of shortes paths
 *
 * The AcyclicSP class holds pairs of hortest paths from all vertexes to other
 * vertexes in the given acyclic graph with non-negative weighted edges
 * -------------------------------------------------------------------------------
 */
class DijkstraAllPairsSP
{
public:
    using EdgeContainer = ShortPaths::EdgeContainer;

    explicit DijkstraAllPairsSP(const EdgeWeightedGraph & gr);
    double        distTo(size_t s, size_t t)  const;
    EdgeContainer pathTo(size_t s, size_t t) const;
private:
    std::vector<DijkstraSP> all_;
};


/**
 * -------------------------------------------------------------------------------
 * @class AcyclicSP
 * @brief The AcyclicSP class holds shortest paths from given vertex
 *
 * The AcyclicSP class holds shortest paths from given vertex to other vertexes
 * in the given acyclic graph with non-negative weighted edges
 * -------------------------------------------------------------------------------
 */
class AcyclicSP : public ShortPaths
{
public:
    using EdgeContainer = ShortPaths::EdgeContainer;

    AcyclicSP(const EdgeWeightedGraph & gr, size_t s);

    static char const * name;
};


/**
 * -------------------------------------------------------------------------------
 * @class AcyclicLP
 * @brief The AcyclicLP class holds longest paths from given vertex
 *
 * The AcyclicLP class holds longest paths from given vertex to other vertexes
 * in the given acyclic graph with non-negative weighted edges
 * -------------------------------------------------------------------------------
 */
class AcyclicLP : public LongPaths
{
public:
    using EdgeContainer = ShortPaths::EdgeContainer;

    AcyclicLP(const EdgeWeightedGraph & gr, size_t s);

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

    /** Time duration of job lasting */
    double duration;
    /** Indexes of dependent jobs in the container with all jobs */
    std::vector<size_t> dependentJobs;
};

using ContinuousJobs = std::vector<ContinuousJob>;


/**
 * -------------------------------------------------------------------------------
 * @class criticalPathMethod
 * @brief The criticalPathMethod function generates graph for parallel dependend
 * jobs
 * @param Const reference to ContinuousJobs
 * @return Returns AcyclicLP object which presents distTo as time when dependent
 * job can be started to execute
 * -------------------------------------------------------------------------------
 */
AcyclicLP criticalPathMethod(const ContinuousJobs & jobs);

} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // SHORT_PATHES_HPP
//--------------------------------------------------------------------------------------------------

