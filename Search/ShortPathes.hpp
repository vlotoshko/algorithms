//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   05-Nov-2018
//--------------------------------------------------------------------------------------------------

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
class Pathes
{
public:
    using EdgeContainer = std::vector<EdgeWeighted>;

    Pathes(const EdgeWeightedGraph & gr, size_t s);
    double        distTo(size_t v)    const;
    bool          hasPathTo(size_t v) const;
    EdgeContainer pathTo(size_t v)    const;

protected:
    void relax(const EdgeWeightedGraph & gr, size_t v);
    std::vector<double> distTo_;
    EdgeContainer edgeTo_;
};

template<typename Compare, typename InitialValue>
Pathes<Compare, InitialValue>::Pathes(const EdgeWeightedGraph & gr, size_t s) :
    distTo_(gr.vertexCount(), InitialValue{}()),
    edgeTo_(gr.vertexCount(), EdgeWeighted{})
{
    distTo_[s] = 0;
}

template<typename Compare, typename InitialValue>
double Pathes<Compare, InitialValue>::distTo(size_t v) const
{
    return distTo_[v];
}

template<typename Compare, typename InitialValue>
bool Pathes<Compare, InitialValue>::hasPathTo(size_t v) const
{
    return Compare{}(InitialValue{}(), distTo_[v]);
}

template<typename Compare, typename InitialValue>
typename Pathes<Compare, InitialValue>::EdgeContainer Pathes<Compare, InitialValue>::pathTo(size_t v) const
{
    typename Pathes<Compare, InitialValue>::EdgeContainer edges;

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
void Pathes<Compare, InitialValue>::relax(const EdgeWeightedGraph & gr, size_t v)
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
using ShortPathes = Pathes<std::greater<>, MaxDouble>;
using LongPathes  = Pathes<std::less<>, MinDouble>;


class DijkstraSP : public ShortPathes
{
public:
    DijkstraSP(const EdgeWeightedGraph & gr, size_t s);
    void relax(const EdgeWeightedGraph & gr, size_t v); // hides relax of base class

    static char const * name;
private:
    data_structs::IndexedPriorityQueue<double, std::greater<double>> pq_;
};


class DijkstraAllPairsSP
{
public:
    using EdgeContainer = ShortPathes::EdgeContainer;

    explicit DijkstraAllPairsSP(const EdgeWeightedGraph & gr);
    double        distTo(size_t s, size_t t)  const;
    EdgeContainer pathTo(size_t s, size_t t) const;
private:
    std::vector<DijkstraSP> all_;
};

class AcyclicSP : public ShortPathes
{
public:
    using EdgeContainer = ShortPathes::EdgeContainer;

    AcyclicSP(const EdgeWeightedGraph & gr, size_t s);

    static char const * name;
};

class AcyclicLP : public LongPathes
{
public:
    using EdgeContainer = ShortPathes::EdgeContainer;

    AcyclicLP(const EdgeWeightedGraph & gr, size_t s);

    static char const * name;
};

} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // SHORT_PATHES_HPP
//--------------------------------------------------------------------------------------------------

