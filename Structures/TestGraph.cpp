//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   16-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "TestGraph.hpp"
#include "MinimalSpanningTree.hpp"
#include "ShortPathes.hpp"

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
    GRAPH_SHORT_PATHES,
};

template<>
void TestGraph::showDirectionDependedProperties<DirectedGraphStrategy<Graph>>(DirectedGraphStrategy<Graph>, const Graph & gr) const
{
    showDirectedGraphProperties(gr);
}

TestGraph::TestGraph(size_t algId, const std::string & fileName) : algId_(algId), fileName_(fileName) {}

void TestGraph::runTest(tools::Timer & timer)
{
    timer.start();
    switch (static_cast<AlgId>(algId_))
    {
        case AlgId::GRAPH:
        {
            Graph gr(NonDirectedGraphStrategy<Graph>{}, fileName_);
            showGraphProperties<NonDirectedGraphStrategy<Graph>>(gr);
            break;
        }
        case AlgId::GRAPH_DIRECTED:
        {
            Graph gr(DirectedGraphStrategy<Graph>{}, fileName_);
            showGraphProperties<DirectedGraphStrategy<Graph>>(gr);
            break;
        }
        case AlgId::GRAPH_SYMBOL:
        {
            SymbolGraph sgr(fileName_);
            std::cout << "vertex #2:\n" << sgr.lexical(2);
            showGraphProperties<NonDirectedGraphStrategy<Graph>>(sgr.G());
            break;
        }
        case AlgId::GRAPH_EDGEWEIGHTED:
        {
            EdgeWeightedGraph gr(NonDirectedGraphStrategy<EdgeWeightedGraph>{}, fileName_);
            showEWGraphProperties(gr);
            break;
        }
        case AlgId::GRAPH_MST:
        {
            EdgeWeightedGraph gr(NonDirectedGraphStrategy<EdgeWeightedGraph>{}, fileName_);
            showEWGraphProperties(gr);
            break;
        }
        case AlgId::GRAPH_SHORT_PATHES:
        {
            EdgeWeightedGraph gr(DirectedGraphStrategy<EdgeWeightedGraph>{}, fileName_);;
            getShortPathes(gr);
            break;
        }
    }
}

void TestGraph::showCommonProperties(const Graph & gr) const
{
    toString(gr);

    std::cout << "degree 5: "   << degree(gr, 5) << std::endl;
    std::cout << "max degree: " << maxDegree(gr) << std::endl;

    deepFirstSearh(gr, 0);
    DeepFirstPaths<Graph> dfp(gr, 5);
    std::cout << "deep to 5:\t" << dfp.pathTo(0) << std::endl;

    BreadthFirstPaths bfp(gr, 5);
    std::cout << "breadth to 5:\t" <<  bfp.pathTo(0) << std::endl;

    CoupledComponents ccg(gr);
    std::cout << "components: " << ccg.componentsCount() << std::endl;

    Cyclic<Graph> cg(gr);
    std::cout << "has cycle: " << std::boolalpha << cg.isCyclic() << std::endl;

    TwoColored tcg(gr);
    std::cout << "is bipartite: " << std::boolalpha << tcg.isBipartite() << std::endl;
}

//void TestGraph::showGraphCommonProperties(const Graph & gr) const
//{
//    toString(gr);

//    std::cout << "degree 5: "   << degree(gr, 5) << std::endl;
//    std::cout << "max degree: " << maxDegree(gr) << std::endl;
//    std::cout << "avg degree: " << avgDegree(gr) << std::endl;
//    std::cout << "self loops: " << selfLoops(gr) << std::endl;

//    DeepFirstSearch dfs(gr, 0);
//    DeepFirstPaths dfp(gr, 5);
//    std::cout << "deep to 5:\t" << dfp.pathTo(0) << std::endl;

//    BreadthFirstPaths bfp(gr, 5);
//    std::cout << "breadth to 5:\t" <<  bfp.pathTo(0) << std::endl;

//    CoupledComponents ccg(gr);
//    std::cout << "components: " << ccg.componentsCount() << std::endl;

//    Cyclic cg(gr);
//    std::cout << "has cycle: " << std::boolalpha << cg.isCyclic() << std::endl;

//    TwoColored tcg(gr);
//    std::cout << "is bipartite: " << std::boolalpha << tcg.isBipartite() << std::endl;
//}

void TestGraph::showDirectedGraphProperties(const Graph &gr) const
{
    DepthFirstOrder<Graph> dfo(gr);

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

    Topological<Graph> tpl(gr);
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

    KosarajuSCC<Graph> KSCC(gr);
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
    toString(gr);

    std::cout << std::endl;
    PrimMST_Lazy lazyMST(gr);
    std::cout << "Lazy Prim MST: " << std::endl;
    for (auto const & edge : lazyMST.edges())
    {
        auto v = edge.either();
        std::cout << v << "-" << edge.other(v) << " cost: " << edge.weight() << std::endl;
    }

    std::cout << std::endl;
    PrimMST_Energy energyMST(gr);
    std::cout << "Energy Prim MST: " << std::endl;
    for (auto const & edge : energyMST.edges())
    {
        auto v = edge.either();
        std::cout << v << "-" << edge.other(v) << " cost: " << edge.weight() << std::endl;
    }

    std::cout << std::endl;
    KruskalMST kruskalMST(gr);
    std::cout << "Kruskal MST: " << std::endl;
    for (auto const & edge : kruskalMST.edges())
    {
        auto v = edge.either();
        std::cout << v << "-" << edge.other(v) << " cost: " << edge.weight() << std::endl;
    }
}

void TestGraph::getShortPathes(const EdgeWeightedGraph & gr) const
{
    toString(gr);

    std::cout << std::endl;
    DijkstraSP dijkstraSP(gr, 3);
    std::cout << "Dijkstra short pathes from 0 to 6: " << std::endl;
    for (auto const & edge : dijkstraSP.pathTo(5))
    {
        auto v = edge.either();
        std::cout << v << "-" << edge.other(v) << " cost: " << edge.weight() << std::endl;
    }
}

} // namespace graph

