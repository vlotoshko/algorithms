//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   05-Nov-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef SHORT_PATHES_HPP
#define SHORT_PATHES_HPP
//--------------------------------------------------------------------------------------------------
#include "EdgeWeightedGraph.hpp"
#include "IndexedPQ.hpp"

#include <vector>
//--------------------------------------------------------------------------------------------------

namespace graph
{

class ShortPathes
{
public:
    using EdgeContainer = std::vector<Edge>;

    ShortPathes(const EdgeWeightedGraph & gr, size_t s);
    double        distTo(size_t v)    const;
    bool          hasPathTo(size_t v) const;
    EdgeContainer pathTo(size_t v)    const;

protected:
    void relax(const EdgeWeightedGraph & gr, size_t v);
    std::vector<double> distTo_;
    EdgeContainer edgeTo_;
};

class DijkstraSP : public ShortPathes
{
public:
    DijkstraSP(const EdgeWeightedGraph & gr, size_t s);
    void relax(const EdgeWeightedGraph & gr, size_t v); // hides relax of base class

private:
    data_structs::IndexedPriorityQueue<double, std::greater<double>> pq_;
};


class DijkstraAllPairsSP
{
public:
    using EdgeContainer = ShortPathes::EdgeContainer;

    DijkstraAllPairsSP(const EdgeWeightedGraph & gr);
    double        distTo(size_t s, size_t t)  const;
    EdgeContainer pathTo(size_t s, size_t t) const;
private:
    std::vector<DijkstraSP> all_;
};


} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // SHORT_PATHES_HPP
//--------------------------------------------------------------------------------------------------
