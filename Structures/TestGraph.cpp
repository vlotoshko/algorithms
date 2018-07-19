//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   16-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "TestGraph.hpp"
#include "GraphAlgorithms.hpp"
#include "MinimalSpanningTree.hpp"

#include "IndexedPQ.hpp"

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
    GRAPH_EDGEWEIGHTED,
    GRAPH_MST,
};

TestGraph::TestGraph(size_t algId, const std::string & fileName) : algId_(algId), fileName_(fileName) {}

void TestGraph::runTest(tools::Timer & timer)
{
    timer.start();
    switch (static_cast<AlgId>(algId_))
    {
        case AlgId::GRAPH:
        {
            Graph gr(fileName_, std::make_shared<NonDirectedGraphStrategy>());
            showGraphCommonProperties(gr);
            break;
        }
        case AlgId::GRAPH_DIRECTED:
        {
            Graph gr(fileName_, std::make_shared<DirectedGraphStrategy>());
            showGraphCommonProperties(gr);
            showDirectedGraphProperties(gr);
            break;
        }
        case AlgId::GRAPH_SYMBOL:
        {
            SymbolGraph sgr(fileName_);
            std::cout << "vertex #2:\n" << sgr.lexical(2);
            showGraphCommonProperties(sgr.G());
            break;
        }
        case AlgId::GRAPH_EDGEWEIGHTED:
        {
            EdgeWeightedGraph gr(fileName_, std::make_shared<NonDirectedEWGraphStrategy>());
            showEWGraphProperties(gr);
            break;
        }
        case AlgId::GRAPH_MST:
        {
            EdgeWeightedGraph gr(fileName_, std::make_shared<NonDirectedEWGraphStrategy>());
            showEWGraphProperties(gr);
            break;
        }
    }
}

void TestGraph::showGraphCommonProperties(const Graph & gr) const
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

void TestGraph::showDirectedGraphProperties(const Graph &gr) const
{
    DepthFirstOrder dfo(gr);

    std::cout << "Deep first order " << std::endl;
    std::cout << "preorder: " << std::endl;
    while(dfo.pre().size() > 0)
    {
        std::cout << dfo.pre().front() << " ";
        dfo.pre().pop();
    }
    std::cout << std::endl;

    std::cout << "postorder: " << std::endl;
    while(dfo.post().size() > 0)
    {
        std::cout << dfo.post().front() << " ";
        dfo.post().pop();
    }
    std::cout << std::endl;


    std::cout << "reversed postorder: " << std::endl;
    while(dfo.reversePost().size() > 0)
    {
        std::cout << dfo.reversePost().top() << " ";
        dfo.reversePost().pop();
    }
    std::cout << std::endl;

    Topological tpl(gr);
    std::cout << "Topological: " << std::endl;
    if (!tpl.isDAG())
    {
        std::cout << "graph not DAG";
    }
    else
    {
        while(tpl.isDAG() && tpl.order().size() > 0)
        {
            std::cout << tpl.order().top() << " ";
            tpl.order().pop();
        }
    }
    std::cout << std::endl;

    KosarajuSCC KSCC(gr);
    std::cout << "KSCC components: " << KSCC.count();
    std::cout << std::endl;

    std::cout << "TransitiveClosure: " << std::endl;
    TransitiveClosure tc(gr);
    std::cout << "0, 7 reachable: " << std::boolalpha << tc.reachable(0, 7) << std::endl;
    std::cout << "1, 5 reachable: " << std::boolalpha << tc.reachable(1, 5) << std::endl;
    std::cout << "3, 9 reachable: " << std::boolalpha << tc.reachable(3, 9) << std::endl;
    std::cout << "9, 4 reachable: " << std::boolalpha << tc.reachable(9, 4) << std::endl;
}

void TestGraph::showEWGraphProperties(const EdgeWeightedGraph & gr) const
{
    gr.toString();

    PrimMST_Lazy lazyMST(gr);
    std::cout << "Lazy Prim MST: " << std::endl;
    auto edges = lazyMST.edges();
    for (auto const & edge : edges)
    {
        auto v = edge.either();
        std::cout << v << "-" << edge.other(v) << " cost: " << edge.weight() << std::endl;
    }

    std::cout << std::endl;
    PrimMST_Energy energyMST(gr);
    std::cout << "Energy Prim MST: " << std::endl;
    auto ec = energyMST.edges();
    for (auto const & edge : ec)
    {
        auto v = edge.either();
        std::cout << v << "-" << edge.other(v) << " cost: " << edge.weight() << std::endl;
    }

    std::cout << std::endl;
    data_structs::IndexedPriorityQueue<double, std::greater<double>> ipq(10);

    ipq.push(7, 0.16);
    ipq.push(4, 0.38);
    ipq.push(2, 0.26);
    ipq.push(6, 0.58);

    std::cout << "top: " << ipq.top() << std::endl;
    ipq.pop();

    ipq.push(4, 0.37);
    ipq.push(5, 0.28);
    ipq.push(1, 0.19);

    for (size_t i = 0; i < 10; ++i)
    {
        std::cout << "element[" << i << "]: ";
        if (ipq.containes(i))
        {
            std::cout << ipq[i] << std::endl;
        }
        else
        {
            std::cout << "element does not exist." << std::endl;
        }

    }
    while (!ipq.empty())
    {
        std::cout << "top: " << ipq.top() << std::endl;
        ipq.pop();

//        for (size_t i = 0; i < 10; ++i)
//        {
//            std::cout << "element[" << i << "]: ";
//            if (ipq.containes(i))
//            {
//                std::cout << ipq[i] << std::endl;
//            }
//            else
//            {
//                std::cout << "element does not exist." << std::endl;
//            }
//        }

    }





}

} // namespace graph

