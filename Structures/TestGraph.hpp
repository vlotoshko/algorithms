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
#include "DeepFirstSearch.hpp"
#include "BreadthFirstSearch.hpp"

#include <fstream>
#include <memory>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------

namespace graph
{

class TestGraph : public ITestable
{
public:
    TestGraph(size_t algId, const std::string & fileName) : algId_(algId), fileName_(fileName) {}

    void runTest(tools::Timer & timer) override
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

private:
    void showGraphProperties(const Graph & gr)
    {
        gr.toString();

        std::cout << "degree 5: " << Graph::degree(&gr, 5) << std::endl;
        std::cout << "max degree: " << Graph::maxDegree(&gr) << std::endl;
        std::cout << "avg degree: " << Graph::avgDegree(&gr) << std::endl;
        std::cout << "self loops: " << Graph::selfLoops(&gr) << std::endl;

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
    size_t algId_;
    std::string fileName_;
};


} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // TESTGRAPH_HPP
//--------------------------------------------------------------------------------------------------
