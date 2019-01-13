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
#include "GraphAlgorithms.hpp"
#include "EdgeWeightedGraph.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
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
    void showCommonProperties(const Graph & gr) const;

    template<typename Strategy>
    void showDirectionDependedProperties(Strategy, const Graph &) const {}

    template<typename Strategy>
    void showGraphProperties(const Graph & gr) const
    {
        showCommonProperties(gr);
        std::cout << "avg degree: " << avgDegree<Strategy>(gr) << std::endl;
        std::cout << "self loops: " << selfLoops<Strategy>(gr) << std::endl;
        showDirectionDependedProperties<Strategy>(Strategy{}, gr);
    }
    void showDirectedGraphProperties(const Graph & gr) const;
    void showEWGraphProperties(const EdgeWeightedGraph &gr) const;
    void getShortPathes(const EdgeWeightedGraph &gr) const;
    size_t algId_;
    std::string fileName_;
};


} // namespace graph



namespace tests
{

template <typename G>
class TestGraph : public CppUnit::TestFixture
{
public:
    static CppUnit::Test * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestGraph");

        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "avgDegree_ShouldReturnAverageDegree_WhenGivenGraph",
                                  &TestGraph::avgDegree_ShouldReturnAverageDegree_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "maxDegree_ShouldReturnMaxDegree_WhenGivenGraph",
                                  &TestGraph::maxDegree_ShouldReturnMaxDegree_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "selfLoops_ShouldReturnCountOfSelfLoops_WhenGivenGraph",
                                  &TestGraph::selfLoops_ShouldReturnCountOfSelfLoops_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "reverse_ShouldReturnReversedGraph_WhenGivenGraph",
                                  &TestGraph::reverse_ShouldReturnReversedGraph_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "isCyclic_ShouldReturnTrue_WhenGivenGraphIsCyclic",
                                  &TestGraph::isCyclic_ShouldReturnTrue_WhenGivenGraphIsCyclic));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "deepFirstSearh_ShouldReturnCountOfSteps_WhenGivenGraph",
                                  &TestGraph::deepFirstSearh_ShouldReturnCountOfSteps_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "deepFirstPaths_ShouldReturnPaths_WhenGivenGraphAndVertex",
                                  &TestGraph::deepFirstPaths_ShouldReturnPaths_WhenGivenGraphAndVertex));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "depthFirstOrder_ShouldReturnOrderedGraphs_WhenGivenGraph",
                                  &TestGraph::depthFirstOrder_ShouldReturnOrderedGraphs_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "topological_ShouldReturnTopologialOrder_WhenGivenGraph",
                                  &TestGraph::topological_ShouldReturnTopologialOrder_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "kosarajuSCC_ShouldReturnSCC_WhenGivenGraph",
                                  &TestGraph::kosarajuSCC_ShouldReturnSCC_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "coupledComponents_ShouldReturnCC_WhenGivenGraph",
                                  &TestGraph::coupledComponents_ShouldReturnCC_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "transitiveClosure_ShouldReturnReachable_WhenGivenGraph",
                                  &TestGraph::transitiveClosure_ShouldReturnReachable_WhenGivenGraph));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "twoColored_ShouldReturnTrue_WhenGivenGraphIsBipartite",
                                  &TestGraph::twoColored_ShouldReturnTrue_WhenGivenGraphIsBipartite));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestGraph<G>>(
                                  "breadthFirstPaths_ShouldReturnPaths_WhenGivenGraphAndVertex",
                                  &TestGraph::breadthFirstPaths_ShouldReturnPaths_WhenGivenGraphAndVertex));
        return suiteOfTests;
    }

    void setUpCustom()
    {
        using Strategy = graph::NonDirectedGraphPolicy<G>;
        Strategy::addEdge(graph_, 0, 3);
        Strategy::addEdge(graph_, 2, 4);
        Strategy::addEdge(graph_, 2, 7);
        Strategy::addEdge(graph_, 9, 4);
        Strategy::addEdge(graph_, 6, 7);
        Strategy::addEdge(graph_, 0, 8);
        Strategy::addEdge(graph_, 6, 3);
        Strategy::addEdge(graph_, 1, 9);
        Strategy::addEdge(graph_, 7, 9);
        Strategy::addEdge(graph_, 2, 2);
    }
