//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   16-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "TestGraph.hpp"
#include "DeepFirstSearch.hpp"
#include "BreadthFirstSearch.hpp"

#include <fstream>
#include <memory>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------

namespace graph
{

TestGraph::TestGraph(size_t algId, const std::string & fileName) : algId_(algId), fileName_(fileName) {}

void TestGraph::runTest(tools::Timer & timer)
{
    timer.start();
    if (algId_ == 300)
    {
        Graph gr(fileName_);
        showGraphProperties(gr);
    }
    else if (algId_ == 301)
    {
        SymbolGraph sgr(fileName_);
        showGraphProperties(sgr.G());
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
    DeepFirstPaths dfp(gr, 0);
    std::cout << "deep to 5:\t" << dfp.pathTo(5) << std::endl;

    BreadthFirstPaths bfp(gr, 0);
    std::cout << "breadth to 5:\t" <<  bfp.pathTo(5) << std::endl;

    CoupledComponents ccg(gr);
    std::cout << "components: " << ccg.componentsCount() << std::endl;

    Cyclic cg(gr);
    std::cout << "has cycle: " << std::boolalpha << cg.isCyclic() << std::endl;

    TwoColored tcg(gr);
    std::cout << "is bipartite: " << std::boolalpha << tcg.isBipartite() << std::endl;
}

} // namespace graph

