//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   16-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "TestGraph.hpp"
#include "GraphAlgorithms.hpp"

#include <fstream>
#include <memory>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------

namespace graph
{

enum class AlgId : int
{
    GRAPH = 300,
    GRAPH_DIRECTED,
    GRAPH_SYMBOL,
};

TestGraph::TestGraph(size_t algId, const std::string & fileName) : algId_(algId), fileName_(fileName) {}

void TestGraph::runTest(tools::Timer & timer)
{
    timer.start();
    switch (static_cast<AlgId>(algId_))
    {
        case AlgId::GRAPH:
        {
            Graph gr(fileName_, std::make_unique<NonDirectedGraphStrategy>());
            showGraphProperties(gr);
            break;
        }
        case AlgId::GRAPH_DIRECTED:
        {
            Graph gr(fileName_, std::make_unique<DirectedGraphStrategy>());
            showGraphProperties(gr);
            break;
        }
        case AlgId::GRAPH_SYMBOL:
        {
            SymbolGraph sgr(fileName_);
            std::cout << "vertex #2:\n" << sgr.lexical(2);
            showGraphProperties(sgr.G());
            break;
        }
    }
}

void TestGraph::showGraphProperties(const Graph & gr) const

{
    gr.toString();

    std::cout << "degree 5: " << Graph::degree(gr, 5) << std::endl;
    std::cout << "max degree: " << Graph::maxDegree(gr) << std::endl;
    std::cout << "avg degree: " << Graph::avgDegree(gr) << std::endl;
    std::cout << "self loops: " << Graph::selfLoops(gr) << std::endl;

    DeepFirstSearch dfs(gr, 0);
    DeepFirstPaths dfp(gr, 5);
    std::cout << "deep to 5:\t" << dfp.pathTo(0) << std::endl;

    BreadthFirstPaths bfp(gr, 5);
    std::cout << "breadth to 5:\t" <<  bfp.pathTo(0) << std::endl;

    CoupledComponents ccg(gr);
    std::cout << "components: " << ccg.componentsCount() << std::endl;

    Cyclic cg(gr);
    std::cout << "has cycle: " << std::boolalpha << cg.isCyclic() << std::endl;

    TwoColored tcg(gr);
    std::cout << "is bipartite: " << std::boolalpha << tcg.isBipartite() << std::endl;
}

} // namespace graph