protected:
    void avgDegree_ShouldReturnAverageDegree_WhenGivenGraph()
    {
        setUpCustom();
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2),
                             graph::avgDegree<graph::NonDirectedGraphPolicy<G>>(graph_));
    }

    void maxDegree_ShouldReturnMaxDegree_WhenGivenGraph()
    {
        setUpCustom();
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), graph::maxDegree(graph_));
    }

    void selfLoops_ShouldReturnCountOfSelfLoops_WhenGivenGraph()
    {
        setUpCustom();
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1),
                             graph::selfLoops<graph::NonDirectedGraphPolicy<G>>(graph_));
    }

    void reverse_ShouldReturnReversedGraph_WhenGivenGraph()
    {
        setUpCustom();
        // NOTE: make sense only for directed graphs
        auto reversed = graph::reverse<graph::DirectedGraphPolicy<G>>(graph_);
//        graph::toString(graph_);
//        graph::toString(*reversed);
    }

    void isCyclic_ShouldReturnTrue_WhenGivenGraphIsCyclic()
    {
        G gr{10};
        using Strategy = graph::NonDirectedGraphPolicy<G>;
        Strategy::addEdge(gr, 0, 3);
        Strategy::addEdge(gr, 2, 4);
        Strategy::addEdge(gr, 2, 7);
        Strategy::addEdge(gr, 9, 4);
        Strategy::addEdge(gr, 6, 7);
        setUpCustom();
        CPPUNIT_ASSERT(graph::Cyclic<G>{graph_}.isCyclic());
        CPPUNIT_ASSERT(!graph::Cyclic<G>{gr}.isCyclic());
    }

    void deepFirstSearh_ShouldReturnCountOfSteps_WhenGivenGraph()
    {
        setUpCustom();
        graph::DeepFirstSearch dfs(graph_, 0);
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(9), graph::deepFirstSearh(graph_, 0));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(9), dfs.count());
    }

    void deepFirstPaths_ShouldReturnPaths_WhenGivenGraphAndVertex()
    {
        setUpCustom();
        graph::DeepFirstPaths<G> dfp(graph_, 0);
        CPPUNIT_ASSERT(dfp.hasPathTo(4));
        CPPUNIT_ASSERT(dfp.hasPathTo(0));
        CPPUNIT_ASSERT(!dfp.hasPathTo(5));
    }

    void depthFirstOrder_ShouldReturnOrderedGraphs_WhenGivenGraph()
    {
        G gr{10};
        using Strategy = graph::DirectedGraphPolicy<G>;
        Strategy::addEdge(gr, 0, 3);
        Strategy::addEdge(gr, 2, 4);
        Strategy::addEdge(gr, 2, 7);
        Strategy::addEdge(gr, 9, 4);
        Strategy::addEdge(gr, 0, 6);
        Strategy::addEdge(gr, 3, 9);
        Strategy::addEdge(gr, 6, 7);
        graph::DepthFirstOrder<G> dfo(gr);

        auto preOder = dfo.pre();
        auto preGet = [&preOder](){ auto item = preOder.front(); preOder.pop(); return item; };
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), preGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), preGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(9), preGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), preGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), preGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(7), preGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), preGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), preGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), preGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8), preGet());

        auto postOder = dfo.post();
        auto postGet = [&postOder](){ auto item = postOder.front(); postOder.pop(); return item; };
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), postGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(9), postGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), postGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(7), postGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), postGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), postGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), postGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), postGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), postGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8), postGet());

        auto revPostOder = dfo.reversePost();
        auto revPostGet = [&revPostOder](){ auto item = revPostOder.top(); revPostOder.pop(); return item; };
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8), revPostGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), revPostGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), revPostGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), revPostGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), revPostGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), revPostGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(7), revPostGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), revPostGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(9), revPostGet());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), revPostGet());
    }

    void topological_ShouldReturnTopologialOrder_WhenGivenGraph()
    {
        // NOTE: this is stub - topological orger is a reverse post orded
        // and it tests in the depthFirstOrder unit test
    }

    // SCC - Strong Coupled Components
    void kosarajuSCC_ShouldReturnSCC_WhenGivenGraph()
    {
        G gr{10};
        using Strategy = graph::DirectedGraphPolicy<G>;
        Strategy::addEdge(gr, 0, 3);
        Strategy::addEdge(gr, 2, 4);
        Strategy::addEdge(gr, 2, 7);
        Strategy::addEdge(gr, 9, 4);
        Strategy::addEdge(gr, 0, 6);
        Strategy::addEdge(gr, 3, 9);
        Strategy::addEdge(gr, 6, 7);
        Strategy::addEdge(gr, 4, 0);
        graph::KosarajuSCC<G> KSCC(gr);

        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(7), KSCC.count());
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), KSCC.id(0));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), KSCC.id(3));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), KSCC.id(4));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), KSCC.id(9));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), KSCC.id(8));

        CPPUNIT_ASSERT(KSCC.stronglyConnected(0, 9));
        CPPUNIT_ASSERT(KSCC.stronglyConnected(3, 4));
        CPPUNIT_ASSERT(!KSCC.stronglyConnected(3, 7));

    }
    
    void coupledComponents_ShouldReturnCC_WhenGivenGraph()
    {
        G gr{10};
        using Strategy = graph::DirectedGraphPolicy<G>;
        Strategy::addEdge(gr, 0, 3);
        Strategy::addEdge(gr, 2, 4);
        Strategy::addEdge(gr, 2, 7);
        Strategy::addEdge(gr, 9, 4);
        Strategy::addEdge(gr, 0, 6);
        Strategy::addEdge(gr, 3, 9);
        Strategy::addEdge(gr, 6, 7);
        Strategy::addEdge(gr, 4, 0);

        graph::CoupledComponents coupledComponents(gr);
        CPPUNIT_ASSERT(coupledComponents.connected(0, 9));
        CPPUNIT_ASSERT(coupledComponents.connected(6, 7));
        CPPUNIT_ASSERT(!coupledComponents.connected(8, 7));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), coupledComponents.id(9));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), coupledComponents.id(8));
    }
    
    void transitiveClosure_ShouldReturnReachable_WhenGivenGraph()
    {
        G gr{10};
        using Strategy = graph::DirectedGraphPolicy<G>;
        Strategy::addEdge(gr, 0, 3);
        Strategy::addEdge(gr, 2, 4);
        Strategy::addEdge(gr, 2, 7);
        Strategy::addEdge(gr, 9, 4);

        graph::TransitiveClosure tc(gr);

        CPPUNIT_ASSERT(tc.reachable(0, 3));
        CPPUNIT_ASSERT(tc.reachable(7, 7));
        CPPUNIT_ASSERT(!tc.reachable(0, 9));
    }
    
    void twoColored_ShouldReturnTrue_WhenGivenGraphIsBipartite()
    {
        G gr{10};
        using Strategy = graph::NonDirectedGraphPolicy<G>;
        Strategy::addEdge(gr, 0, 3);
        Strategy::addEdge(gr, 2, 4);
        Strategy::addEdge(gr, 3, 9);
        Strategy::addEdge(gr, 9, 4);
        CPPUNIT_ASSERT(graph::TwoColored{gr}.isBipartite());

        Strategy::addEdge(gr, 0, 2);
        CPPUNIT_ASSERT(!graph::TwoColored{gr}.isBipartite());
    }
    
    void breadthFirstPaths_ShouldReturnPaths_WhenGivenGraphAndVertex()
    {
        setUpCustom();
        graph::BreadthFirstPaths bfp(graph_, 0);
        CPPUNIT_ASSERT(bfp.hasPathTo(4));
        CPPUNIT_ASSERT(bfp.hasPathTo(0));
        CPPUNIT_ASSERT(!bfp.hasPathTo(5));
    }
    
