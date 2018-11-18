//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   13-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef TESTGRAPH_HPP
#define TESTGRAPH_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "ITestable.hpp"
#include "Graph.hpp"
#include "EdgeWeightedGraph.hpp"

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------

namespace graph
{

class TestGraph : public ITestable
{
public:
    TestGraph(size_t algId, const std::string & fileName);
    void runTest(tools::Timer & timer) override;

private:
    void showGraphCommonProperties(const Graph & gr) const;
    void showDirectedGraphProperties(const Graph & gr) const;
    void showEWGraphProperties(const EdgeWeightedGraph &gr) const;
    void getShortPathes(const EdgeWeightedGraph &gr) const;
    size_t algId_;
    std::string fileName_;
};


} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // TESTGRAPH_HPP
//--------------------------------------------------------------------------------------------------