private:
    G graph_{10};
};


class TestSymbolGraph : public CppUnit::TestFixture
{
public:
    static CppUnit::Test * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestIsSorted");

        suiteOfTests->addTest(new CppUnit::TestCaller<TestSymbolGraph>(
                                  "addEdge_ShouldAddEdge_WhenGivenTwoKeys",
                                  &TestSymbolGraph::addEdge_ShouldAddEdge_WhenGivenTwoKeys));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestSymbolGraph>(
                                  "addEdge_ShouldReturnFalse_WhenAddedOverflowEdge",
                                  &TestSymbolGraph::addEdge_ShouldReturnFalse_WhenAddedOverflowEdge));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestSymbolGraph>(
                                  "contains_ShouldReturnTrue_WhenGivenExistingsKey",
                                  &TestSymbolGraph::contains_ShouldReturnTrue_WhenGivenExistingsKey));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestSymbolGraph>(
                                  "index_ShouldReturnIndex_WhenGivenKey",
                                  &TestSymbolGraph::index_ShouldReturnIndex_WhenGivenKey));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestSymbolGraph>(
                                  "name_ShouldReturnName_WhenGivenIndex",
                                  &TestSymbolGraph::name_ShouldReturnName_WhenGivenIndex));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestSymbolGraph>(
                                  "lexical_ShouldReturnEdgesAsString_WhenGivenIndex",
                                  &TestSymbolGraph::lexical_ShouldReturnEdgesAsString_WhenGivenIndex));
        return suiteOfTests;
    }

    void setUp() override
    {
        graph_.addEdge("key1", "key2");
    }
protected:
    void addEdge_ShouldAddEdge_WhenGivenTwoKeys()
    {
        graph_.addEdge("key3", "key4");
        CPPUNIT_ASSERT(graph_.contains("key3"));
        CPPUNIT_ASSERT(graph_.contains("key4"));
    }

    void addEdge_ShouldReturnFalse_WhenAddedOverflowEdge()
    {
        CPPUNIT_ASSERT(graph_.addEdge("key3", "key7"));
        CPPUNIT_ASSERT(graph_.addEdge("key4", "key8"));
        CPPUNIT_ASSERT(graph_.addEdge("key5", "key9"));
        CPPUNIT_ASSERT(graph_.addEdge("key6", "key0"));
        CPPUNIT_ASSERT(!graph_.addEdge("keyX", "keyXX"));
    }

    void contains_ShouldReturnTrue_WhenGivenExistingsKey()
    {
        CPPUNIT_ASSERT(graph_.contains("key1"));
        CPPUNIT_ASSERT(!graph_.contains("key0"));
    }

    void index_ShouldReturnIndex_WhenGivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(0, graph_.index("key1"));
        CPPUNIT_ASSERT_EQUAL(1, graph_.index("key2"));
        CPPUNIT_ASSERT_EQUAL(-1, graph_.index("key not exists"));
    }

    void name_ShouldReturnName_WhenGivenIndex()
    {
        CPPUNIT_ASSERT_EQUAL(std::string("key1"), graph_.name(0));
        CPPUNIT_ASSERT_EQUAL(std::string("key2"), graph_.name(1));
        CPPUNIT_ASSERT_EQUAL(std::string(), graph_.name(1000));
    }

    void lexical_ShouldReturnEdgesAsString_WhenGivenIndex()
    {
        graph_.addEdge("key1", "key3");
        graph_.addEdge("key1", "key4");
        std::stringstream test;
        test << "key1" << std::endl
             << "  " << "key2" << std::endl
             << "  " << "key3" << std::endl
             << "  " << "key4" << std::endl;
        CPPUNIT_ASSERT_EQUAL(test.str(), graph_.lexical(0));
    }
private:
    graph::SymbolGraph graph_{10};
};


} // namespace tests

//--------------------------------------------------------------------------------------------------
#endif // TESTGRAPH_HPP
//--------------------------------------------------------------------------------------------------
